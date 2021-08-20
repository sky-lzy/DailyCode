# 本文件用于对输入任意图片进行判断

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

# 照片地址
image_dir = '1.jpg'

# 调整格式
image = Image.open(image_dir)
image.show()
image.convert('RGB')

transform = torchvision.transforms.Compose([
    torchvision.transforms.Resize((64, 64)),
    torchvision.transforms.ToTensor()
])
image = transform(image)
image = image.reshape((1, 3, 64, 64))

# 利用模型预测
out = model(image)

if out[0][0] < out[0][1]:
    print('女性')
else:
    print('男性')