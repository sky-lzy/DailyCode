import socket  #示例：导入socket包（python自带）
import numpy  #示例：导入numpy包（常用python第三方库，需提前安装；anaconda已默认安好）


a = True
b = False

if a:
    print('变量a是' + str(a))   # 字符串拼接，直接用+即可，python已经自带基本的运算符重载

if b:
    print('这句话不会被执行')
else:
    print('变量b是' + str(b))

# for循环：生成一个长度为10的循环结构，其中i为循环变量
for i in range(10):
    print(i)   # 标准输出打印

# while 循环
j = 10
while j > 0:
    j -= 1    # j = j - 1
    print(j)  

# 列表遍历
k = ['a', 'b', 'c', 'd', 'e']
for e in k:
    print(e)



# 字典使用
my_dict = {'a':1, 'b':2, 'c':3}
for key, value in my_dict.items():
    print(key)
    print(value)
    print(my_dict[key])
my_dict['d'] = 4
print(my_dict['d'])
del(my_dict['d'])


# 简单的类
class SimpleClass():
    def __init__(self):
        # 可以理解为构造函数
        self.a = 1   # 类内变量；python中没有c一样的复杂变量保护，等同于public
    
    def change_a(self,b):
        # 类内函数，可以调用类中所有元素；第一个参数必须为self
        self.a = b

c = SimpleClass()
print(c.a)
c.change_a(2)
print(c.a)


# 获取标准输入
msg = input()
print(msg)

# 异常处理
try:
    print(abcdefg)  # 打印一个不存在的变量，会报错
except:
    print('出错了')  # try中语句报错，会调用except中的内容