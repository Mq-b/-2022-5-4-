import os
import openpyxl
import openpyxl.styles

path=r"C:\Users\AMD\Desktop"
os.chdir(path)

workbook = openpyxl.load_workbook('test.xlsx')
sheet = workbook.active
print('当前活动表是：'+str(sheet))

cell = sheet['A1']
font = cell.font
print('当前单元格的字体样式是')
print(font.name, font.size, font.bold, font.italic, font.color)

# openpyxl.styles.Font(name=字体名称,size=字体大小,bold=是否加粗,italic=是否斜体,color=字体颜色)
# 修改字体样式
cell = sheet['A1']
cell.font = openpyxl.styles.Font(name="微软雅黑", size=20, bold=True, italic=True, color="FF0000")

# 我们可以使用for循环改变多行多列的数据
for i in sheet['A']:    #注意这里是便利单列A
    i.font = openpyxl.styles.Font(name="微软雅黑", size=20, bold=True, italic=True, color="FF0000")

workbook.save('test.xlsx')