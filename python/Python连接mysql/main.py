from py_mysql import*
if __name__ == '__main__':
    a = MySQL()
    #a.implement(['select * from emp2 where salary<20000;','select * from user;','select 66666;','show tables;','show index from emp;'])
    a.implement(['update emp set name=\'张三2020\' where name=\'张三\' ;'])
    a.implement(['insert into emp values(9,009,\'李四\',\'男\',20,\'110\',\'北京\',\'2020-01-02\')'])
    # a.implement(['show engines;'])
    # a.implement(['select lower (\'Hello\');'])
    # a.implement(['show engines;'])
    # a.implement(['show variables like \'sort_buffer_size\';'])
    # 只要连接了mysql 不管是不是一个数据库的表都可以直接访问    注意传参一定要以列表的方式