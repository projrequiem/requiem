#include "interface/Interface.hpp"

SocketInterface::SocketInterface(uint16_t port){

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        logf("Failed to create socket\n");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(sock, (struct sockaddr*)&address, sizeof(sockaddr)) < 0){
        logf("Failed to bind to port: %hu\n", port);
    }

    if (listen(sock, 32) < 0){
        logf("Failed to listen on socket.\n");
    }
}
void SocketInterface::run(){
    std::vector<std::thread> threads;
    auto addrlen = sizeof(sockaddr);
    int connection = 0;
    do{
        connection = accept(sock, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (connection < 0) {
            logf("Failed to grab connection. errno: %d\n",errno);
            exit(EXIT_FAILURE);
        }
        std::thread w(SocketInterface::worker, connection);
        threads.push_back(move(w));
    }while(connection >= 0);
}
bool SocketInterface::recieveJson(int connection, int readLen, char * buffer, int buffLen, rapidjson::Document & jsonObj){
    int totalRead = 0;
    do{
        auto bytesRead = read(connection, buffer+totalRead, buffLen-totalRead);
        if(bytesRead <= 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        logf("Read %ld bytes\n", bytesRead);
        totalRead += bytesRead;
    }while(totalRead < readLen);
    logf("Total: %d bytes read\n", totalRead);
    logf("The message was: %.20s\n\n",buffer);
    logf("The message was: %.20s\n\n",(char *)buffer+totalRead-20);
    if (!SocketInterface::parseJson(buffer, jsonObj)){
        logf("Parsing the following failed: %s", buffer);
        return false;
    }
    return true;
}
void SocketInterface::sendJson(int connection, rapidjson::Document & doc){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    const char* output = buffer.GetString();
    logf("Outputting %.20s\n",output);
    send(connection, output, buffer.GetSize(), 0);
    buffer.Clear();
}
bool SocketInterface::parseJson(char * buffer, rapidjson::Document & doc){
    try{
        doc.Parse(buffer);
    }catch (int e){
        logf("Failed to parse JSON: exception number %d\n", e);
        return false;
    }
    return true;
}
void SocketInterface::worker(int connection){
    while(true){
        char buffer[RECIEVE_BUFF_LEN];
        memset(buffer, 0, RECIEVE_BUFF_LEN);
        rapidjson::Document reqDoc;
        reqDoc.SetObject();
        if(!SocketInterface::recieveJson(connection, -1, buffer, 1024, reqDoc)){
            logf("Failed to recieve request json\n");
            break;
        }
        assert(reqDoc.HasMember("reqId"));
        auto reqId = reqDoc["reqId"].GetString();
        if (strcmp(reqId, "quit") == 0){
            logf("Recieved quit. Terminating connection.\n");
            break;
        }
        assert(reqDoc.HasMember("len"));
        auto reqLen = reqDoc["len"].GetInt();

        rapidjson::Document ackDoc;
        ackDoc.SetObject();
        ackDoc.AddMember("ACK", true, ackDoc.GetAllocator());
        SocketInterface::sendJson(connection, ackDoc);


        rapidjson::Document doc;
        doc.SetObject();
        char * recvJsonBuff = (char *)calloc(reqLen + 1, sizeof(char));
        if(!SocketInterface::recieveJson(connection, reqLen, recvJsonBuff, reqLen, doc)){
            logf("Failed to recieve data json");
            break;
        }
        if(!doc.HasMember("ekf")){
            logf("Missing EKF member in the data\n");
            logf("%s\n",recvJsonBuff);
        }
        assert(doc.HasMember("ekf"));
        assert(doc["ekf"].IsArray());
        int count = doc["ekf"].Size();

        rapidjson::Document respDoc;
        respDoc.SetObject();
        rapidjson::Document::AllocatorType & allocator = respDoc.GetAllocator();
        rapidjson::Value arr(rapidjson::kArrayType);

        for(int i=0; i<count; i++){
            assert(doc["ekf"][i].IsObject());
            rapidjson::Value & ekfObj = doc["ekf"][i];
            rapidjson::Value queryOutput;
            queryOutput.SetObject();
            if(strcmp(reqId, "f") == 0){
                SocketInterface::_f(ekfObj, queryOutput, allocator);
            }else if (strcmp(reqId, "h") == 0){
                SocketInterface::_h(ekfObj, queryOutput, allocator);
            }else if (strcmp(reqId, "m") == 0){
                SocketInterface::_m(ekfObj, queryOutput, allocator);
            }
            arr.PushBack(queryOutput, allocator);
        }
        respDoc.AddMember("ekf", arr, allocator);
        SocketInterface::sendJson(connection, respDoc);
        free(recvJsonBuff);
        reqDoc.GetAllocator().Clear();
        ackDoc.GetAllocator().Clear();
        respDoc.GetAllocator().Clear();
    }
    close(connection);
}
void SocketInterface::_f(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator){
    Ekf ekf;
    ekf.checkJson(ekfObj);
    ekf.ekfCheckJson(ekfObj);
    ekf.loadFromJson(ekfObj);
    ekf.ekfLoadFromJson(ekfObj);
    ekf.update_f();
    ekf.serializeToJson(outObj, allocator); // serialize ei
    ekf.ekfSerializeToJson(outObj, allocator); //serialize ekf
}

void SocketInterface::_h(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator){
    Ekf ekf;
    ekf.checkJson(ekfObj); // check if json has ei values // ekf.ekfCheckJson(ekfObj);
    ekf.loadFromJson(ekfObj); // check if json has ekf values
    ekf.ekfLoadFromJson(ekfObj);
    ekf.update_h();
    ekf.serializeToJson(outObj, allocator); // serialize ei
    ekf.ekfSerializeToJson(outObj, allocator); //serialize ekf
}

void SocketInterface::_m(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator){
    Ekf ekf;
    ekf.loadFromJson(ekfObj); // check if json has ekf values
    ekf.ekfLoadFromJson(ekfObj);
    ekf.serializeToJson(outObj, allocator); // serialize ei
    ekf.ekfSerializeToJson(outObj, allocator); //serialize ekf
}
