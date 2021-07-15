import random

print("游戏开始！您共有 7 次机会猜词")
rand = random.randint(1, 274926)
txt = open("Python\\Homework\\hangman.txt", 'r')
for i in range(rand - 1):
    txt.readline()
word = txt.readline().strip('\n')

num = 7
now_word = []
for i in range(len(word)):
    now_word.append('_')

# print(word)

flag = False
while (not flag) and num:
    print("您现在还有", num, "次机会：", end='')
    print(' '.join(now_word))
    guess = input("请输入您猜测的字母：")
    for i in range(len(word)):
        if guess == word[i]:
            now_word[i] = guess
    if word.count(guess):
        print("单词中含有本字母\n")
    else:
        print("单词中不含本字母\n")
        num -= 1
    if ''.join(now_word) == word:
        flag = True

if flag:
    print("恭喜你，猜对了！")
else:
    print("很遗憾，猜错了！")
print("单词为：", word)
