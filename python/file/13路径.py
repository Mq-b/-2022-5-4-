import os
print(os.getcwd())  #输出当前目录

#1、相对路径
with open('文件.txt') as file:                #通过相对路径打开文件
    pass

#2、绝对路径
print(os.path.abspath('文件.txt'))            #获取绝对路径

#3、拼接路径
print(os.path.join('D:\文件','文件.txt'))      #拼接字符串，将多个路径拼接在一起
#如果在使用拼接的时候有多个绝对路径，那么以从左到右为准，最后一次出现的路径为准进行拼接，其他参数会被忽略，如下
print(os.path.join("C:\\Users\\AMD",'D:自用',"c&&c++"))   #D:自用\c&&c++