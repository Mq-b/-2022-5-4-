with open('文件.txt','r') as file:
    file.seek(8)            #移动8位文件指针，相当于已经到了9
    string=file.read(10)    #从9的位置开始读取
    print(string)
file.close()