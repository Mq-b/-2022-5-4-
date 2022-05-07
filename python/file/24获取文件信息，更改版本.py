import os
def formatTime(longtime):
    import time
    return time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(longtime))  #格式化时间
def formatByte(number):
    for(scale,label)in [(1024*1024*1024,'GB'),(1024*1024,'MB'),(1024,'KB')]:#处理内存
        if number>=scale:
            return '%.2f %s'%(number*1.0/scale,label)
        elif number==1:
            return '1 字节'
        else:
            byte='%.2f'%(number or 0)
    return (byte[:-3]if byte.endswith('.00')else byte)+'字节'

if __name__=='__main__':
    fileinfo=os.stat('图片1.png')
    print('文件路径:', os.path.abspath('图片1.png'))
    #输出基本信息
    print('索引号:', fileinfo.st_ino)
    print('设备号', fileinfo.st_dev)
    print('文件大小', formatByte(fileinfo.st_size))
    print('最后一次访问时间', formatTime(fileinfo.st_atime))
    print('最后一次修改时间', formatTime(fileinfo.st_mtime))
    print('最后一次状态变化时间', formatTime(fileinfo.st_ctime))