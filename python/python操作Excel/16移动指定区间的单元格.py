#move_range(“数据区域”,rows=,cols=)：正整数为向下或向右、负整数为向左或向上
import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  # 修改工作路径

workbook = openpyxl.load_workbook('test.xlsx')  
sheet = workbook.active  # 获取活动表
print('当前活动表是：' + str(sheet))

sheet.move_range(sheet.dimensions,rows=10,cols=3)  # dimensions是返回数据范围
workbook.save('test.xlsx')