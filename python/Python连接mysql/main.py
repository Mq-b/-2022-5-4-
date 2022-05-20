from py_mysql import*
if __name__ == '__main__':
    a = MySQL()
    a.implement('select * from emp2 where salary<20000;')
    #使用不同数据库 重新连接
    a.connect('',3306,'root','123456','test','utf8')
    a.implement('select * from user;')