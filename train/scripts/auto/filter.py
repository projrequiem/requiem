#!/bin/python3
# Filter out data that only has to do with gps fusion
import numpy as np
import os
import re
import argparse
from pathlib import Path
from importlib.machinery import SourceFileLoader
currentScriptDir = os.path.dirname(os.path.realpath(__file__))
projectRootDir = Path(currentScriptDir).parent.parent.resolve()
projectScriptsDir = os.path.join(projectRootDir, 'scripts')
aud =  SourceFileLoader('datasetWrapper', os.path.join(projectScriptsDir, './analysis/utils/datasetWrapper.py')).load_module()

SAVE = True
DEBUG = True

def dprint(*args, **kwargs):
    if DEBUG:
        print('DEBUG: ', *args, **kwargs)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                        prog = 'Filter out samples when GPS is not being used',
                        description = 'Send log JSON to extracted EKF',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Directory with snapshots")
    parser.add_argument('-o', '--output', type=str, help="Model save directory")
    parser.add_argument('-r', '--recursive', action='store_true', help="Model save directory")
    args = parser.parse_args()

    if args.input == args.output:
        exit('Input and output cannot be the same directory')

    rootDirList = os.listdir(args.input)
    origPattern = re.compile(r'[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}.npz')
    count = 0
    logNameList = list(filter(origPattern.match, rootDirList))
    logNameList.sort()
    # Filter GPS
    for logName in logNameList:
        logPath = os.path.join(args.input, logName)
        outputPath = os.path.join(args.output, logName)
        if os.path.isfile(outputPath+'.npz'):
            continue
        orig = np.load(logPath)['h']

        filteredIndex = np.nonzero(orig[:,1,1211])[0].tolist()

        orig = orig[filteredIndex]
        before = orig.shape
        dprint('ORIG')
        dprint('before',orig.shape)

        innovIndiciesOfInterest = [x for x in range(1852, 1860)] + [1861,1862]
        minInnovs = np.min(np.abs(orig[:,1, innovIndiciesOfInterest]), axis=1)

        nonZeroInnovIndices = np.nonzero(minInnovs)[0].tolist()

        output = orig[nonZeroInnovIndices]
        dprint('after', output.shape)
        if SAVE:
            np.savez(outputPath, h=output)

        logBaseName, logFileType = os.path.splitext(logName)
        extPath = os.path.join(args.input, logBaseName)
        extPathList = os.listdir(extPath)

        extPattern = re.compile(logBaseName + '\([0-9]+\)\-[0-9]'+logFileType)
        extLogNameList = list(filter(extPattern.match, extPathList))

        extOutputDir = os.path.join(args.output, logBaseName)
        if not os.path.isdir(extOutputDir):
            os.mkdir(extOutputDir)
        for extLogName in extLogNameList:
            extLogPath = os.path.join(extPath, extLogName)

            extOutputPath = os.path.join(extOutputDir, extLogName)
            if os.path.isfile(extOutputPath):
                continue

            ext = np.load(extLogPath)['h']
            ext = ext[filteredIndex]
            ext = ext[nonZeroInnovIndices]
            if 0 in np.min(np.abs(ext[:,1,innovIndiciesOfInterest]), axis=1):
                dprint(ext.shape)
                dprint(extLogPath)
                dprint(np.min(np.abs(ext[:,1,innovIndiciesOfInterest]), axis=1), np.max(np.abs(ext[:,1,innovIndiciesOfInterest]), axis=1))
            if SAVE:
                np.savez(extOutputPath, h=ext)
