import pymysql
class MySQL:
    def connect(self,host_='',port_=3306,user_='root',passwd_='123456',db_='itcast',charset_='utf8'):  #连接数据库
            db = pymysql.connect(
                host=host_,       #主机连接本机可不写
                port=port_,       #端口号默认都这个
                user=user_,       #mysql的用户名
                passwd=passwd_,   #密码
                db=db_,           #数据库名
                charset=charset_  #编码
                )
            return db   #连接成功就返回一个对象

    def implement(self,SQL):  #执行SQL语句的函数
        db = self.connect()   #连接数据库
        cursor = db.cursor()  #返回一个数据库的光标
        try:
            for i in range(len(SQL)):   #循环遍历SQL语句
                sql=SQL[i]
                if sql[0:6]=='select' or sql[0:4]=='show':
                    cursor.execute(SQL[i])  #开始事务
                    db.commit()             #提交事务
                    for j in cursor.fetchall():  # 遍历打印数据 fetchall返回一个含有所有数据的元组
                        print(j)
                else:
                    cursor.execute(SQL[i])  #开始事务
                    db.query(SQL[i])        #执行SQL
                    db.commit()             # 提交事务

        except Exception:
            db.rollback()    #如果执行失败就必须回滚到事务执行之前的状态
            print("查询失败")
        cursor.close()  #光标就是迭代器 先关闭在数据里的
        db.close()  #关闭和数据库的连接