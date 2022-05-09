#include<iostream>
#include<mutex>
#include<thread>

//std::lock()函数模板：用于处理多个互斥量的时候才出场
//能力：同时锁住一个或者两个以上的互斥量（至少两个，多了不限，1个不行）；
//它不存在这种因为再多个线程中 因为锁的顺序问题导致的死锁的风险问题；
//std::lock();如果互斥量中有一个没有锁住，它就在那里等着，等所有互斥量都锁住，它才能往下走（返回）
//要嘛两个互斥量都锁住，要嘛两个互斥量都没锁住。如果只锁了一个，另一个没锁成功，则它立即把已经锁住的解锁

using namespace std;
int g_i = 0;
std::mutex g_i_mutex;
std::mutex g_j_mutex;

void safe_increment()
{
	/*同时锁两个*/
	std::lock(g_i_mutex, g_j_mutex);
	for (int i = 0; i < 100; i++)
	{
		++g_i;
	}
	/*需要手动解锁*/
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
	g_i_mutex.unlock();
	g_j_mutex.unlock();
}

int main()
{
	std::cout << "main: " << g_i << '\n';
	std::thread t1(safe_increment);
	std::thread t2(safe_increment);
	t1.join();
	t2.join();
	std::cout << "main: " << g_i << '\n';
	return 0;
}
//总结:std::lock（）：一次锁定多个互斥量：谨慎使用（建议一个一个锁）