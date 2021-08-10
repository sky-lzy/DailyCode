此文件夹 "Python\Homework\Final_work" 为课程《计算机程序设计基础（2）》夏季小学期的python大作业
net.py      文件包含所有使用的网络模型
train.py    文件为使用网络模型进行训练、验证、优化的程序
test.py     文件为使用训练好的网络模型进行测试
mydata.py   文件封装了需要用到的 MyData 类

注：训练、验证、测试集的比例为 4:1:5 ，其中测试集的内容固定，而训练集和验证集为每次随机分配

第一次：
网络模型：      Net_1
优化器：        Adam
学习率：        0.001 (无递减)
训练次数：      50
batch_size:    32
输入数据：      3*64*64
验证集收敛:     94.5%左右
稳定收敛轮数:   20
测试集准确率:   95.1%
模型保存：      "Python\Homework\Final_work\net_1_model"
数据保存：      "Python\Homework\Final_work\logs_net_1" (tensorboard)

第二次：
