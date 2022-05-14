import datetime

class People(object):
  country = 'China'
  @staticmethod
  # 静态方法
  def time_():
    print(datetime.datetime.now().strftime('%Y-%m-%d  %H:%M:%S'))

class func2:
  a = 0
  @classmethod  #类方法
  def __init__(self):
    self.a += 1
  #classmethod的第一个参数为类本身(cls)，正如实例方法的第一个参数为对象本身(self);
  #staticmethod第一个参数不需要传入cls或self，故staticmethod中是无法访问类和对象的数据的
  # classmethod可以设置修改类属性；也可以实例化对象；
  # staticmethod无法访问类或对象的数据，所以可把它当作一个辅助功能方法用，里面包含一些与该类有关的逻辑代码。比如validate(*args)
  # 比如上面这个静态方法

func2()
func2()
func2()
print(func2().a)    #我们可以看出对类的改变是有记录的
People.time_()#直接调用
