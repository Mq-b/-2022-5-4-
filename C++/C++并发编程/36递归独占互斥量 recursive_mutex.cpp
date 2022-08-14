#include<iostream>
#include<thread>
#include<mutex>

std::recursive_mutex mymutex;
void test() {
	std::lock_guard<std::recursive_mutex>myguard(mymutex);
	mymutex.lock();
	std::cout << "1" << std::endl;
	mymutex.unlock();
	mymutex.lock();
	mymutex.unlock();
}
int main()
{
/*四、递归独占互斥量 std::recursive_mutex
std::mutex 独占式互斥量

std::recursive_mutex：允许在同一个线程中同一个互斥量多次被 lock() ，（但是递归加锁的次数是有限制的，太多可能会报异常），效率要比mutex低。

如果你真的用了 recursive_mutex 要考虑代码是否有优化空间，如果能调用一次 lock()就不要调用多次。*/
	std::thread a(test), a2(test);
	a.join();
	a2.join();
}