#include<mutex>
#include<iostream>
#include<thread>

std::timed_mutex my_mymutex;
void test() {
	std::chrono::milliseconds timeout(1);
	if (my_mymutex.try_lock_for(timeout)) {/*尝试锁互斥。阻塞直到经过指定的 timeout_duration 或得到锁，取决于何者先到来。成功获得锁时返回 true ， 否则返回 false 。*/
		//......拿到锁返回ture
		std::cout << "1毫秒内拿到锁了" << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		my_mymutex.unlock();
	}
	else
	{
		std::cout << "没有拿到锁" << std::endl;
		std::chrono::milliseconds sleeptime(100);
		std::this_thread::sleep_for(sleeptime);
	}
}
/*    try_lock_until()：
参数是一个未来的时间点，在这个未来的时间没到的时间内，如果拿到了锁头，流程就走下来，如果时间到了没拿到锁，流程也可以走下来。*/
void test2() {
	std::chrono::milliseconds timeout(1);
	if (my_mymutex.try_lock_until(std::chrono::steady_clock::now() + timeout)) {
		//......拿到锁返回ture
		std::cout << "1毫秒内拿到锁了" << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		my_mymutex.unlock();
	}
	else
	{
		std::cout << "没有拿到锁" << std::endl;
		std::chrono::milliseconds sleeptime(100);
		std::this_thread::sleep_for(sleeptime);
	}
}
int main() {
/*std::recursive_timed_mutex：是待超时的递归独占互斥量

5.1 std::timed_mutex：是待超时的独占互斥量

	try_lock_for()：

等待一段时间，如果拿到了锁，或者超时了未拿到锁，就继续执行（有选择执行）如下：*/
	std::thread a(test), a2(test), a3(test),a4(test);
	a.join();
	a2.join();
	a3.join();
	a4.join();

	/*    try_lock_until()：

参数是一个未来的时间点，在这个未来的时间没到的时间内，如果拿到了锁头，流程就走下来，如果时间到了没拿到锁，流程也可以走下来。*/


}