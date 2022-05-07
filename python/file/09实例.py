with open('古诗.txt','a+',encoding='utf-8') as file:  #追加模式打开，以utf-8模式写入
    s=input('古诗=')         #手动输入数据
    file.write(s)           #写入文件
    file.seek(0)            #重置文件指针的位置，因为当写入完文件后，文件的指针依旧偏移到了数据的末尾
    string=file.read()      #读取文件全部的数据
    print(string)           #打印
file.close()                #关闭文件对象

#值得一提的是read()方法只能从文件开始的位置读取，也只能使用r或者r+，一定要使用a+就需要先重置文件指针位置