fin = open('Python\\Homework\\1-1_in.txt', 'r', encoding='utf-8')
fout = open('Python\\Homework\\1-1_out.txt', 'w', encoding='utf-8')

str_in = fin.read()
list_in = str_in.split(' ')
i = 0
while i < len(list_in):
    list_in[i] = float(list_in[i])
    i += 1
(income, savings, profit, amount) = list_in
savings /= 100
profit /= 100

total = income * savings
year = 1
temp = 0
while total < amount:
    temp = total * profit + income * savings
    total += temp
    year += 1
month = int((amount + temp - total) / (temp / 12))

if month == 0:
    fout.write("按照您目前的情况，支付首付需要 " + str(year) + " 年")
else:
    year -= 1
    fout.write("按照您目前的情况，支付首付需要 " + str(year)+" 年 " + str(month) + " 个月")

fin.close()
fout.close()
