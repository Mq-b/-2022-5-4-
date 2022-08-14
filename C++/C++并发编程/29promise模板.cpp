#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<vector>
#include<algorithm>
/*std::promise，类模板
我们能够在某个线程中给它赋值，然后我们可以在其他线程中，把这个值取出来*/
void mythread(std::promise<int>& tmp, int clac) {
	std::cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << std::endl;
	int result = clac;
	tmp.set_value(result); //结果保存到了tmp这个对象中
}

std::vector<std::packaged_task<int(int)>> task_vec;

int main() {
	std::promise<int> myprom;					//声明一个promise对象，保存的值的类型为int
	std::thread t1(mythread, std::ref(myprom), 180);
	t1.join(); //在这里线程已经执行完了
	std::future<int> fu1 = myprom.get_future(); //promise和future绑定，用于获取线程返回值
	auto result = fu1.get();
	std::cout << "result = " << result << std::endl;
}