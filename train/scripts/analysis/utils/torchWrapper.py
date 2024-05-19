import sys
import torch

device = torch.device("cpu")
if 'linux' in sys.platform or sys.platform == 'win32':
    if torch.has_cuda:
        device = torch.device('cuda')
    pass
elif sys.platform == 'darwin':
    # check if torch has mps
    if torch.has_mps:
        device = torch.device("mps")
def optimizer_to(optim):
    for param in optim.state.values():
        # Not sure there are any global tensors in the state dict
        if isinstance(param, torch.Tensor):
            param.data = toDevice(param.data)
            if param._grad is not None:
                param._grad.data = toDevice(param._grad.data)
        elif isinstance(param, dict):
            for subparam in param.values():
                if isinstance(subparam, torch.Tensor):
                    subparam.data = toDevice(subparam.data)
                    if subparam._grad is not None:
                        subparam._grad.data = toDevice(subparam._grad.data)


def toDevice(tensor):
    # to any gpu/cuda if availiable
    return tensor.to(device)

def toNumpy(tensor):
    if torch.is_tensor(tensor):
        return tensor.numpy()

def fromNumpy(npVec):
    return toDevice(torch.from_numpy(npVec))

def fromList(l):
    return toDevice(torch.torch(l))

def toDouble(tensor):
    if sys.platform == 'darwin':
        return tensor.float()
    return tensor.double()