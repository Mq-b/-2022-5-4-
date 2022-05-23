import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  

workbook = openpyxl.load_workbook('test.xlsx')  
sheet = workbook.active 
sheet['A1'] = 'name'
workbook.save('test.xlsx')
# 使用索引直接修改单元格