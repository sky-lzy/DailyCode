income = float(input("请输入您的年收入（万元）： "))
savings = float(input("请输入您的年存款额比例（%）： ")) / 100
profit = float(input("请输入您的年化投资收益（%）：")) / 100
amount = float(input("请输入您目标房的首付（万元）："))

total = income * savings
year = 1
while total < amount:
    temp = total * profit + income * savings
    total += temp
    year += 1
month = int((amount + temp - total) / (temp / 12))

if month == 0:
    print("按照您目前的情况，支付首付需要", year, "年")
else:
    year -= 1
    print("按照您目前的情况，支付首付需要", year, "年", month, "个月")
