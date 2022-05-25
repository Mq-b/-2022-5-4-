import xlsxwriter
import os
import random
path = r"C:\Users\AMD\Desktop"
os.chdir(path)

workbook=xlsxwriter.Workbook('2022年五月体温.xlsx')
worksheet=workbook.add_worksheet('体温表')

headings=['日期','姓名','体温']
worksheet.write_row('A1',headings)

for i in range(1,101):  
    for j in range(len(headings)):
        list_=['2022-5-'+str(random.randint(1,31)),str(i)+'A',format(random.uniform(36.8,37.3), '.2f')]
        worksheet.write(i,j,list_[j])   

workbook.close()