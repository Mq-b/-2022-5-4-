class Test:
    a=0
    def t1(self):
        self.a+=1
    @classmethod
    def t2(cls):
        cls.a+=1
    @staticmethod
    def t3():
        a=10
a=Test()
a.t1()
a.t1()
print(a.a,Test.a)   #由此可得普通方法无法改变类的属性

a.t2()
a.t2()
print(a.a,Test.a)  #由此可得，类方法只能访问类的属性，不能访问实例的属性

a.t3()
print(a.a,Test.a)  #由此可得，静态方法既无法改变类的属性也无法改变实例的属性

#且下面这样不适用于类方法
Test.t1(a)
#Test.t2(a)  #这是错误的
#Test.t3(a)   #这也是错误的       由此可得，只有普通方法才能类名直接调用
print(a.a,Test.a)