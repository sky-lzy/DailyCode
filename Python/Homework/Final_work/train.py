import torch
import torch.nn as nn
from torch.utils.data import random_split, DataLoader
from torch.utils.tensorboard import SummaryWriter
from net import Net_2
from mydata import MyData

# tensorboard可视化
writer = SummaryWriter('logs')

# 构建数据集
all_data = MyData(True)
all_size = len(all_data)
train_size = int(0.8 * all_size)
test_size = all_size - train_size
train_dataset, test_dataset = random_split(all_data, [train_size, test_size])

train_dataloader = DataLoader(train_dataset, batch_size=16, shuffle=True)
test_dataloader = DataLoader(test_dataset, batch_size=16, shuffle=True)

# 设置训练设备
device = torch.device('cuda')

# 构建神经网络实例
net = Net_2()
# net = torch.load('.pth')
net.to(device)

# 定义损失函数
loss_func = nn.CrossEntropyLoss()
loss_func.to(device)

# 设置学习率和优化器
learning_rate = 0.01
net_optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate)
net_scheduler = torch.optim.lr_scheduler.StepLR(net_optimizer, 5, 0.8)

# 设置训练参数
total_train_step = 0
total_test_step = 0
train_epoch = 50

# 训练开始
for i in range(train_epoch):
    print('----------第{}轮训练开始----------'.format(i + 1))

    # 训练过程
    net.train()

    for inputs, targets in train_dataloader:
        inputs = inputs.to(device)
        targets = targets.to(device)

        outputs = net(inputs)
        loss = loss_func(outputs, targets)

        # 训练器优化
        net_optimizer.zero_grad()
        loss.backward()
        net_optimizer.step()
        net_scheduler.step()

        total_train_step += 1
        if total_train_step % 20 == 0:
            print('训练次数: {}, Loss: {}'.format(total_train_step, loss))

    # 测试步骤
    net.eval()

    total_test_loss = 0
    total_accuracy = 0

    with torch.no_grad():
        for inputs, targets in test_dataloader:
            inputs = inputs.to(device)
            targets = targets.to(device)

            outputs = net(inputs)
            loss = loss_func(outputs, targets)
            total_test_loss += loss
            accuracy = (outputs.argmax(1) == targets).sum()
            total_accuracy += accuracy

        total_test_step += 1

        print('测试集上的Loss: {}'.format(total_test_loss))
        print('正确率: {}'.format(total_accuracy / test_size))

        writer.add_scalar('test_loss', total_test_loss, total_test_step)
        writer.add_scalar('test_accuracy', total_accuracy / test_size, total_test_step)

    # 保存训练模型
    if (i + 1) % 5 == 0:
        torch.save(net, 'net_2_{}.pth'.format(i + 1))
        print('模型已保存')

writer.close()