import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)
workbook = openpyxl.load_workbook('test.xlsx')
sheet=workbook.active
print('当前活动表是:'+str(sheet))
data=[
    ['素子',23],
    ['巴特',24],
    ['塔奇克马',2]
]
for row in data:
    sheet.append(row)
workbook.save('test.xlsx')
# 使用append方法插入数据