# 加密函数，对给定字符串 str 以 k 进行加密
def lock(str, k):
    temp = list(str)
    for i in range(len(temp)):
        if temp[i] >= 'a' and temp[i] <= 'z':
            temp[i] = chr(ord(temp[i]) + k)
            if temp[i] > 'z':
                temp[i] = chr(ord(temp[i]) - 26)
            if temp[i] < 'a':
                temp[i] = chr(ord(temp[i]) + 26)
        elif temp[i] >= 'A' and temp[i] <= 'Z':
            temp[i] = chr(ord(temp[i]) + k)
            if temp[i] > 'Z':
                temp[i] = chr(ord(temp[i]) - 26)
            if temp[i] < 'A':
                temp[i] = chr(ord(temp[i]) + 26)
    str = ''.join(temp)
    return str


# 读取文件 3-1.txt 中的内容并加密
file = open("Python\\Homework\\3-1.txt", 'r')
str = file.read()
file.close()

k = int(input("请输入您需要加密的位数(1~25)："))
while k < 1 or k > 25:
    k = int(input("请输入正确范围(1~25)："))
lock_str = lock(str, k)
print("加密后的文件信息如下：\n", lock_str, sep='', end='')
print("解密后的文件信息如下：\n", lock(lock_str, -k), sep='', end='')
