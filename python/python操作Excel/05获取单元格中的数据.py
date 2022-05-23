import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径

workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类型
sheet=workbook.active   #获取活动表
#print(sheet.dimensions) #获取表格的尺寸大小
cell1=sheet['A1']
cell2=sheet['B7']
print(cell1.value,cell2.value)  #姓名 18