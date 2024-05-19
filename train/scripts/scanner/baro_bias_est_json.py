from utils.formatter import *
import utils.parser as utpa 
import alphafilter_json as afj
from parse import parse

# MAY NOT NEED THIS
def serialize_BaroBiasEst(outerJson, estJson, estName, struct, allocator,  tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'rapidjson::Value {estJson}(rapidjson::kObjectType);\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_state", {estName}.getBias(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_state_max", {estName}.getStateMax(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_state_drift_rate", {estName}.getStateDriftRate(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_dt", {estName}.getDt(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_gate_size", {estName}.getGateSize(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_state_var", {estName}.getBiasVar(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_process_var", {estName}.getProcessVar(), {allocator});\n'
    output += insertTabs(tabs+1) + '{estJson}.AddMember("_state_var_max", {estName}.getStateVarMax(), {allocator});\n'
    output = output.format(estJson=estJson, estName=estName, allocator=allocator)

    # Status: _status
    output += utpa.format_struct('status', '_status', struct, innerObj='statusJson', outerObj=estJson, tabs=tabs+1, allocator='allocator')

    # Alpha Filter: _signed_innov_test_ratio_lpf
    afj.serialize_AlphaFilter(estJson, 'sitrAF', 'float', '_signed_innov_test_ratio_lpf', allocator,  tabs=tabs+1)

    output += insertTabs(tabs+1) + '{oj}.AddMember("{en}", {ej}, {a});\n'.format(oj=outerJson, en=estName, ej=estJson, a=allocator)
    output += insertTabs(tabs) + '}\n'
    return output

def type_BaroBiasEst(datatype):
    baroType = {}
    baroType['_state'] = 'float'
    baroType['_state_max'] = 'float'
    baroType['_state_drift_rate'] = 'float'
    baroType['_dt'] = 'float'
    baroType['_gate_size'] = 'float'
    baroType['_state_var'] = 'float'
    baroType['_process_var'] = 'float'
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        baroType['_filter_state'] = ['float' for _ in range(arrlen)]
    elif datatype == 'float':
        baroType['_filter_state'] = 'float'
    return baroType

baroBiasEstType = {
        "_state": "float",
        "_state_max": "float",
        "_state_drift_rate": "float",
        "_dt": "float",
        "_gate_size": "float",
        "_state_var":  "float",
        "_process_var":  "float",
        "_state_var_max":  "float",
        "_signed_innov_test_ratio_lpf":{
            "_cutoff_freq": "float",
            "_alpha": "float",
            "_filter_state": "float"
        },
        "_status":{
            "bias":"float",
            "bias_var":"float",
            "innov":"float",
            "innov_var":"float",
            "innov_test_ratio":"float"
        }
    }


def assert_BaroBiasEst(outerJson, estName, datatype, tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'assert({oj}.HasMember("{en}"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].IsObject());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_state"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_state"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_state_max"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_state_max"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_state_drift_rate"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_state_drift_rate"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_dt"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_dt"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_gate_size"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_gate_size"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_state_var"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_state_var"].IsFloat());\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"].HasMember("_process_var"));\n'
    output += insertTabs(tabs+1) + 'assert({oj}["{en}"]["_process_var"].IsFloat());\n'
    if 'Vector' in datatype:
        arrlen = int(parse("Vector{}f", datatype)[0])
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].IsArray());\n'
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].Size() == {arrlen});\n'
        output += insertTabs(tabs+1) + 'for(int assertIndex = 0; assertIndex < {arrlen}; assertIndex++){{\n'
        output += insertTabs(tabs+2) + 'assert({oj}["{an}"]["_filter_state"][assertIndex].IsFloat());\n'
        output += insertTabs(tabs+1) + '}}\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, an=estName, arrlen=arrlen)
    elif datatype == 'float':
        output += insertTabs(tabs+1) + 'assert({oj}["{an}"]["_filter_state"].IsFloat());\n'
        output += insertTabs(tabs) + '}}\n'
        return output.format(oj=outerJson, an=estName)
    exit("ERROR: Unexpected datatype encountered while parsing asserting for AlphaFilter variable {an}: {d}".format(an=estName, d=datatype))


def load_BaroBiasEst(outerJson, estName, keyname,  tabs=0):
    output = insertTabs(tabs) + '{{\n'
    output += insertTabs(tabs+1) + 'auto & estJson = {oj}["{k}"];\n'
    output += insertTabs(tabs+1) + '{estName}.setBias(estJson["_state"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setStateMax(estJson["_state_max"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setStateDriftRate(estJson["_state_drift_rate"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setDt(estJson["_dt"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setGateSize(estJson["_gate_size"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setBiasVar(estJson["_state_var"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setProcessVar(estJson["_process_var"].GetFloat());\n'
    output += insertTabs(tabs+1) + '{estName}.setStateVarMax(estJson["_state_var_max"].GetFloat());\n'
    output = output.format(oj=outerJson, k=keyname, estName=estName)
    output += insertTabs(tabs+1) + 'BaroBiasEstimator::status estStatus;\n'
    output += utpa._load_struct_helper('estJson', 'status', 'estStatus', struct, tabs=tabs+1)
    output += insertTabs(tabs+1) + '{estName}.setStatus(estStatus);\n'
    output += insertTabs(tabs+1) + 'AlphaFilter<float> estAF;\n'
    output += utpa._load_AlphaFilter('estJson', 'float', 'estAF', '_signed_innov_test_ratio_lpf',tabs=tabs+1)
    output += insertTabs(tabs+1) + '{estName}.setSignedInnovTestRatio(estAF);\n'
    output += insertTabs(tabs) + '}\n'