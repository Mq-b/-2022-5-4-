import setting.PI
print(setting.PI.PI)
#要先把包放到同级目录下，然后像模块一样导入即可，就是先导入包然后点出模块

from setting import PI  #通过这种方式导入模块后，在使用时不需要加上包的前缀了
print(PI.PI)

from setting.PI import PI   #from+完整包名+模块名+import+定义名，也就是需要导入的具体变量，函数，类啥的的
print(PI)

from setting.PI import *    #和上面的格式一样，但是可以直接用*代替表示导入包内指定模块内所有的信息
print(PI)

#另一个模块
from setting.size import *
if __name__=='__main__':
    print(getWidth(),getHeight())

#记住，包是一个文件夹，里面得先有一个__init__.py的文件表示这是一个包，然后写其他模块，包必须写在项目的同级目录下才能被导入