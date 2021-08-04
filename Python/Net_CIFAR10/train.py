# 本例尝试训练分类器神经网络，以CIFAR10为例

import torch
import torch.nn as nn
import torchvision
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter

from net import Net

# tensorboard可视化
writer = SummaryWriter('./logs')

# 数据集
train_data = torchvision.datasets.CIFAR10(
    "./dataset", train=True, transform=torchvision.transforms.ToTensor(), download=True)
test_data = torchvision.datasets.CIFAR10(
    "./dataset", train=False, transform=torchvision.transforms.ToTensor(), download=True)

train_data_size = len(train_data)  # 50000
test_data_size = len(test_data)  # 10000

train_dataloader = DataLoader(train_data, batch_size=64)
test_dataloader = DataLoader(test_data, batch_size=64)

# 定义训练设备
device = torch.device('cuda')

# 构建神经网络实例
net = Net()
net.to(device)

# 损失函数
loss_func = nn.CrossEntropyLoss()
loss_func.to(device)

# 优化器
learning_rate = 0.1
optimizer = torch.optim.SGD(net.parameters(), lr=learning_rate)

# 设置训练参数
total_train_step = 0  # 训练次数
total_test_step = 0 # 测试次数
epoch = 100  # 训练轮数

for i in range(epoch):
    print('---------第{}轮训练开始---------'.format(i + 1))

    # 训练步骤
    net.train()

    for data in train_dataloader:
        imgs, targets = data
        imgs = imgs.to(device)
        targets = targets.to(device)

        outputs = net(imgs)
        loss = loss_func(outputs, targets)

        #优化器优化
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        total_train_step += 1
        if total_train_step % 100 == 0:
            print('训练次数：{}, Loss: {}'.format(total_train_step, loss.item()))
            writer.add_scalar('train_loss', loss.item(), total_train_step)

    # 测试步骤
    net.eval()

    total_test_loss = 0
    total_accuracy = 0
    with torch.no_grad():
        for data in test_dataloader:
            imgs, targets = data
            imgs = imgs.to(device)
            targets = targets.to(device)

            outputs = net(imgs)
            loss = loss_func(outputs, targets)
            total_test_loss += loss.item()
            accuracy = (outputs.argmax(1) == targets).sum()
            total_accuracy += accuracy

        total_test_step += 1
        
        print('测试集上的Loss: {}'.format(total_test_loss))
        print('正确率: {}'.format(total_accuracy / test_data_size))

        writer.add_scalar('test_loss', total_test_loss, total_test_step)
        writer.add_scalar('test_accuracy', total_accuracy / test_data_size, total_test_step)

    # 保存训练模型
    if (i + 1) % 10 == 0:
        torch.save(net, 'net_CIFAR10_gpu_{}.pth'.format(i + 1))
        print('模型已保存')

writer.close()