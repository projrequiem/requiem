from utils.formatter import *
from utils.parser import _serializePrimitive, _serializeVector, _loadArray,_loadValuePrimitive, _loadArray
from parse import parse

def type_alphaFilter(datatype):
    alphaType = {}
    alphaType['_cutoff_freq'] = 'float'
    alphaType['_alpha'] = 'float'
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        alphaType['_filter_state'] = ['float' for _ in range(arrlen)]
    elif datatype == 'float':
        alphaType['_filter_state'] = 'float'
    return alphaType

def serialize_AlphaFilter(outerJson, alphaJson, datatype, alphaName, allocator,  tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'rapidjson::Value {alphaJson}(rapidjson::kObjectType);\n'
    output += insertTabs(tabs+1) + '{alphaJson}.AddMember("_cutoff_freq", {alphaName}.getCutoffFreq(), {allocator});\n'
    output += insertTabs(tabs+1) + '{alphaJson}.AddMember("_alpha", {alphaName}.getAlpha(), {allocator});\n'
    output = output.format(alphaJson=alphaJson, alphaName=alphaName, allocator=allocator)
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        output += insertTabs(tabs+1) + 'auto & fs = {alphaName}.getState();\n'.format(alphaName=alphaName)
        output += _serializeVector( alphaJson, allocator, alphaName+'_filter_state', arrlen, 'fs', keyname='_filter_state', tabs=tabs+1)
    elif datatype == 'float':
        # Assume float
        output += _serializePrimitive(alphaJson, '_filter_state', alphaName+'.getState()', allocator, tabs=tabs+1)
    else:
        exit("ERROR: Unexpected datatype encountered while parse gen serialization of AlphaFilter variable {a}: {d}".format(a=alphaName, d=datatype))
    output += insertTabs(tabs+1) + '{oj}.AddMember("{an}", {aj}, {a});\n'.format(oj=outerJson, an=alphaName, aj=alphaJson, a=allocator)
    output += insertTabs(tabs) + '}\n'
    return output

def assert_AlphaFilter(outerJson, alphaName, datatype, tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'assert({oj}.HasMember("{an}"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"].IsObject());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"].HasMember("_cutoff_freq"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_cutoff_freq"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"].HasMember("_alpha"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_alpha"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{an}"].HasMember("_filter_state"));\n'
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].IsArray());\n'
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].Size() == {arrlen});\n'
        output += insertTabs(tabs+1) + 'for(int assertIndex = 0; assertIndex < {arrlen}; assertIndex++){{\n'
        output += insertTabs(tabs+2) + 'assert({oj}["{an}"]["_filter_state"][assertIndex].IsFloat());\n'
        output += insertTabs(tabs+1) + '}}\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, an=alphaName, arrlen=arrlen)
    elif datatype == 'float':
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].IsFloat());\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, an=alphaName)
    exit("ERROR: Unexpected datatype encountered while parsing asserting for AlphaFilter variable {an}: {d}".format(an=alphaName, d=datatype))


def load_AlphaFilter(outerJson, datatype, alphaName, keyname,  tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'auto & afJson = {oj}["{k}"];\n'
    output += insertTabs(tabs+1) + '{an}.setCutoff(afJson["_cutoff_freq"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{an}.setAlpha(afJson["_alpha"].GetFloat());\n'
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        output += insertTabs(tabs+1) + '{dt} tmpVec;\n'
        output += insertTabs(tabs+1) + 'for(int afIndex = 0; afIndex < {al}; afIndex++){{\n'
        output += insertTabs(tabs+2) + 'tmpVec(afIndex) = afJson["_filter_state"][afIndex].GetFloat();\n'
        output += insertTabs(tabs+1) + '}}\n'
        output += insertTabs(tabs+1) + '{an}.setState(tmpVec);\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, k=keyname, an=alphaName, dt=datatype, al=arrlen)
    elif datatype == 'float':
        output += insertTabs(tabs+1) + '{an}.setState(afJson["_filter_state"].GetFloat());\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, k=keyname, an=alphaName)
    exit("ERROR: Unexpected datatype encountered while parse load AlphaFilter variable {an}: {d}".format(an=alphaName, d=datatype))