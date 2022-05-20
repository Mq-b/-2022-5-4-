import pymysql
class MySQL:
    def __init__(self):
        self.connect()
    def connect(self,host_='',port_=3306,user_='root',passwd_='123456',db_='itcast',charset_='utf8'):  #连接数据库
        try:
            db = pymysql.connect(
                host=host_,       #主机连接本机可不写
                port=port_,       #端口号默认都这个
                user=user_,       #mysql的用户名
                passwd=passwd_,   #密码
                db=db_,           #数据库名
                charset=charset_  #编码
                )
            return db   #连接成功就返回一个对象
        except Exception:
            raise Exception("数据库连接失败")

    def implement(self,SQL):    #执行SQL语句
        db = self.connect()
        cursor = db.cursor()
        try:
            cursor.execute(SQL)
            db.commit()
            for i in cursor.fetchall(): #打印数据 fetchall返回一个含有所有数据的元组
                print(i)
        except Exception:
            db.rollback()
            print("查询失败")
        cursor.close()
        db.close()