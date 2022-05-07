with open('文件.txt','w')as file:     #把文件打开后产生的结果保存到file变量中
    pass

#with的好处是在处理文件的时候无论是否抛出异常，都能保证with语句执行完毕后关闭已经打开的文件
