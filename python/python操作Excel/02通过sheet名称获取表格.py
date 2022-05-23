import os
import openpyxl

path =r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径
workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类型的值
print(workbook.sheetnames)  #打印Excel表中的所有表

sheet=workbook['Sheet1']    #获取指定sheet表
print(sheet)