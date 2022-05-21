from py_mysql import*
if __name__ == '__main__':
    a = MySQL()
    a.implement(['select * from emp2 where salary<20000;','select * from user;','select 66666;','show tables;','show index from emp;'])
    a.implement(['update emp set name=\'归故里牛马\' where name=\'柳岩\' ;'])
    # 只要连接了mysql 不管是不是一个数据库的表都可以直接访问