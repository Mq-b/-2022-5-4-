#include<iostream>
#include<thread>
#include<shared_mutex>
using namespace std;
/*C++14提供了shared_mutex来解决读者-写者问题，也就是读写锁，和普通锁不一样，读写锁同时只能有一个写者或多个读者，但不能同时既有读者又有写者，读写锁的性能一般比普通锁要好。

shared_mutex通过lock_shared，unlock_shared，shared_lock进行读者的锁定与解锁；通过lock，unlock，unique_lock进行写者的锁定与解锁。*/
shared_mutex g_mutex;
std::string g_str;

void readLoop()
{
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		g_mutex.lock_shared();
		cout << g_str;
		g_mutex.unlock_shared();
	}
}

void writeLoop()
{
	int number = 0;
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		g_mutex.lock();
		g_str = to_string(number++) + "\n";
		g_mutex.unlock();
	}
}

int main()
{
	thread(writeLoop).detach();
	thread(writeLoop).detach();
	thread(readLoop).detach();
	thread(readLoop).detach();
	system("pause");
}
//也可以使用unique_lcok配合使用，类似于mutex