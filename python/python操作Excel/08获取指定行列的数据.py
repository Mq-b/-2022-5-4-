import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  # 修改工作路径

workbook = openpyxl.load_workbook('test.xlsx')  # 返回一个workbook数据类型的值
sheet = workbook.active  # 获取活动表
print('当前活动表是：' + str(sheet))

cell = sheet['2']  # 获取第2行的数据

# 打印A1到A5的数据
for i in cell:
    print(i.value)