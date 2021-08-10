import torch.nn as nn

# Net_1 输入：(3, 64, 64)


class Net_1(nn.Module):

    def __init__(self):
        super(Net_1, self).__init__()

        self.model = nn.Sequential(
            nn.Conv2d(3, 64, 3, 1, 1, bias=False),
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.MaxPool2d(2),
            nn.Conv2d(64, 64, 3, 1, 1, bias=False),
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.MaxPool2d(2),

            nn.Conv2d(64, 128, 3, 1, 1, bias=False),
            nn.BatchNorm2d(128),
            nn.ReLU(True),
            nn.MaxPool2d(2),
            nn.Conv2d(128, 128, 3, 1, 1, bias=False),
            nn.BatchNorm2d(128),
            nn.ReLU(True),
            nn.MaxPool2d(2),

            nn.Flatten(),

            nn.Linear(2048, 64),
            nn.ReLU(True),
            nn.Linear(64, 2)
        )

    def forward(self, x):
        out = self.model(x)
        return out


# Net_2 输入：(3, 227, 227), 改自Alexnet网络模型
class Net_2(nn.Module):

    def __init__(self):
        super(Net_2, self).__init__()

        self.model = nn.Sequential(
            nn.Conv2d(3, 96, 11, 4, 0),
            nn.ReLU(True),
            nn.MaxPool2d(3, 2),

            nn.Conv2d(96, 256, 5, 1, 2),
            nn.ReLU(True),
            nn.MaxPool2d(3, 2),

            nn.Conv2d(256, 384, 3, 1, 1),
            nn.ReLU(True),

            nn.Conv2d(384, 384, 3, 1, 1),
            nn.ReLU(True),

            nn.Conv2d(384, 256, 3, 1, 1),
            nn.ReLU(True),
            nn.MaxPool2d(3, 2),

            nn.Flatten(),

            nn.Linear(4096, 4096),
            nn.ReLU(True),
            nn.Dropout2d(0.5, True),

            nn.Linear(4096, 2)
        )

    def forward(self, x):
        out = self.model(x)
        return out
