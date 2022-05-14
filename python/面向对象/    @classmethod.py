class func:
    a=0
    def __init__(self):
        self.a+=1

func()
func()
func()
print(func().a)#结果是1，Python和cpp一样不会记录，但是可以像使用static一样的效果 使用 @classmethod

class func2:
    a=0
    @classmethod
    def __init__(self):
        self.a+=1

func2()
func2()
func2()
print(func2().a)