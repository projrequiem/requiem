from parse import *
import re
from utils.formatter import *
from inspect import currentframe, getframeinfo

PRIMITIVE_NUMBERS = {"uint64_t", "int64_t", "unsigned", "float", "double", "int", "uint8_t", "uint16_t", "uint32_t", 'int32_t', 'hrt_abstime'}


def parse_line(line):
    t = None
    var = None
    val = None
    if "Vector" in line:
        t, var = parse("{} {};", line)
    elif "const " in line: 
        t, var =  parse("const {} {};", line)
        t = 'const ' + t
    elif "<" in line:
        t1, t2, var =  parse("{}<{}>{};", line)
        t = "%s<%s>"%(t1, t2)
    else:
        t, var = parse("{} {};", line)
    
    t = t.strip()
    var = var.strip()
    return t, var
def _serializeAddMember(structJson, keyname, memberObj, allocator, tabs=0):
    output = insertTabs(tabs) + "{structObj}.AddMember(\"{keyname}\", {memberObj}, {allocator});\n"
    return output.format(structObj=structJson, keyname=keyname, memberObj=memberObj, allocator=allocator)

def _serializePrimitive(structObj, keyname, memberObj, allocator, tabs=0):
    output = ''
    output += insertTabs(tabs) + "if (isnan({memberObj})){{\n".format(memberObj=memberObj)
    output += _serializeAddMember(structObj, keyname, 'false', allocator, tabs=tabs+1)
    output += insertTabs(tabs) + "}else{\n"
    output += _serializeAddMember(structObj, keyname, memberObj, allocator, tabs=tabs+1)
    output += insertTabs(tabs) + "}\n"
    return output
