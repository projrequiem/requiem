import os
import re
import torch
import math

class SimpleFF(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden2 = torch.nn.ReLU().double()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).double()
        self.hidden4 = torch.nn.ReLU().double()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).double()
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        x = self.hidden5(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class SimpleFFWithDropout(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden2 = torch.nn.ReLU().double()
        self.drop1 = torch.nn.Dropout(p=0.1).double()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).double()
        self.hidden4 = torch.nn.ReLU().double()
        self.drop2 = torch.nn.Dropout(p=0.1).double()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).double()
        self.drop = True
    
    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class SimpleFFWithDropoutFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden2 = torch.nn.ReLU().float()
        self.drop1 = torch.nn.Dropout(p=0.1).float()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden4 = torch.nn.ReLU().float()
        self.drop2 = torch.nn.Dropout(p=0.1).float()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.drop = True
    
    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class HourGlassFFWithDropout(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_hidden2 : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden2 = torch.nn.ReLU().double()
        self.drop1 = torch.nn.Dropout(p=0.1).double()

        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden2).double()
        self.hidden4 = torch.nn.ReLU().double()
        self.drop2 = torch.nn.Dropout(p=0.1).double()
        
        self.hidden5 = torch.nn.Linear(dim_hidden2, dim_hidden2).double()
        self.hidden6 = torch.nn.ReLU().double()
        self.drop3 = torch.nn.Dropout(p=0.1).double()

        self.hidden7 = torch.nn.Linear(dim_hidden2, dim_hidden).double()
        self.hidden8 = torch.nn.ReLU().double()
        self.drop4 = torch.nn.Dropout(p=0.1).double()

        self.hidden9 = torch.nn.Linear(dim_hidden, dim_output).double()
        self.drop = True
    
    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        if self.drop:
            x = self.drop3(x)
        x = self.hidden7(x)
        x = self.hidden8(x)
        if self.drop:
            x = self.drop4(x)
        x = self.hidden9(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device


class SimpleFFProbWithDrop(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden2 = torch.nn.ReLU().double()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).double()
        self.hidden4 = torch.nn.ReLU().double()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).double()
        self.hidden6 = torch.nn.Sigmoid().double()

        self.drop = True
        self.drop1 = torch.nn.Dropout(p=0.1).double()
        self.drop2 = torch.nn.Dropout(p=0.1).double()

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class SimpleFFProbWithDropFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden2 = torch.nn.ReLU().float()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden4 = torch.nn.ReLU().float()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden6 = torch.nn.Sigmoid().float()

        self.drop = True
        self.drop1 = torch.nn.Dropout(p=0.1)
        self.drop2 = torch.nn.Dropout(p=0.1)

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device


class HourGlassFFWithDropoutFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_hidden2 : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden2 = torch.nn.ReLU().float()
        self.drop1 = torch.nn.Dropout(p=0.1).float()

        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden2).float()
        self.hidden4 = torch.nn.ReLU().float()
        self.drop2 = torch.nn.Dropout(p=0.1).float()
        
        self.hidden5 = torch.nn.Linear(dim_hidden2, dim_hidden2).float()
        self.hidden6 = torch.nn.ReLU().float()
        self.drop3 = torch.nn.Dropout(p=0.1).float()

        self.hidden7 = torch.nn.Linear(dim_hidden2, dim_hidden).float()
        self.hidden8 = torch.nn.ReLU().float()
        self.drop4 = torch.nn.Dropout(p=0.1).float()

        self.hidden9 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.drop = True
    
    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        if self.drop:
            x = self.drop3(x)
        x = self.hidden7(x)
        x = self.hidden8(x)
        if self.drop:
            x = self.drop4(x)
        x = self.hidden9(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class HourGlassFFProbWithDropoutFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_hidden2 : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden)
        self.hidden2 = torch.nn.ReLU()
        self.drop1 = torch.nn.Dropout(p=0.1)

        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden2)
        self.hidden4 = torch.nn.ReLU()
        self.drop2 = torch.nn.Dropout(p=0.1)
        
        self.hidden5 = torch.nn.Linear(dim_hidden2, dim_hidden2)
        self.hidden6 = torch.nn.ReLU()
        self.drop3 = torch.nn.Dropout(p=0.1)

        self.hidden7 = torch.nn.Linear(dim_hidden2, dim_hidden)
        self.hidden8 = torch.nn.ReLU()
        self.drop4 = torch.nn.Dropout(p=0.1)

        self.hidden9 = torch.nn.Linear(dim_hidden, dim_output)
        self.sig = torch.nn.Sigmoid()
        self.drop = True
    
    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        if self.drop:
            x = self.drop3(x)
        x = self.hidden7(x)
        x = self.hidden8(x)
        if self.drop:
            x = self.drop4(x)
        x = self.hidden9(x)
        x = self.sig(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class SimpleLinearFFWithDropFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_output).float()

        self.drop = True
        self.drop1 = torch.nn.Dropout(p=0.1)
        self.drop2 = torch.nn.Dropout(p=0.1)

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden3(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden5(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class DeepSimpleFFWithDropFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden2 = torch.nn.ReLU()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden4 = torch.nn.ReLU()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden6 = torch.nn.ReLU()
        self.hidden7 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden8 = torch.nn.ReLU()
        self.hidden9 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden10 = torch.nn.ReLU()
        self.hidden11 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden12 = torch.nn.ReLU()
        self.hidden13 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden14 = torch.nn.ReLU()
        self.hidden15 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden16 = torch.nn.ReLU()
        self.hidden17 = torch.nn.Linear(dim_hidden, dim_output).float()

        self.drop = True
        self.drop1 = torch.nn.Dropout(p=0.1)
        self.drop2 = torch.nn.Dropout(p=0.1)
        self.drop3 = torch.nn.Dropout(p=0.1)

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        x = self.hidden7(x)
        x = self.hidden8(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden9(x)
        x = self.hidden10(x)
        x = self.hidden11(x)
        x = self.hidden12(x)
        if self.drop:
            x = self.drop3(x)
        x = self.hidden13(x)
        x = self.hidden14(x)
        x = self.hidden15(x)
        x = self.hidden16(x)
        x = self.hidden17(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class DeeperSimpleFFWithDropFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int):
        super().__init__()
        self.hidden1 = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden2 = torch.nn.ReLU()
        self.hidden3 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden4 = torch.nn.ReLU()
        self.hidden5 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden6 = torch.nn.ReLU()
        self.hidden7 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden8 = torch.nn.ReLU()
        self.hidden9 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden10 = torch.nn.ReLU()
        self.hidden11 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden12 = torch.nn.ReLU()
        self.hidden13 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden14 = torch.nn.ReLU()
        self.hidden15 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden16 = torch.nn.ReLU()
        self.hidden17 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden18 = torch.nn.ReLU()
        self.hidden19 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden20 = torch.nn.ReLU()
        self.hidden21 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden22 = torch.nn.ReLU()
        self.hidden23 = torch.nn.Linear(dim_hidden, dim_hidden).float()
        self.hidden24 = torch.nn.ReLU()
        self.hidden25 = torch.nn.Linear(dim_hidden, dim_output).float()

        self.hidden26 = torch.nn.ReLU()
        self.hidden27 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden28 = torch.nn.ReLU()
        self.hidden29 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden30 = torch.nn.ReLU()
        self.hidden31 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden32 = torch.nn.ReLU()
        self.hidden33 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden34 = torch.nn.ReLU()
        self.hidden35 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.hidden36 = torch.nn.ReLU()
        self.hidden37 = torch.nn.Linear(dim_hidden, dim_output).float()
        self.sig = torch.nn.Sigmoid()

        self.drop = True
        self.drop1 = torch.nn.Dropout(p=0.1)
        self.drop2 = torch.nn.Dropout(p=0.1)
        self.drop3 = torch.nn.Dropout(p=0.1)

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.hidden1(x)
        x = self.hidden2(x)
        x = self.hidden3(x)
        x = self.hidden4(x)
        if self.drop:
            x = self.drop1(x)
        x = self.hidden5(x)
        x = self.hidden6(x)
        x = self.hidden7(x)
        x = self.hidden8(x)
        if self.drop:
            x = self.drop2(x)
        x = self.hidden9(x)
        x = self.hidden10(x)
        x = self.hidden11(x)
        x = self.hidden12(x)
        if self.drop:
            x = self.drop3(x)
        x = self.hidden13(x)
        x = self.hidden14(x)
        x = self.hidden15(x)
        x = self.hidden16(x)
        x = self.hidden17(x)
        x = self.hidden18(x)
        x = self.hidden19(x)
        x = self.hidden20(x)
        x = self.hidden21(x)
        x = self.hidden22(x)
        x = self.hidden23(x)
        x = self.hidden24(x)
        x = self.hidden25(x)
        return self.sig(x)
    
    @property
    def device(self):
        return next(self.parameters()).device

class VariableFFFloat(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int, hidden_count : int):
        super().__init__()
        self.input = torch.nn.Linear(dim_input, dim_hidden).float()
        self.hidden = torch.nn.ModuleList()
        for _ in range(hidden_count):
            self.hidden.append(torch.nn.Linear(dim_hidden, dim_hidden).float())
            self.hidden.append(torch.nn.ReLU())
        self.output = torch.nn.Linear(dim_hidden, dim_output).float()
        self.drop = True

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.input(x)
        for l in self.hidden:
            x = l(x)
        x = self.output(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class VariableFF(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int, hidden_count : int):
        super().__init__()
        self.input = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden = torch.nn.ModuleList()
        for _ in range(hidden_count):
            self.hidden.append(torch.nn.Linear(dim_hidden, dim_hidden).double())
            self.hidden.append(torch.nn.ReLU())
        self.output = torch.nn.Linear(dim_hidden, dim_output).double()
        self.drop = True

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.input(x)
        for l in self.hidden:
            x = l(x)
        x = self.output(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class LinearFF(torch.nn.Module):
    def __init__(self, dim_input : int, dim_hidden : int, dim_output : int, hidden_count : int):
        super().__init__()
        self.input = torch.nn.Linear(dim_input, dim_hidden).double()
        self.hidden = torch.nn.ModuleList()
        for _ in range(hidden_count):
            self.hidden.append(torch.nn.Linear(dim_hidden, dim_hidden).double())
            # self.hidden.append(torch.nn.ReLU())
        self.output = torch.nn.Linear(dim_hidden, dim_output).double()
        self.drop = True

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.input(x)
        for l in self.hidden:
            x = l(x)
        x = self.output(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device


class SimpleConv(torch.nn.Module):
    # Size of convolution
    def __init__(self, dim_input:int, dim_hidden:int, dim_output:int, 
                 conv_inc:int, conv_outc:int, conv_kern:int, conv_stride:int, conv_pad:int, conv_dila:int,
                 pool_kern:int, pool_stride:int, pool_pad:int, pool_dila:int):
        # ensure that him_hidden is a square
        root = math.sqrt(dim_hidden)
        # if int(root + 0.5) ** 2 == dim_hidden:
        #     print(dim_hidden, "is a perfect square")
        # else:
        #     print(dim_hidden, "is not a perfect square")

        super().__init__()

        self.input = torch.nn.Linear(dim_input, dim_hidden).double()
        self.linear1 = torch.nn.Linear(dim_hidden, dim_hidden).double()
        self.relu1 = torch.nn.ReLU()
        self.conv1 = torch.nn.Conv1d(conv_inc, conv_outc, conv_kern, conv_stride, conv_pad, conv_dila).double()

        # out shape [(W−K+2P)/S]+1
        self.conv1_in_shape = (int(root), int(root))
        #  (l_in +2 * padding - dialation * (kern-1)-1)/stride + 1
        conv1_l_out = math.floor((root + 2 * conv_pad - conv_dila * (conv_kern - 1) - 1)/conv_stride + 1)
        self.conv1_out_shape = (root, conv1_l_out)

        self.conv2 = torch.nn.Conv1d(conv_inc, conv_outc, conv_kern, conv_stride, conv_pad, conv_dila).double()
        conv2_l_out = math.floor((conv1_l_out + 2 * conv_pad - conv_dila * (conv_kern - 1) - 1)/conv_stride + 1)

        self.pool1 = torch.nn.MaxPool1d(pool_kern, pool_stride, pool_pad, pool_dila)

        pool1_l_out =  math.floor((conv2_l_out + 2 * pool_pad - pool_dila * (pool_kern-1)-1)/pool_stride + 1)

        self.linear2 = torch.nn.Linear(int(root * pool1_l_out), dim_hidden).double()
        self.relu2 = torch.nn.ReLU()
        self.output = torch.nn.Linear(dim_hidden, dim_output).double()
        self.drop = True

    def dropOff(self):
        self.drop = False
    def dropOn(self):
        self.drop = True
        
    def forward(self, x):
        x = self.input(x)
        x = self.linear1(x)
        x = self.relu1(x)
        x = self.conv1(x.view(-1, self.conv1_in_shape[0], self.conv1_in_shape[1]))
        x = self.conv2(x)
        x = self.pool1(x)
        x = torch.flatten(x, start_dim=1)
        x = self.linear2(x)
        x = self.relu2(x)
        x = self.output(x)
        return x
    
    @property
    def device(self):
        return next(self.parameters()).device

class VariableAE(torch.nn.Module):
    def __init__(self) -> None:
        super().__init__()

