import os
import json
import argparse

def insertTabs(tc):
    return '\t'*tc
def params_to_vec(paramsNames, tabs=0):
    # params index goes from 0 to 110
    output = ''
    for n in paramsNames:
        line = ''
        if '[' in paramsNames:
            pass
        else:
            pass
        line += insertTabs(tabs+1)
        output += line + '\n'
        

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Generate unique IDs for each field from a log',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, default=None, help="Input direcotry of where the header files are")
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory")
    args = parser.parse_args()

    output = ''
    indexToName_path = os.path.join()
    indexToName = {}
    with open(indexToName_path, 'r') as f:
        indexToName = json.load(f)
    output += params_to_vec(indexToName[:111])
    pass