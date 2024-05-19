#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
#include "ecl_ekf/ekf.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>

#define RECIEVE_BUFF_LEN 4048
static const char* kTypeNames[] = 
    { "Null", "False", "True", "Object", "Array", "String", "Number" };

#ifdef NODEBUG
    #define logf(...) 
#else
    #define logf(...) printf(__VA_ARGS__)
#endif

class SocketInterface
{
    public:
        // listens for clients
        SocketInterface(uint16_t port);
        void run();
        static void worker(int conn);
        static bool recieveJson(int connection, int readLen, char * buffer, int buffLen, rapidjson::Document & jsonObj);
        static void sendJson(int conn, rapidjson::Document & doc);
        static bool parseJson(char * buffer, rapidjson::Document & doc);
        static void _f(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator);
        static void _h(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator);
        static void _m(rapidjson::Value & ekfObj, rapidjson::Value & outObj, rapidjson::Document::AllocatorType & allocator);
    private:
        struct sockaddr_in address;
        int sock;
};