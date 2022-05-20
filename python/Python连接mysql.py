import pymysql
class MySQL:
    def __init__(self):
        self.connect()
    def connect(self):  #连接数据库
        try:
            db = pymysql.connect(
                host='',
                port=3306,
                user='root',
                passwd='123456',
                db='itcast',
                charset='utf8'
                )
            return db
        except Exception:
            raise Exception("数据库连接失败")

    def implement(self,SQL):    #执行SQL语句
        db = self.connect()
        cursor = db.cursor()
        try:
            cursor.execute(SQL)
            db.commit()
            #print('查询结果：', cursor.fetchall())
            data=cursor.fetchall()
            for i in data:
                for j in i:
                    print(i)
        except Exception:
            db.rollback()
            print("查询失败")

        cursor.close()
        db.close()

if __name__ == '__main__':
    a = MySQL()
    a.implement('select * from emp2 where salary<20000')
