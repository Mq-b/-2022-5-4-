import os
fileinfo=os.stat('图片1.png')                         #获取文件的基本信息

print('文件路径:',os.path.abspath('图片1.png'))
print('索引号:',fileinfo.st_ino)
print('设备号',fileinfo.st_dev)
print('文件大小',fileinfo.st_size)
print('最后一次访问时间',fileinfo.st_atime)
print('最后一次修改时间',fileinfo.st_mtime)
print('最后一次状态变化时间',fileinfo.st_ctime)
#结果都是时间戳，要转换