def _serializeArray( outerJson, allocator, array, arrlen, varname, keyname=None, tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + "rapidjson::Value {array}(rapidjson::kArrayType);\n"
    output += insertTabs(tabs+1) + "for(int i = 0; i < {arrlen}; i++){{\n"
    output += insertTabs(tabs+2) + "{array}.PushBack({varname}[i], {allocator});\n"
    output += insertTabs(tabs+1) + "}}\n"
    output = output.format(allocator=allocator, array=array, arrlen=arrlen, varname=varname)
    if keyname is None:
        output += _serializeAddMember(outerJson, varname, array, allocator, tabs+1)
    else:
        output += _serializeAddMember(outerJson, keyname, array, allocator, tabs+1)
    output += insertTabs(tabs) + '}\n'
    return output

def _serializeVector( structObj, allocator, array, arrlen, varname, keyname=None, tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + "rapidjson::Value {array}(rapidjson::kArrayType);\n"
    output += insertTabs(tabs+1) + "for(int i = 0; i < {arrlen}; i++){{\n"
    output += insertTabs(tabs+2) + "{array}.PushBack({varname}(i), {allocator});\n"
    output += insertTabs(tabs+1) + "}}\n"
    output = output.format(structObj=structObj, allocator=allocator, array=array, arrlen=arrlen, varname=varname)
    if keyname is None:
        output += _serializeAddMember(structObj, varname, array, allocator, tabs=tabs+1)
    else:
        output += _serializeAddMember(structObj, keyname, array, allocator, tabs=tabs+1)
    output += insertTabs(tabs) + '}\n'
    return output

def _serializeMatrix( structObj, allocator, array, rowSize, colSize, varname, keyname=None, tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + "rapidjson::Value {array}(rapidjson::kArrayType);\n"
    output += insertTabs(tabs+1) + "for(int i = 0; i < {rowSize}; i++){{\n"
    output += insertTabs(tabs+2) + "for(int j = 0; j < {colSize}; j++){{\n"
    output += insertTabs(tabs+3) + "{array}.PushBack({varname}(i, j), {allocator});\n"
    output += insertTabs(tabs+2) + "}}\n"
    output += insertTabs(tabs+1) + "}}\n"
    output = output.format(structObj=structObj, allocator=allocator, array=array, rowSize=rowSize, colSize=colSize, varname=varname)
    if keyname is None:
        output += _serializeAddMember(structObj, varname, array, allocator, tabs=tabs+1)
    else:
        output += _serializeAddMember(structObj, keyname, array, allocator, tabs=tabs+1)
    output += insertTabs(tabs) + '}\n'
    return output

def _loadArray( structObj, arrlen, varname, keyname, getType, tabs=0):
    output = ''
    output += insertTabs(tabs) + "for(int i = 0; i < {arrlen}; i++){{\n"
    if getType == "Float" or getType == "Double":
        output += insertTabs(tabs+1) + "if({structObj}[\"{keyname}\"][i].IsBool()){{\n"
        output += insertTabs(tabs+2) + "{varname}[i] = NAN;\n"
        output += insertTabs(tabs+1) + "}}else {{\n\t"
    output += insertTabs(tabs+1) + "{varname}[i] = {structObj}[\"{keyname}\"][i].Get{getType}();\n"
    if getType == "Float" or getType == "Double":
        output += insertTabs(tabs+1) + "}}\n"
    output += insertTabs(tabs) + "}}\n"
    return output.format(structObj=structObj, arrlen=arrlen, varname=varname, keyname=keyname, getType=getType)
def _loadVector( structObj, arrlen, varname, keyname, tabs=0):
    output = ''
    output += insertTabs(tabs) + "for(int i = 0; i < {arrlen}; i++){{\n"
    output += insertTabs(tabs+1) + "{varname}(i) = {structObj}[\"{keyname}\"][i].GetFloat();\n"
    output += insertTabs(tabs) + "}}\n"
    return output.format(structObj=structObj, arrlen=arrlen, varname=varname, keyname=keyname)
def _loadMatrix( structObj, rowSize, colSize, varname, keyname, tabs=0):
    output = ''
    output += insertTabs(tabs) +"for(int i = 0; i < {rowSize}; i++){{\n"
    output += insertTabs(tabs+1) +"for(int j = 0; j < {colSize}; j++){{\n"
    output += insertTabs(tabs+2) +"{varname}(i, j) = {structObj}[\"{keyname}\"][i*{rowSize} + j].GetFloat();\n"
    output += insertTabs(tabs+1) +"}}\n"
    output += insertTabs(tabs) +"}}\n"
    return output.format(structObj=structObj, rowSize=rowSize, colSize=colSize, varname=varname, keyname=keyname)
def _loadMember(structObj, varname, keyname, dataType, tabs=0):
    return insertTabs(tabs) + "{varname} = {structObj}[\"{keyname}\"].Get{dataType}();\n".format(varname=varname, structObj=structObj, keyname=keyname, dataType=dataType)
def _loadValuePrimitive(structObj, varname, keyname, dataType, tabs=0):
    t = None
    if "int" == dataType or "int32_t" == dataType:
        t = "Int"
    elif "unsigned" == dataType or "uint8_t" == dataType or dataType == 'uint32_t' or dataType == 'uint16_t':
        t = "Uint"
    elif "int64_t" == dataType:
        t = "Int64"
    elif "uint64_t" == dataType or 'hrt_abstime' == dataType:
        t = "Uint64"
    elif dataType == 'float':
        t = "Float"
    elif dataType == 'double':
        t = "Double"
    elif dataType == 'bool':
        t = "Bool"
    else:
        exit('Unknown type: %s'%dataType)

    if t == "Float" or t == 'Double':
        output = ''
        output += insertTabs(tabs) + 'if ({structObj}["{keyname}"].IsBool()){{\n'.format(structObj=structObj, keyname=keyname)
        output += insertTabs(tabs+1) + "{varname} = NAN;\n".format(varname=varname)
        output += insertTabs(tabs) + "}else{\n"
        output += _loadMember(structObj, varname, keyname, t, tabs+1)
        output += insertTabs(tabs) + "}\n"
        return output
    else:
        return _loadMember(structObj, varname, keyname, t, tabs+1)

def serialize_line(t, var, tabs=0):
    output = ""
    if "<" in t:
        return output
    output += insertTabs(tabs) + "{\n"
    if "[" in var:
        arrlen = int(parse("{}[{}]", var)[1])
        varname = parse("{}[{}]", var)[0]
        output += _serializeArray("ekfObj", "allocator", "array"+varname, arrlen, varname, tabs=tabs+1)
    elif "Vector" in t:
        arrlen = int(parse("Vector{}f", t)[0])
        output += _serializeVector("ekfObj", "allocator", "array"+var, arrlen, var, tabs=tabs+1)
    elif "Dcmf" in t:
        output += _serializeMatrix("ekfObj", "allocator", "array"+var, 3, 3, var, tabs=tabs+1)
    elif "SquareMatrix" in t:
        s = int(parse("SquareMatrix{}f", t)[0])
        output += _serializeMatrix("ekfObj", "allocator", "array"+var, s, s, var, tabs=tabs+1)
    elif "Matrix" in t:
        s = int(parse("Matrix{}f", t)[0])
        output += _serializeMatrix("ekfObj", "allocator", "array"+var, s, s, var, tabs=tabs+1)
    elif "Quatf" in t:
        output += _serializeVector("ekfObj", "allocator", "array"+var, 4, var, tabs=tabs+1)
    elif t in PRIMITIVE_NUMBERS or t == 'bool':
        output += _serializePrimitive("ekfObj", var, var, 'allocator', tabs=tabs+1)
    output += insertTabs(tabs) + "}\n"
    return output

def assert_line(t, var):
    if "[" in var:
        varname = parse("{}[{}]", var)[0]
        output = "assert(ekfObj.HasMember(\"%s\"));\n"%(varname)
        output += "assert(ekfObj[\"%s\"].IsArray());"%(varname)
    else:
        output = "assert(ekfObj.HasMember(\"%s\"));\n"%(var)
        if "<" in t:
            return output
        elif "Vector" in t:
            output += "assert(ekfObj[\"%s\"].IsArray());"%(var)
        elif "Matrix" in t:
            output += "assert(ekfObj[\"%s\"].IsArray());"%(var)
        elif "Dcmf" in t:
            output += "assert(ekfObj[\"%s\"].IsArray());"%(var)
        elif "int" == t or 'int32_t' == t:
            output += "assert(ekfObj[\"%s\"].IsInt());"%(var)
        elif "int64_t" == t :
            output += "assert(ekfObj[\"%s\"].IsInt64());"%(var)
        elif "unsigned" == t or t == "uint8_t" or t =='uint32_t' or t == 'uint16_t':
            output += "assert(ekfObj[\"%s\"].IsUint());"%(var)
        elif "uint64_t" == t  or 'hrt_abstime' == t:
            output += "assert(ekfObj[\"%s\"].IsUint64());"%(var)
        elif "float" == t:
            output += "assert(ekfObj[\"%s\"].IsFloat() || ekfObj[\"%s\"].IsBool());"%(var, var)
        elif "double" == t:
            output += "assert(ekfObj[\"%s\"].IsDouble() || ekfObj[\"%s\"].IsBool());"%(var, var)
        elif "bool" == t:
            output += "assert(ekfObj[\"%s\"].IsBool());"%(var)
        else:
            print("WARNING:Unhandled variable: %s \t %s"%(t, var))
            frameinfo = getframeinfo(currentframe())
            # print("\t\t%s %s"%(frameinfo.filename, frameinfo.lineno))
            return ''
    output+='\n'
    return output

def load_line(t, var, tabs=0):
    output = insertTabs(tabs) + "{\n"
    if "<" in t:
        return ''
    if "const" in t:
        return ''
    if "[" in var:
        varname = parse("{}[{}]", var)[0]
        s = int(parse("{}[{}]", var)[1])
        getType = None
        if "int" == t or "int32_t" == t:
            getType = 'Int'
        elif "unsigned" == t or "uint8_t" == t:
            getType = 'UInt'
        elif "int64_t" == t:
            getType = 'Int64'
        elif "uint64_t" == t or 'hrt_abstime' == t:
            getType = 'UInt64'
        elif "float" == t:
            getType = 'Float'
        elif "double" == t:
            getType = 'Double'
        elif t == 'bool':
            getType = 'Bool'
        if getType is not None:
            output += _loadArray("ekfObj", s, varname=varname, keyname=varname, getType=getType, tabs=tabs+1)
    elif "Vector" in t:
        s = int(parse("Vector{}f", t)[0])
        output += _loadVector("ekfObj", s, var, var, tabs=tabs+1)
    elif "SquareMatrix" in t:
        s = int(parse("SquareMatrix{}f", t)[0])
        output += _loadMatrix("ekfObj", s, s, var, var, tabs=tabs+1)
    elif "Matrix" in t:
        s = int(parse("Matrix{}f", t)[0])
        output += _loadMatrix("ekfObj", s, s, var, var, tabs=tabs+1)
    elif "Dcmf" in t:
        output +=_loadMatrix("ekfObj", 3, 3, var, var, tabs=tabs+1)
    elif t in PRIMITIVE_NUMBERS or t == 'bool':
        output += _loadValuePrimitive('ekfObj', var, var, t, tabs+1)
    else:
        print("Not handled %s, %s"%(t, var))
    if len(output.strip()) == 0:
        return ""
    output += insertTabs(tabs)+"}\n"
    return output

def format_struct(t, var, struct, innerObj='structObj', outerObj='ekfObj', tabs=0, allocator='allocator'):
    if '[' in var:
        varname = parse("{}[{}]", var)[0]
        s = int(parse("{}[{}]", var)[1])
        return serialize_array_struct(t, varname, varname, struct, s, outerObj, tabs, allocator)
    output = insertTabs(tabs) + '{\n'
    output += _format_struct_helper(t, var, struct, innerObj, allocator, tabs=tabs+1)
    output += insertTabs(tabs+1) +'{outerObj}.AddMember("{keyname}", {innerObj}, {allocator});\n'.format(
        outerObj=outerObj, keyname=var, innerObj=innerObj, allocator=allocator)
    output += insertTabs(tabs) +'}\n'
    return output

def serialize_array_struct(t, var, key, struct, count, outerObj='ekfObj', tabs=0, allocator='allocator'):
    output = insertTabs(tabs) + '{\n'
    output += insertTabs(tabs+1) + 'rapidjson::Value buffArray(rapidjson::kArrayType);\n'
    output += insertTabs(tabs+1) + 'for(int index = 0; index < {count}; index++){{\n'.format(count=count)
    output += insertTabs(tabs+2) + '{datatype} & elem = {varname}[index];\n'.format(datatype=t, varname=var)
    output += _format_array_struct(t, 'elem', struct, outerObj='buffArray', tabs=tabs+2)
    output += insertTabs(tabs+2) + '}\n'
    output += insertTabs(tabs+2) + '{outerObj}.AddMember("{keyword}", buffArray, {allo});'.format(
        outerObj=outerObj, keyword=key, allo=allocator)
    output += insertTabs(tabs) + '}\n'
    return output

def _format_array_struct(t, var, struct, innerObj='structObj', outerObj='ekfObj', tabs=0):
    output = insertTabs(tabs) + '{\n'
    output += _format_struct_helper(t, var, struct, innerObj, 'allocator', tabs=tabs+1)
    output += insertTabs(tabs+1) +'{outerObj}.PushBack({innerObj}, allocator);\n'.format(outerObj=outerObj, innerObj=innerObj)
    output += insertTabs(tabs) +'}\n'
    return output

def _format_struct_helper(t, var, struct, innerObj, allocator, tabs):
    output = ''
    output += insertTabs(tabs) + 'rapidjson::Value {innerObj}(rapidjson::kObjectType);\n'.format(innerObj=innerObj)
    #output += 'rapidjson::Document structObj;\n'
    output += insertTabs(tabs) + '{innerObj}.SetObject();\n'.format(innerObj=innerObj)
    if "~serialize" in struct[t]:
        output += struct[t]["~serialize"]%(var)
    else:
        for k,v in struct[t].items():
            if "Vector" in v:
                arrlen = int(parse("Vector{}f", v)[0])
                output += _serializeVector(innerObj, allocator, "array"+var, arrlen, var+'.'+k, k, tabs=tabs)
            elif "SquareMatrix" in v:
                arrlen = int(parse("SquareMatrix{}f", v)[0])
                output += _serializeMatrix(innerObj, allocator, "array"+var, arrlen, arrlen, var+'.'+k, k, tabs=tabs)
            elif "Matrix" in v:
                arrlen = int(parse("Matrix{}f", v)[0])
                output += _serializeMatrix(innerObj, allocator, "array"+var, arrlen, arrlen, var+'.'+k, k, tabs=tabs)
            elif "Quatf" in v:
                output += _serializeVector(innerObj, allocator, "array"+var, 4, var+'.'+k, k, tabs=tabs)
            elif "Dcmf" in v:
                output += _serializeMatrix(innerObj, allocator, "array"+var, 3, 3, var+'.'+k, k, tabs=tabs)
            elif "[" in v:
                arrlen = int(parse("{}[{}]", v)[1])
                output += _serializeArray(innerObj, allocator, "array"+var, arrlen, var+'.'+k, k, tabs=tabs)
            elif v in PRIMITIVE_NUMBERS or v == 'bool':
                output += _serializePrimitive(innerObj, k, var+"."+k, allocator, tabs=tabs)
    return output

def assert_struct(t, var, struct, outerObj='ekfObj', tabs=0):
    output = insertTabs(tabs)+"{\n"
    output += insertTabs(tabs+1)+"assert(%s[\"%s\"].IsObject());\n"%(outerObj, var)
    structObj =  "%s[\"%s\"]"%(outerObj,var)
    output += _assert_struct_helper(t, struct, structObj, tabs+1)
    output += insertTabs(tabs)+"}\n"
    return output

def _assert_struct_helper(t, struct, structObj, tabs=0):
    output = ''
    for k,tv in struct[t].items():
        if "~" in k:
            continue
        if "const" in tv:
            continue
        if "Vector" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "SquareMatrix" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "Matrix" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "Dcmf" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "Quatf" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "[" in tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsArray());\n"%(structObj, k)
        elif "int" == tv or "int32_t" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsInt());\n"%(structObj, k)
        elif "int64_t" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsInt64());\n"%(structObj, k)
        elif "unsigned" == tv or "uint8_t" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsUint());\n"%(structObj, k)
        elif "uint64_t" == tv or 'hrs_abstime' == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsUint64());\n"%(structObj, k)
        elif "float" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsFloat() || %s[\"%s\"].IsBool());\n"%(structObj, k, structObj, k)
        elif "double" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsDouble() || %s[\"%s\"].IsBool());\n"%(structObj, k, structObj, k)
        elif "bool" == tv:
            output += insertTabs(tabs)+"assert(%s[\"%s\"].IsBool());\n"%(structObj, k)
    return output

def load_struct(t, var, struct, tabs=0):
    if '[' in var:
        varname = parse("{}[{}]", var)[0]
        return load_array_struct(t, varname, varname, struct, outerObj='ekfObj', tabs=tabs)

    output = insertTabs(tabs) + "{\n"
    output += insertTabs(tabs+1) + "rapidjson::Value& structObj = ekfObj[\"%s\"];\n"%var
    output += _load_struct_helper('structObj', t, var, struct, tabs+1)
    output += "}\n"
    return output
def load_array_struct(t, var, key, struct, outerObj='ekfObj', tabs=0):
    output = ''
    output += insertTabs(tabs) + '{\n'
    output += insertTabs(tabs+1) + 'auto & buffArray = {outerObj}["{key}"];\n'.format(outerObj=outerObj, key=key)
    output += insertTabs(tabs+1) + 'for(unsigned int index = 0; index < buffArray.Size(); index++){\n'
    output += insertTabs(tabs+2) + 'auto & elem = buffArray[index];\n'.format(outerObj=outerObj, key=key)
    output += _load_struct_helper('elem', t, var+'[index]', struct, tabs=tabs+2)
    output += insertTabs(tabs+1) + '}\n'
    output += insertTabs(tabs) + '}\n'
    return output
def _load_struct_helper(outerStruct, t, var, struct, tabs):
    output = ''
    if "~load" in struct[t]:
        output += insertTabs(tabs+1) + struct[t]["~load"]%(var)
    else:
        for k,tv in struct[t].items():
            if "const" in tv:
                continue
            if "Vector" in tv:
                s = int(parse("Vector{}f", tv)[0])
                output += _loadVector(outerStruct, s, var+"."+k, k, tabs=tabs+1)
            elif "SquareMatrix" in tv:
                arrlen = int(parse("SquareMatrix{}f", tv)[0])
                output += _loadMatrix(outerStruct, arrlen, arrlen, var+"."+k, k, tabs=tabs+1)
            elif "Matrix" in tv:
                arrlen = int(parse("Matrix{}f", tv)[0])
                output += _loadMatrix(outerStruct, arrlen, arrlen, var+"."+k, k, tabs=tabs+1)
            elif "Dcmf" in tv:
                output += _loadMatrix(outerStruct, 3, 3, var+"."+k, k, tabs=tabs+1)
            elif "Quatf" in tv:
                output += _loadVector(outerStruct, 4, var+"."+k, k, tabs=tabs+1)
            elif "[" in tv:
                array_type = parse("{}[{}]", tv)[0].strip()
                s = int(parse("{}[{}]", tv)[1])
                dataType = None
                if "bool" == array_type:
                    dataType = 'Bool'
                elif "float" == array_type:
                    dataType = 'Float'
                elif "int" == array_type or "int32_t" == array_type:
                    dataType = 'Int'
                else:
                    print("Array inside object is not handled: %s"%array_type)
                    exit("ERROR")
                output += _loadArray(outerStruct, s, var+"."+k, k, dataType,tabs=tabs+1)
            elif tv in PRIMITIVE_NUMBERS or "bool" == tv :
                output += _loadValuePrimitive(outerStruct, var+'.'+k, k, tv, tabs+1)
    return output

def extract_content(file_name, parse_format, mask):
    content = ''
    with open(file_name, 'r') as f:
        string = f.read()
        # extract contents of the paramters struct
        chunks = list(parse(parse_format, string))
        for i in range(len(chunks)):
            if mask[i]:
                ch = remove_comment_block(chunks[i])
                ch = remove_nest(ch)
                ch = remove_comments(ch)
                ch = re.sub('[\n\t]+', '', ch)
                ch = remove_func(ch)
                ch = remove_ass(ch)
                content += ch
    return content