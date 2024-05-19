import argparse
import numpy as np
import snappy
import json
import os
import utils.file as uf
import utils.log as ul

def getDictDiff(da, db, blacklist=[]):
    output = {}
    da_keys = set(da.keys())
    db_keys = set(db.keys())
    if len(da_keys) != len(db_keys) or len(da_keys.intersection(db_keys)) != len(da_keys):
        print("Key Difference")
    keys = list(da_keys)
    for k in keys:
        va = da[k]
        vb = db[k]
        if va != vb:
            if k in blacklist:
                continue
            if type(va) is dict:
                result = getDictDiff(va,vb)
                if len(result) != 0:
                    output[k] = result
            # elif type(va) == type(vb) and type(va[0]) == type(vb[0]) and type(va) is list and type(va[0]) is not bool and type(va[0]) is not dict:
            #     va = np.array(va)
            #     vb = np.array(vb)
            #     if not np.isclose(va,vb):
            #         output[k] = {'pdiff': ((vb- va)/vb).tolist(), 'comp': [va.tolist(), vb.tolist()]}
            else:
                if type(va) == type(vb) and (type(va) is bool):
                    output[k] = {'comp': [va, vb]}
                elif type(va) == type(vb) and (type(va) is int or type(va) is float):
                    if np.isclose(va, vb):
                        continue
                    output[k] = {'comp': [va, vb]}
                    if vb != 0:
                        output[k]['pdiff'] = (vb- va)/vb 
                else:
                    output[k] = {'comp': [va, vb]}
    return output

# def vec_to_log(vec, logStruct, nameToIndex, root=''):
#     output = {}
#     for k,v in logStruct.items():
#         full_name = root+"."+k
#         if root == '':
#             full_name = k
#         if type(v) is dict:
#             output[k] = vec_to_log(vec, v, nameToIndex, full_name)
#         elif type(v) is list:
#             arr = []
#             for i in range(len(v)):
#                 key = full_name+'[%d]'%i
#                 if type(v[i]) is dict:
#                     arr.append(vec_to_log(vec, v[i], nameToIndex, key))
#                 else:
#                     arr.append(vec[nameToIndex[key]])
#             output[k] = arr
#         else:
#             output[k] = vec[nameToIndex[full_name]]
#     return output

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-pi', '--parsedInput', type=str, help="Path to the numpy file")
    parser.add_argument('-li', '--logInput', type=str, help="Path to the log file")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    args = parser.parse_args()

    vecs = np.load(args.parsedInput)
    logJsons = uf.loadJson(args.logInput)

    path_to_name2index = os.path.join(args.lookup, 'nameToIndex.json')
    path_to_index2name = os.path.join(args.lookup, 'indexToName.json')
    if not os.path.isdir(args.lookup):
        exit('Specified lookup table does not exist: %s'%args.lookup)
    elif not os.path.isfile(path_to_name2index):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_name2index)
    elif not os.path.isfile(path_to_index2name):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_index2name)

    nameToIndex = uf.loadJson(path_to_name2index)
    indexToName = uf.loadJson(path_to_index2name)


    for i in range(len(logJsons['hist'])):
        print(i)
        lj = logJsons['hist'][i]
        log_pref = lj['pref']
        log_postf = lj['postf']
        log_posth = lj['posth']

        vec_pref = vecs['f'][i][0]
        vec_postf = vecs['f'][i][1]
        vec_posth = vecs['h'][i][1]

        vec_log_pref = ul.vec_to_log(vec_pref, log_pref, nameToIndex)
        vec_log_postf = ul.vec_to_log(vec_postf, log_pref, nameToIndex)
        vec_log_posth = ul.vec_to_log(vec_posth, log_pref, nameToIndex)

        if log_pref != vec_log_pref:
            print('pref not equal')

        if log_postf != vec_log_postf:
            print('postf not equal')
        if log_posth != vec_log_posth:
            output = getDictDiff(log_posth, vec_log_posth)
            if len(output.keys()) == 0:
                continue
            print('posth not equal')
            with open("discrepencies.json","w") as f:
                json.dump({"keys":list(output.keys()), "instances":output, "reference":vec_posth.tolist()}, f, indent=4)
            exit()
