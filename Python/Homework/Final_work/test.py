import torch
from mydata import MyData
from torch.utils.data.dataloader import DataLoader
from torch.utils.tensorboard import SummaryWriter

# tensorboard可视化
writer = SummaryWriter('logs_net_')

# 构建测试数据集
test_data =  MyData(False)
test_size = len(test_data)
test_dataloader = DataLoader(test_data, batch_size=32, shuffle=True)

# 设置测试设备
device = torch.device('cuda')

for i in range(5, 55, 5):
    # 导入已训练好的模型
    model = torch.load('net_1_model\\net_1_{}.pth'.format(i))
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

        accuracy_rate = total_accuracy / test_size
        print('第{}轮模型 正确率：{}'.format(i, accuracy_rate))

        writer.add_scalar('model_accuracy', accuracy_rate, i)
    
writer.close()