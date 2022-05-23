# xlsxwriter
# xlsxwriter模块一般是和xlrd模块搭配使用的，
# xlsxwriter：负责写入数据，
# xlrd：负责读取数据。
import xlsxwriter
import os

path = r"C:\Users\AMD\Desktop"
os.chdir(path)

# 这一步相当于创建了一个新的"工作簿"；
# "demo.xlsx"文件不存在，表示新建"工作簿"；
# "demo.xlsx"文件存在，表示新建"工作簿"覆盖原有的"工作簿"；
workbook = xlsxwriter.Workbook("demo.xlsx")

# close是将"工作簿"保存关闭，这一步必须有，否则创建的文件无法显示出来。
workbook.close()