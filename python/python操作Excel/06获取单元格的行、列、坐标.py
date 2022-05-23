#   .row获取某个格子的行数;
#   .columns获取某个格子的列数;
#   .coordinate获取某个格子的坐标
import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径

workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类型
sheet=workbook.active   #获取活动表
cell=sheet.cell(row=3,column=2) #获取第三行第四列的数据
print(cell.value,cell.row,cell.column,cell.coordinate)#结果 行 列 坐标