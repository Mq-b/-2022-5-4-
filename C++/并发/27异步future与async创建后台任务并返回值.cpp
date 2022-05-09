#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<map>
#include<future>

int mythread() {	//线程入口函数
	std::cout << "mythread() start" << "threadid=" << std::this_thread::get_id() << std::endl;//打印新线程id
	std::chrono::milliseconds dura(1000);//顶一份一秒的时长
	std::this_thread::sleep_for(dura);
	std::cout << "mythread()end" << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}

class A {
public:
	int mythread(int a) {	
		std::cout << a << std::endl;
		std::cout << "mythread() start" << "threadid=" << std::this_thread::get_id() << std::endl;//打印新线程id
		std::chrono::milliseconds dura(1000);//顶一份五秒的时长
		std::this_thread::sleep_for(dura);
		std::cout << "mythread()end" << "threadid=" << std::this_thread::get_id() << std::endl;
		return 5;
	}
};
void test() {		//类成员函数传参版本
	A a;
	int i = 10;
	//我们通过向std::async()传递一个参数，该参数类型是std::lunnch类型(枚举类型),来达到一些特殊的目的
	//std::lanuch::deferred:表示线程入口函数被延迟到std::future的wait()或者get()函数调用时才执行
	//那如果wait()或者get()没有被调用，那么这个线程根本不会创建
	//std::lauch:延迟调用，并且没有创建新的线程，是在主线程中调用的线程入口函数：
	//std::lauch::async，在调用async函数的时候开始创建线程；
	//async()函数默认用std::lauch::async，所以只需要注意：std::lanuch::deferred

	//std::future<int>result = std::async(std::launch::deferred, &A::mythread, &a, i);
	std::future<int>result = std::async(std::launch::async, &A::mythread, &a, i);
	//std::future<int>result = std::async(&A::mythread, &a, i);		//默认方式，和上面的没区别

	std::cout << result.get() << std::endl;	//卡在这里等待mythread执行完毕，拿到结果
}
int main() {
//一：std::async,future创建后台任务并返回值
//希望线程返回一个结果：
//std::async是个函数模板，用来启动一个异步任务，启动起来一个异步任务之后，他返回一个std::future对象，std::future是个类模板

/*什么叫“启动一个异步任务”？就是自动创建一个线程，并开始 执行对应的线程入口函数，它返回一个std::future对象，这个std::future对象中
就含有线程入口函数所返回的结果，我们可以通过调用future对象的成员函数get()来获取结果。

“future”将来的意思，也有人称呼std::future提供了一种访问异步操作结果的机制，就是说这个结果你可能没办法马上拿到，但是在不久的将来，
这个线程执行完毕的时候，你就能够拿到结果了，所以，大家这么理解：future中保存着一个值，这个值是在将来的某个时刻能够拿到。

std::future对象的get()成员函数会等待线程执行结束并返回结果，拿不到结果它就会一直等待，感觉有点像join()。但是，它是可以获取结果的。

std::future对象的wait()成员函数，用于等待线程返回，本身并不返回结果，这个效果和 std::thread 的join()更像。*/

	//下列程序通过std::future对象的get()成员函数等待线程执行结束并返回结果
	//这个get()函数很牛，不拿到将来的返回值 誓不罢休，不拿到值就在这里等待拿值
	
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::future<int>result = std::async(mythread);		//创建一个线程并开始执行,绑定关系，流程并不卡到这里
	std::cout << "continue......!" << std::endl;
	int def;
	def = 0;
	std::cout << result.get() << std::endl;	//卡在这里等待mythread执行完毕，拿到结果
	//std::cout << result.get() << std::endl;	//get()只能调用一次，不能调用多次
	//result.wait();	//等待线程返回，本身不返回结果
	std::cout << "I Love China!" << std::endl;
	test();
	return 0;
}