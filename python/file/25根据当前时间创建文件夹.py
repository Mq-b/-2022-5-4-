import os
import time

def nsfile(s):
    b = os.path.exists("D:\\testFile\\")
    if b:
        print("该目录存在！")
    else:
        os.mkdir("D:\\testFile\\")              # 生成文件
    for i in range(1, s + 1):
        # 获取当前系统时间
        localTime = time.strftime("%Y%m%d%H%M%S", time.localtime())
        # 以当前系统时间作为文件名称
        filename = "D:\\testFile\\" + localTime + ".txt"        # a:以追加模式打开（必要时可以创建）append;b:表示二进制
        f = open(filename, 'ab')
        testnote = '文件测试'                  # 文件内写入的信息
        f.write(testnote.encode('utf-8'))    # 写入文件信息，以utf-8的编码写入
        f.close()
        print("file" + " " + str(i) + ":" + str(localTime) + ".txt")#打印出来创建的文件的名字
        time.sleep(1)     # 休眠一秒
    print('生成文件成功！')

if __name__ == '__main__':
    s = int(input("请输入需要生成的文件数："))    # 获取输入的文件个数
    nsfile(s)