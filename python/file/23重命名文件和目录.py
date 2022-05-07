import os
src="D:\自用\新建 文本文档.txt"         #原始目录
dst="D:\自用\测试.txt"                 #更改文件名后的目录
if os.path.exists(src):
    os.rename(src,dst)
    print('文件重命名完毕')
else :
    print('文件不存在')

#----------------重命名目录-----------------
#目录重命名和文件没区别，只要把文件路径换成目录即可
src="666"         #原始目录
dst="Test"                 #更改文件名后的目录
if os.path.exists(src):
    os.rename(src,dst)
    print('目录重命名完毕')
else :
    print('目录不存在')