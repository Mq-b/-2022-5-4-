#读取全部行的作用同调用read()放大时不指定size类似，只不过读取全部行的时候，返回的是一个字符串列表
#每个元素为文件的一行内容。读取全部行，使用的是文件对象的readiness()方法
with open('古诗.txt','r',encoding='utf-8') as file:
    string=file.readlines()        #读取全部行，放入字符串列表
    print(string)
    file.seek(0)                  #记得需要重置文件指针
    string=file.read()            #用read()读取全部内容
    print(string)
file.close()