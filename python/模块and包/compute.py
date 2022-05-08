import rectangle as r      #导入矩形模块
import circular as c       #导入圆形模块
if __name__=='__main__':   #程序从这里开始执行 可以有多个模块 , 但只有一个文件里的__name__为main
    print('圆的周长为:',c.girth(10))
    print('矩形的周长为:',r.girth(10,20))