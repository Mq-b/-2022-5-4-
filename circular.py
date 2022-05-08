import math
PI=math=math.pi
def girth(r):
    return round(2*PI*r,2)      #计算圆周长并保留两位小数，round函数就是保留小数的
def area(r):
    return round(PI*r**2,2)     #计算圆面积并保留两位小数
if __name__=='__main__':
    print(girth(10))