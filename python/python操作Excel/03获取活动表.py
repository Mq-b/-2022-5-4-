import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径
workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类的值
sheet=workbook.active   #获取活动表
print(sheet)