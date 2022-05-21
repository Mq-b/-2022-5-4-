from py_mysql import*
if __name__ == '__main__':
    a = MySQL()
    a.implement('select * from emp2 where salary<20000;')
    a.implement('select * from user;')
    #只要连接了mysql 不管是不是一个数据库的表都可以直接访问
    #为了简洁我们没提供更改连接参数的接口 如果要改 直接手动改默认参数