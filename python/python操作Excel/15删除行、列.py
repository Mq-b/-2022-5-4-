# delete_rows(idx=数字编号, amount=要删除的行数)
# delete_cols(idx=数字编号, amount=要删除的列数)
import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)

workbook=openpyxl.load_workbook('test.xlsx')
sheet=workbook.active
print('当前活动表是:'+str(sheet))

sheet.delete_rows(idx=3,amount=2) #在第三行删除两行
sheet.delete_cols(idx=2,amount=1) #在第二列删除一列
workbook.save('test.xlsx')
#删除完之后会自动对其