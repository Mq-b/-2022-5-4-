import xlsxwriter
import os

path = r"C:\Users\AMD\Desktop"
os.chdir(path)

# 创建一个名为【demo.xlsx】工作簿
workbook=xlsxwriter.Workbook('demo.xlsx')

# 创建一个名为【2018年销售量】工作表
worksheet=workbook.add_worksheet('2018年销售量')

# 使用write_row方法 为【2018年销售量】工作表添加一个表头
headings=['产品','销量','单价']
worksheet.write_row('A1',headings)
# 使用write方法，在【2018年销售量】工作表中插入一条数据；
# write语法格式：worksheet.write(行,列,数据)
data = ["苹果", 500, 8.9]
for i in range(len(headings)):
    worksheet.write(1, i, data[i])

workbook.close()
#也可也使用之前的按照工作表插入数据