num = 0


def permutation(str, k):
    global num
    n = len(str)
    if k == n - 1:
        print(''.join(str))
        num += 1
    else:
        i = k
        finish = []
        while i < n:
            if finish.count(str[i]) == 0:
                (str[i], str[k]) = (str[k], str[i])
                str2 = str[0: k + 1: 1] + sorted(str[k + 1: n: 1])
                permutation(str2, k + 1)
                (str[i], str[k]) = (str[k], str[i])
                finish.append(str[i])
            i += 1


str_list = list(input("请输入要进行全排列的字符串："))
str_list.sort()
permutation(str_list, 0)
print("一共有", num, "种不重复的全排列方式")
