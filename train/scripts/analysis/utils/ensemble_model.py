import torch


class SimpleEnsemble(torch.nn.Module):
    def __init__(self, models, ensemble_idim, ensemble_hdim, ensemble_odim, hidden_count):
        super().__init__()
        self._models = torch.nn.ModuleList(models)
        self.ilayer = torch.nn.Linear(ensemble_idim, ensemble_hdim)
        self.ensembleLayer = torch.nn.ModuleList()
        for _ in range(hidden_count):
            self.ensembleLayer.append(torch.nn.Linear(ensemble_hdim, ensemble_hdim))
            self.ensembleLayer.append(torch.nn.ReLU())
        self.olayer = torch.nn.Linear(ensemble_hdim, ensemble_odim)

    def forward(self, x):
        ensemble_in = []
        with torch.no_grad():
            for m in self._models:
                ensemble_in.append(m(x))
        ensemble_in = torch.cat(ensemble_in, dim=1)
        return self.ensembelForward(ensemble_in)

    def ensembelForward(self,x):
        x = self.ilayer(x)
        for m in self.ensembleLayer:
            x = m(x)
        return self.olayer(x)

