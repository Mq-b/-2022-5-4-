import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  # 修改工作路径

workbook = openpyxl.Workbook()
sheet = workbook.active
sheet.title = '1号sheet'
workbook.save('1.xlsx') #另存为另一个文件
# 不写第9行，默认创建sheet
# 写了第9行，创建指定名字的sheet表