class students:
    def __init__(self,name,gender,age):
        self.__name=name
        self.__gender=gender
        self.__age=age
    def __add__(self,other):    #自己实现+
        return self.__name+' '+other.__name
    def __len__(self):         #自己实现len
        return self.__age
    def show(self):
        print(self.__name,self.__gender,self.__age)

demo=students('张飞','男',23)
demo2=students('李四','男',12)
students.show(demo)
students.show(demo2)
print(demo+demo2)