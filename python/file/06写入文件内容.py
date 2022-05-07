file=open('文件.txt','a+')
file.write('66666666666666')        #使用write的前提是在打开文件的时候模式为可以写入的，a，w，a+都行
file.close()