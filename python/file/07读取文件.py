with open('文件.txt','r') as file:
    string=file.read(9)     #调用read函数读取前面9个字符,read函数是从文件开始的时候开始读取的
    print(string)
file.close()