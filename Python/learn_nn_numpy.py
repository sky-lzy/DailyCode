# 本文件是以numpy库构建简单的神经网络
from os import times
import numpy as np

# 前向传播函数
def affine_forward(x, w, b):
    out = None                  # 初始化输出
    N = x.shape[0]              # 获取第零维长度
    x_row = x.reshape(N, -1)    # 重塑x，得到二维张量
    out = np.dot(x_row, w) + b  # 仿射变换
    cache = (x, w, b)           # 保存输入值
    return out, cache           # 返回值

# 反向传播函数
def affine_backward(dout, cache):
    x, w, b = cache                             # 读入缓存
    dx, dw, db = None, None, None               # 初始化返回值
    dx = np.dot(dout, w.T)                      # (N, D)
    dx = np.reshape(dx, x.shape)                # (N, d1, ... ,dk)
    x_row = x.reshape(x.shape[0], -1)           # (N, D)
    dw = np.dot(x_row.T, dout)                  # (D, M)
    db = np.sum(dout, axis=0, keepdims=True)    # (1, M)
    return dx, dw, db


X = np.array([[2, 1], [-1, 1], [-1, -1], [1, -1]])
t = np.array([0, 1, 2, 3])
np.random.seed(1)

input_dim = X.shape[1]
num_classes = t.shape[0]
hidden_dim = 50
reg = 0.001
epsilon = 0.001

w1 = np.random.randn(input_dim, hidden_dim)
w2 = np.random.randn(hidden_dim, num_classes)
b1 = np.zeros((1, hidden_dim))
b2 = np.zeros((1, num_classes))

for j in range(10000):
    H, fc_cache = affine_forward(X, w1, b1)
    H = np.maximum(0, H)  # ReLU激活函数
    relu_cache = H
    Y, cachey = affine_forward(H, w2, b2)

    probs = np.exp(Y - np.max(Y, axis=1, keepdims=True))
    probs /= np.sum(probs, axis=1, keepdims=True)

    N = Y.shape[0]
    print(probs[np.arange(N), t])
    loss = -np.sum(np.log(probs[np.arange(N), t])) / N

    dx = probs.copy()
    dx[np.arange(N), t] -= 1
    dx /= N
    dh1, dw2, db2 = affine_backward(dx, cachey)
    dh1[relu_cache <= 0] = 0
    dX, dw1, db1 = affine_backward(dh1, fc_cache)

    dw2 += reg * w2
    dw1 += reg * w1
    w2 += -epsilon * dw2
    w1 += -epsilon * dw1
    b2 += -epsilon * db2
    b1 += -epsilon * db1

test = np.array([[2, 2], [-2, 2], [-2, -2], [2, -2]])
H, fc_cache = affine_forward(test, w1, b1)
H = np.maximum(0, H)
relu_cache = H
Y, cachey = affine_forward(H, w2, b2)

probs = np.exp(Y - np.max(Y, axis=1, keepdims=True))
probs /= np.sum(probs, axis=1, keepdims=True)
print(probs)
for k in range(4):
    print(test[k, :], "所在象限为", np.argmax(probs[k, :]) + 1)
