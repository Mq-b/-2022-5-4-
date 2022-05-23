# Alignment(horizontal=水平对齐模式,vertical=垂直对齐模式,text_rotation=旋转角度,wrap_text=是否自动换行)
# 水平对齐：‘distributed’，‘justify’，‘center’，‘left’， ‘centerContinuous’，'right，‘general’
# 垂直对齐：‘bottom’，‘distributed’，‘justify’，‘center’，‘top’
import os
import openpyxl.styles

path=r"C:\Users\AMD\Desktop"
os.chdir(path)

workbook = openpyxl.load_workbook('test.xlsx') 
sheet = workbook.active
print('当前活动表是：' + str(sheet))

cell = sheet['A1']
alignment = openpyxl.styles.Alignment(horizontal="center", vertical="center", text_rotation=0, wrap_text=True)
cell.alignment = alignment #变成居中对齐

#for循环处理多列
for i in sheet['A']:
    i.alignment=alignment

workbook.save('test.xlsx')