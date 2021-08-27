# 本文件使用函数式生成素数序列


# 从3开始的奇数序列
def odd_list():
    n = 1
    while True:
        n += 2
        yield n


# 不能被 n 整除的数
def not_divisible(n):
    return lambda x: x % n != 0


# 素数序列
def prime_list():
    yield 2
    it = odd_list()
    while True:
        n = next(it)
        yield n
        it = filter(not_divisible(n), it)


# 生成素数序列
g = prime_list()
for i in range(1000):
    print(next(g), end=' ')
print('')
