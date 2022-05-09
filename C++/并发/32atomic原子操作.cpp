#include<iostream>
#include<thread>
#include<mutex>
#include <atomic>
//int g_mycout = 0;	//定义一个全局变量
std::atomic<int>g_mycout = 0;	//我们封装了一个类型为int的对象（值）；我们可以像操作一个int类型变量一样来操作这个g_mycout
//std::mutex g_my_mutex;
void mythread()
{
	for (int i = 0; i < 1000000; i++)
	{
		//g_my_mutex.lock();
		//g_mycout++;
		//g_my_mutex.unlock();

		g_mycout++;//对应的操作是一个原子操作（不会被打断）
		g_mycout += 1;//支持
		//g_mycout = g_mycout + 1;	//结果不对,不是原子操作
	}
}

std::atomic<bool>g_ifod = false;	//线程标记退出，这里是原子操作，防止读和写乱套

void mythread2()
{
	std::chrono::milliseconds dura(1000);	//一秒钟
	while (g_ifod == false)
	{
		//系统没要求线程退出，所以本线程可以干自己的事情
		std::cout << "thread id= " << std::this_thread::get_id() << "运行中..." << std::endl;
		std::this_thread::sleep_for(dura);
	}
	std::cout << "thread id= " << std::this_thread::get_id() << "运行结束...." << std::endl;
}

int main() {
/*三、std::atomic原子操作

3.1 原子操作概念引出范例：
互斥量：多线程编程中 用于保护共享数据：先锁住， 操作共享数据， 解锁。

有两个线程，对一个变量进行操作，一个线程读这个变量的值，一个线程往这个变量中写值。

即使是一个简单变量的读取和写入操作，或者同时写，如果不加锁，也有可能会导致读写值混乱（一条C语句会被拆成3、4条汇编语句来执行，所以仍然有可能混乱）*/

	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
	std::cout << g_mycout << std::endl;	//结果不可预料,加锁即可解决

	//大家可以把原子操作理解成一种不需要用到互斥量（无锁）技术的多线程并发编程方式
	//或者也可以理解成原子操作是在多线程中不会被打断的程序执行片段；原子操作比互斥量效率上更胜一筹
	//互斥量的加锁一般是针对一个代码段（几行代码），而原子操作（针对）的一般都是一个变量，而不是一个代码段

	//原子操作，一般都是指“不可分割的操作”；也就是说这种操作要么是完成状态，要么是没完成的，不可能出现半完成状态
	//std::atomic来代表原子操作，std::atomic是个类模板，其实std::atomic
	std::thread mytobj1(mythread2);
	std::thread mytobj2(mythread2);
	std::chrono::milliseconds dura(5000);	//五秒钟
	std::this_thread::sleep_for(dura);
	g_ifod = true;	//对原子对象的写操作，让线程自行运行结束；
	mytobj1.join();
	mytobj2.join();
	std::cout << "程序执行完毕，退出" << std::endl;
}