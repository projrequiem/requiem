import re
from parse import *
import json
import os
from parse_var import remove_comment_block, remove_comments

def struct_name_extractor(string):
    output = []
    regex_pattern = re.compile('struct [a-zA-Z0-9_]+')
    for n in regex_pattern.findall(string):
        _, n = n.split(' ')

        start_index = string.index(n) + len(n)
        content_start = None
        content_end = None
        nest_depth = 0
        content = ''
        for i in range(start_index, len(string)):
            c = string[i]
            if c == '{':
                nest_depth += 1
                if content_start == None:
                    content_start = i+1
                    continue
            elif c == '}':
                nest_depth -= 1
                if nest_depth < 0:
                    exit('UNEXPECTED }')
                elif nest_depth == 0:
                    content_end = i
                    break
        output.append((n, string[content_start:content_end]))
    return output

def extract_structs(filename, output_dir):
    with open(filename, 'r') as f:
        string = f.read()
        string = remove_comment_block(string)
        string = remove_comments(string)
        string = re.sub('[\n]+', ' ', string)
        string = re.sub('[\t]+', ' ', string)
        string = re.sub('[ ]+', ' ', string)
        names = struct_name_extractor(string)
        for (n, stuff) in names:
            struct_dict = {}
            for line in stuff.split(';'):
                l = re.sub(' +', ' ', line.strip().replace('\t',' '))
                l = re.sub('{[0-9_\.\- |\n:a-zA-Z]*}', '', l)
                l = l.strip()
                if len(l) < 1:
                    continue
                if 'const' in l:
                    t, var = parse("const {} {}", l)
                    struct_dict[var] = "const "+t
                if '[' in l:
                    t, var, val = parse("{} {}[{}]", l)
                    struct_dict[var] = t+"[%d]"%int(val)
                else:
                    t, var = parse("{} {}", l)
                    struct_dict[var] = t 
            with open(os.path.join(output_dir, n+".json"), 'w') as sf:
                json.dump(struct_dict, sf)

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.realpath(__file__))
    struct_dir = os.path.join(script_dir,'struct')
    #extract_structs('common.h', struct_dir)
    extract_structs('EKF2.hpp', struct_dir)