import torch
import os
import re
from importlib.machinery import SourceFileLoader

def listCPPaths(modelDir, prefix=''):
    rootDirList = os.listdir(modelDir)
    origPattern = re.compile(r'%scheckpoint\_[0-9]+.pt'%prefix)
    output = []
    for modelPath in list(filter(origPattern.match, rootDirList)):
        output.append(modelPath)
    return output

def _cpSortHelper(p):
    return int(p.split('_')[-1].split('.')[0])

def getLatestCPPath(modelDir, prefix=''):
    cpps = listCPPaths(modelDir, prefix=prefix)
    cpps.sort(key=_cpSortHelper)
    return cpps[-1], _cpSortHelper(cpps[-1])


def saveCheckpoint(outputPath, model, modelArgs, optimizer, optimizer_args, loss, epoch, targetIndices=None, targetNames=None, val_loss=None, meta=None):
    if os.path.isfile(outputPath):
        return False
    checkpoint = {'epoch':epoch, 'model_state_dict': model.state_dict(), 'optimizer_state_dict':optimizer.state_dict(),
                    'loss':loss, 'model_type':model.__class__.__name__, 'model_args':
                    modelArgs, 'optimizer_type':optimizer.__class__.__name__, 'optimizer_args':optimizer_args, 'val_loss':val_loss}
    if targetIndices is not None:
        checkpoint['target_indices']=targetIndices
    if targetNames is not None:
        checkpoint['target_names']=targetNames
    if val_loss is not None:
        checkpoint['val_loss']=val_loss
    if meta is not None:
        checkpoint['meta']=meta
    torch.save(checkpoint, outputPath)
    return True

def loadCheckpoint(checkpointPath):
    _current_script_path = os.path.dirname(os.path.realpath(__file__))
    modelModule =  SourceFileLoader('model', os.path.join(_current_script_path, 'model.py')).load_module()

    output = {'model':None, 'optimizer':None, 'optimizer_type':None, 'epoch':None, 'model_args':None, 'optimizer_args':None}
    with torch.no_grad():
        print('loading:', checkpointPath)
        checkpoint = torch.load(checkpointPath)
        print('Finished loading')
        model = getattr(modelModule, checkpoint['model_type'])(**checkpoint['model_args'])
        model.load_state_dict(checkpoint['model_state_dict'])
        model.eval()
        model.cuda()
        optimizer = getattr(torch.optim, checkpoint['optimizer_type'])(model.parameters(), **checkpoint['optimizer_args'])
        optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        output['epoch'] = checkpoint['epoch']
        output['loss'] = checkpoint['loss']
        output['model'] = model
        output['model_args'] = checkpoint['model_args']
        output['optimizer'] = optimizer
        output['optimizer_args'] = checkpoint['optimizer_args']
        if 'target_indices' in checkpoint:
            output['target_indices'] = checkpoint['target_indices']
        if 'target_names' in checkpoint:
            output['target_names'] = checkpoint['target_names']
        if 'meta' in checkpoint:
            output['meta'] = checkpoint['meta']
    return output