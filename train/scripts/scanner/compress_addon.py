import json
import os
import snappy
import argparse
import re

def compress(content, lookup):
    output = content
    for k,v in lookup.items():
        keyword = "\"%s\""%k
        compid = "\"%x\""%v
        if keyword in output:
            output = output.replace(keyword, compid)
    return output

def get_keywords(content):
    return list(set(re.findall(r'\[\"[a-zA-Z0-9\.\_]+\"\]', content)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'compress addon.cpp',
                        description = 'replace the keywordsin the addon.cpp',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input that contains the addon files")
    parser.add_argument('-o', '--output', type=str, default='./',help="Output directory")
    parser.add_argument('-l', '--lookup', type=str, default='./', help="Path to lookup table dir to serialize the log")

    args = parser.parse_args()
    N2ID = {}
    path_to_nameToId = os.path.join(args.lookup, 'nameToId.json')
    with open(path_to_nameToId,"r") as f:
        N2ID = json.load(f)

    content = ""
    path_to_ekf_addon = os.path.join(args.input, 'ekf_addon.cpp')
    with open(path_to_ekf_addon, "r") as f:
        content = f.read()
    comp_content = compress(content, N2ID)
    keywords = get_keywords(comp_content)
    for k in keywords:
        if "_" in k:
            print(k)
    path_to_ekf_addon_out = os.path.join(args.output, 'ekf_addon_comp.cpp')
    with open(path_to_ekf_addon_out, "w") as f:
        f.write(comp_content)

    content = ""
    path_to_ei_addon = os.path.join(args.input, 'ei_addon.cpp')
    with open(path_to_ei_addon, "r") as f:
        content = f.read()
    comp_content = compress(content, N2ID)
    keywords = get_keywords(comp_content)
    for k in keywords:
        if "_" in k:
            print(k)
    path_to_ei_addon_out = os.path.join(args.output, 'ei_addon_comp.cpp')
    with open(path_to_ei_addon_out, "w") as f:
        f.write(comp_content)
    
    
