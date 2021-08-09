import torch
from mydata import MyData
from torch.utils.data.dataloader import DataLoader

# 构建测试数据集
test_data =  MyData(False)
test_size = len(test_data)
test_dataloader = DataLoader(test_data, batch_size=32, shuffle=True)

# 设置测试设备
device = torch.device('cuda')

# 导入已训练好的模型
model = torch.load('net_gpu.pth')
model.to(device)

# 测试步骤
total_accuracy = 0

model.eval()
with torch.no_grad():
    for inputs, targets in test_dataloader:
        inputs = inputs.to(device)
        targets = targets.to(device)

        outputs = model(inputs)
        accuracy = (outputs.argmax(1) == targets).sum()
        total_accuracy += accuracy

    print('正确率：{}'.format(total_accuracy / test_size))