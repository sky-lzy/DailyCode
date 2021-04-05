import math


def isPrime(n):
    k = int(math.sqrt(n))
    i = 2
    flag = 1
    while (i <= k) & flag:
        if n % i == 0:
            flag = 0
        i += 1
    return flag


n = int(input())
if isPrime(n):
    print('%d是素数' % n)
else:
    print('%d不是素数' % n)
