import json
from parse import *
from utils.parser import PRIMITIVE_NUMBERS, remove_comments
from utils.formatter import insertTabs
import re
import os
import argparse
# autnomate the generation of edge case types such as union

def extract_union(s, save_dir=None):
    # assumes there is only 1 struct in union
    regex_pattern = re.compile('union[ \t]+[a-zA-Z0-9_]+[ \t]+{')
    for ns in re.findall(regex_pattern, s):
        jobj = {}
        name = ns.split(' ')[1].strip()
        content = _extract_union(name, s)
        struct_name, struct_content, remaining_content = _extract_struct(content)
        jobj[struct_name] = convert_struct(struct_content)
        for l in remaining_content.split(';'):
            if len(l.strip()) < 3:
                continue
            var_type, var_name = l.strip().split(' ')
            jobj[var_name.strip()]=var_type.strip()
        jobj['~load'] = union_generate_load(jobj, struct_name)
        jobj['~assert'] = union_generate_assert(jobj, struct_name)
        jobj['~serialize'] = union_generate_serialize(jobj, struct_name)
        jobj['~union'] = True
        output_path = '%s.json'%name
        if save_dir is not None:
            output_path = os.path.join(save_dir, output_path)
        with open(output_path,'w') as of:
            of.write(json.dumps(jobj,sort_keys=True, indent=4))
    
def _extract_union(name, s):
    start_string = 'union %s {'%name
    start_index = s.index(start_string) + len(start_string)
    nest = 1
    content = ''
    for i in range(start_index, len(s)):
        if s[i] == '{':
            nest += 1
        elif s[i] == '}':
            nest -= 1
            if nest == 0:
                return content.strip()
        content += s[i]
    return None

def _extract_var_name(name, file_str):
    regex_pattern = re.compile('[\n \t]+%s[ \t]+[a-zA-Z0-9_\{\}]+;'%name)
    names = []
    for fs in file_str:
        n =re.findall(regex_pattern, fs)
        if len(n) == 0:
            continue
        n = n[0].strip()
        n = n.split(' ')[-1]
        if '{' in n:
            n = n.split("{")[0]
        names.append(n)
    return names


def _extract_struct(s):
    start_string = 'struct {'
    start_index = s.index(start_string) + len(start_string)
    end_index = -1
    nest = 1
    content = ''
    name = ''
    new_var_index = -1
    for i in range(start_index, len(s)):
        if s[i] == '{':
            nest += 1
        elif s[i] == '}':
            nest -= 1
            if nest == 0:
                end_index = i+1
                break
        content += s[i]
    for i in range(end_index, len(s)):
        if s[i] == ';':
            new_var_index = i+1
            break
        name += s[i]
    return name.strip(), content.strip(), s[new_var_index:]

def convert_struct(struct_content):
    jobj = {}
    for l in struct_content.split(';'):
        if len(l) < 1:
            continue
        type_n_name, _ = l.split(':')
        var_type, var_name = type_n_name.strip().split(' ')
        jobj[var_name.strip()] = var_type.strip()
    return jobj
    

def union_generate_load(outerJson, varname, union_obj, target_key, tabs=0):
    # Assumes it is the fault checker
    command = insertTabs(tabs) + '{{\n'
    command += insertTabs(tabs+1) + 'rapidjson::Value& innerJson = {oj}["{vn}"]["{tk}"];\n'
    for k,_ in union_obj[target_key].items():
        command += insertTabs(tabs+1) + '{vn}.{tk}.'+k+ ' = innerJson["{k}"].GetBool();\n'.format(k=k)
    command += '}}'
    return command.format(oj=outerJson, vn=varname, tk=target_key)

def union_generate_assert(outerJson, varname, union_obj, target_key, tabs=0):
    # Assumes it is the fault checker
    command = insertTabs(tabs)+'{{\n'
    command += insertTabs(tabs+1) +'assert({oj}["{vn}"].IsObject());\n'
    command += insertTabs(tabs+1) + 'assert({oj}["{vn}"]["{tk}"].IsObject());\n'
    structObj =  '{oj}["{vn}"]["{tk}"]'
	
    for k,_ in union_obj[target_key].items():
        l = insertTabs(tabs+1) + 'assert('+structObj+'["{k}"].IsBool());\n'.format(k=k)
        command += l
    command += insertTabs(tabs) + '}}\n'
    return command.format(oj=outerJson, vn=varname, tk=target_key)

def union_generate_serialize(outerJson, varname, unionObj, target_key, allocator, tabs=0): # only serialize flag
    # Assumes it is the fault checker
    command = insertTabs(tabs) + '{\n'
    command += insertTabs(tabs+1) + 'rapidjson::Value unionJson(rapidjson::kObjectType);\n'
    command += insertTabs(tabs+1) + 'rapidjson::Value innerJson(rapidjson::kObjectType);\n'
    for k,v in unionObj[target_key].items():
        if v == 'bool':
            l = insertTabs(tabs+1) + 'innerJson.AddMember("{k}", {vn}.{tk}.{k}, {a});\n'.format(k=k, vn=varname, tk=target_key, a=allocator)
        elif v in PRIMITIVE_NUMBERS:
            l = insertTabs(tabs+1) + 'if({vn}.{tk}.{k}){{\n'
            l += insertTabs(tabs+2) + 'innerJson.AddMember("{k}", true, {a});\n'
            l += insertTabs(tabs+1) + '}}else{{\n'
            l += insertTabs(tabs+2) + 'innerJson.AddMember("{k}", false, {a});\n'
            l += insertTabs(tabs+1) + '}}\n'
            l = l.format(vn=varname, k=k, tk=target_key, a=allocator)
        else:
            exit('ERROR: unexpected type encountered: %s when dealing with %s'%(v, unionObj))
        command += l
    command += insertTabs(tabs+1) + 'unionJson.AddMember("{tk}", innerJson, {a});\n'.format(tk=target_key, a=allocator)
    command += insertTabs(tabs+1) + '{oj}.AddMember("{vn}", unionJson, {a});\n'.format(oj=outerJson, vn=varname, a=allocator)
    command += insertTabs(tabs) +'}'
    return command

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Struct and Union generator',
                        description = 'Generates JSON used to generate c++ code to serialize and load structs',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input name to type file")
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory path other than the lookup")
    args = parser.parse_args()


    header_file_names = ['ekf.h', 'estimator_interface.h', 'common.h']
    script_dir = os.path.dirname(os.path.realpath(__file__))
    header_file_paths = []
    for name in header_file_names:
        if args.input is None:
            filePath = os.path.join(os.path.join(script_dir, "./headers"), name)
        else:
            filePath = os.path.join(args.input, name)
        header_file_paths.append(filePath)
    output_path = args.output
    if args.output is None:
        output_path = os.path.join(script_dir, "./struct")
    
    for fpath in header_file_paths:
        with open(fpath, 'r') as f:
            string = f.read()
            string = remove_comments(string)
            extract_union(string, output_path)