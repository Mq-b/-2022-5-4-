import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径

workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类型
sheet=workbook['Sheet1']    #获取指定sheet表
print(sheet.dimensions) #获取表格的尺寸大小
