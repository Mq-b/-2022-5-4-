import os
path='D:\\demo'                 #指定要创建的目录
if not os.path.exists(path):    #判断目录是否存在   exists方法是当路径存在就为假，不存在就为真，所以使用if not
    os.mkdir(path)              #创建目录
else:
    print('该目录已经存在！')