# insert_rows(idx=数字编号, amount=要插入的行数)，插入的行数是在idx行数的下方插入
# insert_cols(idx=数字编号, amount=要插入的列数)，插入的位置是在idx列数的左侧插入
import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)

workbook=openpyxl.load_workbook('test.xlsx')
sheet=workbook.active
print('当前活动表是:'+str(sheet))

sheet.insert_rows(idx=3,amount=2) #在第三行插入两行空行
sheet.insert_cols(idx=2,amount=1) #在第二列插入一列空列
workbook.save('test.xlsx')
