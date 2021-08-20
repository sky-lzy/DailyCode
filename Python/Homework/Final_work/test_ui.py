# 本文件用于将所训练模型显式测试

import os
import torch
import torchvision
from PIL import Image

# 关闭兼容性warning
import warnings
warnings.filterwarnings('ignore')

# 训练设备选择
device = torch.device('cpu')

# 导入已训练好的模型
model = torch.load('net_1_model\\net_1_50.pth')
model.to(device)

# 载入姓名
name = input('请输入您想要识别的姓名：')
filelist = os.listdir('data\\'+name)

# 进行判断
if filelist.__len__() == 0:
    print('该人不存在')
else:
    flag = 0
    # 对所有照片进行遍历
    for image_name in filelist:
        image = Image.open(os.path.join('data', name, image_name))
        image.show()
        image.convert('RGB')

        # 更改照片格式
        transform = torchvision.transforms.Compose([
            torchvision.transforms.Resize((64, 64)),
            torchvision.transforms.ToTensor()
        ])
        image = transform(image)
        image = image.reshape((1, 3, 64, 64))

        # 使用模型预测
        out = model(image)
        flag += (out[0][0] < out[0][1]) / filelist.__len__()
    
    # 进行判断
    if flag > 0.5:
        print('女性')
    elif flag < 0.5:
        print('男性')
    else:
        print('无法判断')