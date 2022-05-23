#1.使用sheet['A1:A5']拿到指定区间
#2.使用两个for循环拿到数据
import os
import openpyxl

path=r"C:\Users\AMD\Desktop"
os.chdir(path)  #修改工作路径

workbook=openpyxl.load_workbook('test.xlsx')    #返回一个workbook数据类型的值
sheet=workbook.active   #获取活动表
print('当前活动表是',sheet)

cell=sheet['A1:B5'] #获取A1到A5的数据

print(cell)

#遍历二维元组打印A1到B5的数据 两列的数据打印一列可读性较差 看09
for i in cell:
    for j in i:
        print(j.value)