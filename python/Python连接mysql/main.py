from py_mysql import*
if __name__ == '__main__':
    a = MySQL()
    #a.implement(['select * from emp2 where salary<20000;','select * from user;','select 66666;','show tables;','show index from emp;'])
    #a.implement(['update emp set name=\'归故里123\' where name=\'柳岩100\' ;'])

    #a.implement('show engines;')
    a.implement(['select lower (\'Hello\');'])
    a.implement(['show engines;'])
    # 只要连接了mysql 不管是不是一个数据库的表都可以直接访问    注意传参一定要以列表的方式