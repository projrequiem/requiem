#include <iostream>
#include "ecl_ekf/ekf.h"
#include "interface/Interface.hpp"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>

int main(){
    uint16_t port = 33344;
    auto si = SocketInterface(port);
    si.run();
    return 0;
}
