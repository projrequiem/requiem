#!/bin/python3
import argparse
from utils.formatter import insertTabs

bufferObj = {
    "_head": "uint8_t",
    "_tail": "uint8_t",
    "_size": "uint8_t",
    "_first_write": "bool",
    "_buffer": "datatype"
}

def buffer_serialize(outerObj, bufferObj, varname, pointer, allocator, datatype, formatFunc, struct, tabs=0):
    output = ''
    if pointer == '->':
        output += insertTabs(tabs) +'if({varname} != nullptr){{\n'
    else:
        output += insertTabs(tabs) +'{{\n'
    output += insertTabs(tabs+1) + 'rapidjson::Value {bufferObj}(rapidjson::kObjectType);\n'
    output += insertTabs(tabs+1) + '{bufferObj}.AddMember("_head", {varname}{pointer}get_head(), {allocator});\n'
    output += insertTabs(tabs+1) + '{bufferObj}.AddMember("_tail", {varname}{pointer}get_tail(), {allocator});\n'
    output += insertTabs(tabs+1) + '{bufferObj}.AddMember("_size", {varname}{pointer}get_length(), {allocator});\n'
    output += insertTabs(tabs+1) + '{bufferObj}.AddMember("_first_write", {varname}{pointer}get_first_write(), {allocator});\n'
    output += insertTabs(tabs+1) + 'rapidjson::Value buffArray(rapidjson::kArrayType);\n'
    output += insertTabs(tabs+1) + 'for(int index = 0; index < {varname}{pointer}get_length(); index++){{\n'
    output += insertTabs(tabs+2) + '{datatype} & elem = {varname}{pointer}get_data(index);\n'
    output = output.format(bufferObj=bufferObj, varname=varname, pointer=pointer, allocator=allocator, datatype=datatype)

    output += formatFunc(datatype, 'elem', struct, outerObj='buffArray', tabs=tabs+2)
    output += insertTabs(tabs+2) + '}'

    # Elem struct string here
    output += insertTabs(tabs+1) + '{bufferObj}.AddMember("_buffer", buffArray, {allocator});\n'.format(bufferObj=bufferObj, allocator=allocator, )
    output += insertTabs(tabs+1) + '{outerObj}.AddMember("{varname}", {bufferObj}, {allocator});\n'.format(
        outerObj=outerObj, varname=varname, bufferObj=bufferObj, allocator=allocator)
    output += insertTabs(tabs) +'}\n'
    return output

def buffer_load(outerObj, bufferObj, varname, pointer, datatype, loadFunc, struct, tabs= 0):
    output = ""
    output += insertTabs(tabs) +'if({outerObj}.HasMember("{varname}")){{\n'
    output += insertTabs(tabs+1) +'rapidjson::Value & {bufferObj} = {outerObj}["{varname}"];\n'
    if pointer == '->':
        output += insertTabs(tabs+1) + 'if({varname}==nullptr){{\n'
        output += insertTabs(tabs+2) + '{varname} = new RingBuffer<{datatype}>({bufferObj}["_size"].GetUint());\n'
        output += insertTabs(tabs+1) + '}}\n'
    output += insertTabs(tabs+1) +'{varname}{pointer}allocate({bufferObj}["_size"].GetUint());\n'
    output += insertTabs(tabs+1) +'{varname}{pointer}set_head({bufferObj}["_head"].GetUint());\n'
    output += insertTabs(tabs+1) +'{varname}{pointer}set_tail({bufferObj}["_tail"].GetUint());\n'
    output += insertTabs(tabs+1) +'{varname}{pointer}set_first_write({bufferObj}["_first_write"].GetBool());\n'
    output += insertTabs(tabs+1) +'auto & array = {bufferObj}["_buffer"];\n'
    output += insertTabs(tabs+1) +'for(unsigned int index = 0; index < std::min(array.Size(),{bufferObj}["_size"].GetUint()) ; index++){{\n'
    output += insertTabs(tabs+2) +'{datatype} elem;\n'
    output = output.format(outerObj=outerObj, bufferObj=bufferObj, varname=varname, pointer=pointer, datatype=datatype)

    output += loadFunc('array[index]', datatype, 'elem', struct, tabs+2)
    output += insertTabs(tabs+2) +'{varname}{pointer}set_data(elem, index);\n'.format(varname=varname, pointer=pointer)
    output +=insertTabs(tabs+1) +'}'
    output += insertTabs(tabs) +'}'
    return output

def buffer_assert(outerObj, bufferObj,  varname, datatype, assertFunc, struct, tabs=0):
    output = insertTabs(tabs) + 'if({outerObj}.HasMember("{varname}")){{'
    output += insertTabs(tabs+1) + 'rapidjson::Value & {bufferObj} = {outerObj}["{varname}"];\n'
    output += insertTabs(tabs+1) +'assert({bufferObj}["_size"].IsUint());\n'
    output += insertTabs(tabs+1) +'assert({bufferObj}["_head"].IsUint());\n'
    output += insertTabs(tabs+1) +'assert({bufferObj}["_tail"].IsUint());\n'
    output += insertTabs(tabs+1) +'assert({bufferObj}["_first_write"].IsBool());\n'
    output += insertTabs(tabs+1) +'assert({bufferObj}["_buffer"].IsArray());\n'
    output += insertTabs(tabs+1) +'auto & array = {bufferObj}["_buffer"];\n'
    output += insertTabs(tabs+1) +'for(unsigned int index = 0; index < array.Size(); index++){{\n'
    output += insertTabs(tabs+2) +'assert({bufferObj}["_buffer"][index].IsObject());\n'
    output = output.format(bufferObj=bufferObj, outerObj=outerObj, varname=varname)

    output += assertFunc(datatype, struct, '{bufferObj}["_buffer"][index]'.format(bufferObj=bufferObj), tabs=tabs+2)
    output += insertTabs(tabs+1) +'}'
    output += insertTabs(tabs) +'}'
    return output

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Generate RingBuffer.json',
                        description = 'Create template json for RingBuffer to handle different data types',
                        epilog = '')
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory")
    args = parser.parse_args()

    # Construct ~serialize template
    pass