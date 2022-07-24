#include<unistd.h>
#include<stdio.h>
int main(){
	alarm(1);//一秒钟重复执行下面的代码
	for(int i=0;;i++){
		printf("%d\n",i);
	}
}
//我们可以这样运行，先编译，然后 time ./a.out
//最后会打印real  user   sys   三个时间，real表示程序实际运行的时间，user表示程序运行在用户空间所消耗的时间，sys是在内核运行所消耗的时间
//我们可以优化一下，time ./a.out > out 将这些输出到文件中，而非终端

/*alarm 函数：使用自然计时法。

	定时发送SIGALRM给当前进程。

	unsigned int alarm(unsigned int seconds);

		seconds：定时秒数

		返回值：上次定时剩余时间。

			无错误现象。

		alarm（0）； 取消闹钟。

	time 命令 ： 查看程序执行时间。   实际时间 = 用户时间 + 内核时间 + 等待时间。  等待时间是可能是在等内存，也可能是在等cpu,等设备。这个得占大头
*/