from parse import *
import re
import json
import glob
import os
import argparse
import gen_buffer_json as bufferParser
import alphafilter_json as afParser
import yaw_estimator_json as yawParser
import gen_struct_json as unionParser 
import utils.formatter as utfo
import  utils.parser as utpa
from inspect import currentframe, getframeinfo

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


def generate_addon_file(struct, union, content, include, serialize_func_name, assert_func_name, load_func_name, output_file, blacklist=[]):
    serialize_output = ''
    assert_output = ''
    load_output = ''
    nameToType = {}
    for line in content.split(";"):
        if len(line.strip()) == 0:
            continue
        t= None
        var = None
        try:
            t, var = utpa.parse_line(line+";")
        except Exception as e:
            print("Not parseable: %s"%(line) )
            continue
        
        if t in blacklist :
            continue
        if "<" in t:
            if ">" in t:
                outerType, elemType = parse("{}<{}>", t.strip())
                if outerType == 'RingBuffer' and elemType in struct:
                    varname = var.strip()
                    pointer = '.'
                    if var[0] == '*':
                        varname = varname[1:]
                        pointer = '->'
                    nameToType[varname] = bufferParser.bufferObj.copy()
                    nameToType[varname]['_buffer'] = [elemType for _ in range(12)]
                    serialize_output += bufferParser.buffer_serialize(
                        outerObj='ekfObj', bufferObj=elemType+'_buffer', varname=varname,
                        pointer=pointer, allocator='allocator', datatype=elemType, formatFunc=utpa._format_array_struct , struct=struct, tabs=1)
                    load_output += bufferParser.buffer_load(
                        'ekfObj', elemType+'_buffer', varname, pointer, elemType, utpa._load_struct_helper, struct, tabs= 1)
                    assert_output += bufferParser.buffer_assert(
                        'ekfObj', elemType+'_buffer', varname, elemType, utpa._assert_struct_helper, struct, tabs= 1)
                if outerType == 'AlphaFilter':
                    nameToType[var.strip()] = afParser.type_alphaFilter(elemType)
                    serialize_output += afParser.serialize_AlphaFilter('ekfObj', elemType+"AF", elemType, var.strip(), 'allocator',  1)
                    load_output += afParser.load_AlphaFilter('ekfObj', elemType, var.strip(), var.strip(), 1)
                    assert_output += afParser.assert_AlphaFilter('ekfObj', var.strip(), elemType, 1)
            else:
                print("WARNING: Not handled: "+line)
                continue
        elif t in struct:
            nameToType[var] = t
            serialize_output += utpa.format_struct(t,var,struct, tabs=1)
            assert_output += utpa.assert_struct(t,var,struct)
            load_output += utpa.load_struct(t,var,struct)
        elif t in union:
            nameToType[var] = t
            serialize_output += unionParser.union_generate_serialize('ekfObj', var, union[t], 'flags', 'allocator', tabs=1)
            assert_output += unionParser.union_generate_assert('ekfObj', var, union[t], 'flags', tabs=1)
            load_output += unionParser.union_generate_load('ekfObj', var, union[t], 'flags', tabs=1)
        else:
            fl = utpa.serialize_line(t, var)
            if fl != "":
                if '[' in var:
                    varname, arrlen = parse("{}[{}]", var)
                    nameToType[varname] = t+"["+arrlen+"]"
                else:
                    nameToType[var] = t
            # For serializing params as json
            serialize_output += fl
            # For checking the validity of json
            assert_output += "\t"+utpa.assert_line(t, var)
            # For loading json
            load_output += utpa.load_line(t, var) 

    # indent the content
    #serialize_output = re.sub('\n', '\n\t\t', serialize_output)
    serialize_output = serialize_func_name + serialize_output + '\n}\n'

    #assert_output = re.sub('\n', '\n\t\t', assert_output)
    assert_output = assert_func_name + assert_output + '\n}\n'

    #load_output = re.sub('\n', '\n\t\t', load_output)
    load_output = load_func_name + load_output + '\n}\n'

    # For loading json for param
    addon_str = include + serialize_output + assert_output + load_output
    with open(os.path.join(output_dir ,output_file+".cpp"),"w") as f:
        f.write(addon_str)
    return nameToType

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Generate unique IDs for each field from a log',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, default=None, help="Input direcotry of where the header files are")
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory")
    args = parser.parse_args()

    dump_output = ''
    check_output = ''
    load_output = ''

    struct = {}
    union = {}
    struct_dir = args.input
    output_dir = args.output
    script_dir = os.path.dirname(os.path.realpath(__file__))
    if args.input is None:
        struct_dir = os.path.join(script_dir,'struct')
    if args.output is None:
        output_dir = os.path.join(script_dir,'output')
    
    for s in glob.glob(os.path.join(struct_dir, "*.json")):
        with open(s, 'r') as f:
            jobj = json.load(f)
            if '~union' in jobj:
                union[os.path.basename(s).split('.')[0]] = jobj
            else:
                struct[os.path.basename(s).split('.')[0]] = jobj
    
    nameToType = dict()

    common_include = '#include <rapidjson/document.h>\n#include <rapidjson/writer.h>\n#include <rapidjson/stringbuffer.h>\n#include <rapidjson/prettywriter.h>\n#include <rapidjson/filewritestream.h>\n#include <rapidjson/filereadstream.h>\n'
    if True:
        ei_include = '#include "estimator_interface.h"\n' + common_include
        ei_parse_format = "{}class EstimatorInterface{}{{\npublic:{}\nprotected:{}\nprivate:{}\n}};{}"
        ei_mask = [False, False, False,True,True, False]
        ei_content = utpa.extract_content('headers/estimator_interface.h', ei_parse_format, ei_mask)
        ei_load_func_name = "void EstimatorInterface::loadFromJson(rapidjson::Value & ekfObj){\n"
        ei_serialize_func_name = "void EstimatorInterface::serializeToJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){\n"
        ei_assert_func_name = "void EstimatorInterface::checkJson(rapidjson::Value & ekfObj){\n"
        n2t = generate_addon_file(struct, union, ei_content, ei_include, ei_serialize_func_name, ei_assert_func_name, ei_load_func_name, 'ei_addon')
        nameToType.update(n2t)

    if True:
        print("Parsing EKF file")
        ekf_include = '#include "ekf.h"\n' + common_include
        ekf_parse_format = "{}class Ekf final : public EstimatorInterface{}{{\npublic:{}\nprivate:{}\n}};{}"
        ekf_mask = [False,False, True, True, False]
        ekf_content = utpa.extract_content('headers/ekf.h', ekf_parse_format, ekf_mask)
        ekf_serialize_func_name = 'void Ekf::ekfSerializeToJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){\n'
        ekf_load_func_name = 'void Ekf::ekfLoadFromJson(rapidjson::Value & ekfObj){\n'
        ekf_assert_func_name = 'void Ekf::ekfCheckJson(rapidjson::Value & ekfObj){\n'
        
        serialize_yaw_estimator = utfo.insertTabs(1)+'rapidjson::Value yawObj(rapidjson::kObjectType);\n'
        serialize_yaw_estimator += utfo.insertTabs(1)+'_yawEstimator.toJson(yawObj, allocator);\n'
        serialize_yaw_estimator += utfo.insertTabs(1)+'ekfObj.AddMember("_yawEstimator", yawObj, allocator);\n'
        ekf_serialize_func_name += serialize_yaw_estimator

        serialize_baro_estimator = utfo.insertTabs(1)+'rapidjson::Value baroObj(rapidjson::kObjectType);\n'
        serialize_baro_estimator += utfo.insertTabs(1)+'_baro_b_est.toJson(baroObj, allocator);\n'
        serialize_baro_estimator += utfo.insertTabs(1)+'ekfObj.AddMember("_baro_b_est", baroObj, allocator);\n'
        ekf_serialize_func_name += serialize_baro_estimator


        load_yaw_estimator = utfo.insertTabs(1)+'rapidjson::Value & yawObj = ekfObj["_yawEstimator"];\n'
        load_yaw_estimator += utfo.insertTabs(1)+'_yawEstimator.fromJson(yawObj);\n'
        ekf_load_func_name += load_yaw_estimator

        load_baro_estimator = utfo.insertTabs(1)+'rapidjson::Value & baroObj = ekfObj["_baro_b_est"];\n'
        load_baro_estimator += utfo.insertTabs(1)+'_baro_b_est.fromJson(baroObj);\n'
        ekf_load_func_name += load_baro_estimator

        n2t = generate_addon_file(struct, union, ekf_content, ekf_include, ekf_serialize_func_name, ekf_assert_func_name, ekf_load_func_name, 'ekf_addon')
        nameToType.update(n2t)
    
    if False:
        mod_include = '#include "EKF2.hpp"\n' + common_include
        mod_parse_format = '{}class EKF2 final : public ModuleParams, public px4::ScheduledWorkItem{}{{\npublic:{}private:{}}};\n#endif{}'
        mod_mask = [False, False, True, True, False]
        mod_content = extract_content('headers/EKF2.hpp', mod_parse_format, mod_mask)
        mod_serialize_func_name = 'void EKF2::_modSerializeToJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){\n'
        mod_load_func_name = 'void EKF2::_modLoadFromJson(rapidjson::Value & ekfObj){\n'
        mod_assert_func_name = 'void EKF2::_modCheckJson(rapidjson::Value & ekfObj){\n'
        blacklist = ["parameters"]
        n2t = generate_addon_file(struct, union, mod_content, mod_include, mod_serialize_func_name, mod_assert_func_name, mod_load_func_name, 'mod_addon', blacklist)
        nameToType.update(n2t)
    
    if True:
        print("Parsing EKF file")
        yaw_include = '#include "EKFGSF_yaw.h"\n' + common_include
        yaw_parse_format = "{}class EKFGSF_yaw{}{{\npublic:{}\nprivate:{}\n}};{}"
        yaw_mask = [False,False, True, True, False]
        yaw_content = utpa.extract_content('headers/EKFGSF_yaw.h', yaw_parse_format, yaw_mask)
        yaw_content = yawParser.yaw_est_content_filter(yaw_content)
        yaw_serialize_func_name = 'void EKFGSF_yaw::toJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){\n'
        yaw_load_func_name = 'void EKFGSF_yaw::fromJson(rapidjson::Value & ekfObj){\n'
        yaw_assert_func_name = 'void EKFGSF_yaw::checkJson(rapidjson::Value & ekfObj){\n'
        n2t = generate_addon_file(struct, union, yaw_content, yaw_include, yaw_serialize_func_name, yaw_assert_func_name, yaw_load_func_name, 'yaw_addon')
        # nameToType.update(n2t)
    if True:
        print("Parsing EKF file")
        baro_include = '#include "baro_bias_estimator.hpp"\n' + common_include
        baro_parse_format = "{}class BaroBiasEstimator{}{{\npublic:{}\nprivate:{}\n}};{}"
        baro_mask = [False,False, True, True, False]
        baro_content = utpa.extract_content('headers/baro_bias_estimator.hpp', baro_parse_format, baro_mask)
        baro_serialize_func_name = 'void BaroBiasEstimator::toJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){\n'
        baro_load_func_name = 'void BaroBiasEstimator::fromJson(rapidjson::Value & ekfObj){\n'
        baro_assert_func_name = 'void BaroBiasEstimator::checkJson(rapidjson::Value & ekfObj){\n'
        n2t = generate_addon_file(struct, union, baro_content, baro_include, baro_serialize_func_name, baro_assert_func_name, baro_load_func_name, 'baro_addon')
        # nameToType.update(n2t)
    

    nameToType_path = os.path.join(output_dir, 'nameToType.json')
    names = nameToType.keys()

    struct["EKFGSF_yaw"] = yawParser.yawEstimatorType
    struct["BaroBiasEstimator"] = baroBiasEstType


    def typeLookup(obj):
        if type(obj) is not dict:
            if type(obj) is list:
                types = []
                for l in obj:
                    types.append(typeLookup(l))
                return types
            if obj in struct:
                types = {}
                for k,v in struct[obj].items():
                    if k[0] != "~":
                        types[k] = typeLookup(v)
                return types
            elif obj in union:
                types = {}
                for k,v in union[obj].items():
                    if k[0] != "~":
                        types[k] = typeLookup(v)
                return types
            elif "[" in obj:
                t, arrlen = parse("{}[{}]", obj)
                arrlen = int(arrlen)
                return [t for _ in range(arrlen)]
            elif "Vector" in obj:
                arrlen = int(parse("Vector{}f", obj)[0])
                return ['float' for _ in range(arrlen)]
            elif "Dcmf" in obj:
                return ['float' for _ in range(3 * 3)]
            elif "SquareMatrix" in obj:
                s = int(parse("SquareMatrix{}f", obj)[0])
                return ['float' for _ in range(s * s)]
            elif "Matrix" in obj:
                s = int(parse("Matrix{}f", obj)[0])
                return ['float' for _ in range(s * s)]
            elif "Quatf" in obj:
                return ['float' for _ in range(4)]
            return obj
        
        output = {}
        for n in obj.keys():
            typeObj = obj[n]
            if type(typeObj) is dict:
                output[n] = typeLookup(typeObj)
            elif type(typeObj) is list:
                arr = []
                for t in typeObj:
                    arr.append(typeLookup(t))
                output[n] = arr
            elif typeObj in struct:
                types = {}
                for k,v in struct[typeObj].items():
                    if k[0] != "~":
                        types[k] = typeLookup(v)
                output[n] = types
            elif typeObj in union:
                types = {}
                for k,v in union[typeObj].items():
                    if k[0] != "~":
                        types[k] = typeLookup(v)
                output[n] = types
            else:
                output[n] = typeLookup(typeObj)
        return output
    
    def setFlagsAsBool(obj):
        output = {}
        for k,v in obj.items():
            if k == 'flags':
                flags = {}
                for fk, _ in v.items():
                    flags[fk] = 'bool'
                output[k] = flags
            elif type(v) is dict:
                output[k] = setFlagsAsBool(v)
            else:
                output[k] = v
        return output

    nameToType = setFlagsAsBool(typeLookup(nameToType))
    with open(nameToType_path, "w") as f:
        json.dump(nameToType, f, indent=4)

                