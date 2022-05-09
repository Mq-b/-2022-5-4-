#include<iostream>
#include<thread>
#include<future>
#include<atomic>
using namespace std::literals;

int mythread()
{
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 1;
}

int main() {
	////std::async参数详述，async用来创建一个异步任务；
	//std::cout << "main start" << "threadid = " << std::this_thread::get_id() << std::endl;
	//std::future<int>result = std::async(std::launch::deferred,mythread);//延迟调用，并且不会创建新线程，延迟到get()或者wait()才执行，反之不执行
	////std::future<int>result = std::async(mythread);
	//std::cout << result.get() << std::endl;

	//std::launch::deferred【延迟调用】,以及std::launch::async【强制创建一个线程】
	//std::thread()如果系统资源紧张，那么可能创建线程就会失败，那么执行std::thread()时整个程序可能奔溃
	//std::async()我们一般不叫创建线程（解释async能够创建线程），我们一般叫它创建一个异步任务
	//std::async和std::thread最明显的不同，就是async有时候并不创建新线程
	//std::launch::deferred【延迟调用】并且不会创建新线程，延迟到get()或者wait()才执行，反之不执行
	//std::launch::async：强制这个任务在新线程上执行，意味着，系统必须创建新线程
	//std::launch::async | std::launch::deferred
	//这里这个 | 意味着调用async的行为可能是 创建新线程并立即执行 或者 是没有创建新线程并延迟调用
			//两者居其一，系统按照一些规则决定

	//第九节课讲错了，其实默认值应该是std::launch::async | std::launch::deferred，和上面效果完全一致
	//换句话说系统会自动决定是异步（创建新线程）还是同步（不创建新线程）运行

	///自行决定的意思？系统如何决定异步（创建新线程）还是同步（不创建新线程）
	//std::async和std::thread的区别
	//std::thread创建线程，如果系统资源紧张，创建线程失败，那么整个程序就会报异常奔溃
	//int mythread(){return 1;}
	//std::thread mytobj(mythread);
	//mytobj.join
	//std::thread创建线程的方式，如果线程返回值，你想拿到这个值也不容易；
	//std::async创建异步任务。可能创建也可能不创建线程。并且async调用方法很容易拿到线程的返回值
	//由于系统资源限制：
	//（1）如果用std::thread创建的线程太多，则可能创建失败，系统报告异常，奔溃
	//（2）如果用std::async，一般就不会报异常，因为，如果系统资源紧张导致无法创建新线程的时候，这种不加额外参数的调用 就不会创建新线程。而是后序谁调用了result.get()。
				//那么这个异步任务就运行在主线程上
	//如果你强制std::async一定要创建新线程，那么就必须使用，std::launch::async。承受的代价就是系统资源紧张时，程序奔溃
	//（3）经验：一个程序里，线程数量不宜超过100-200，时间片。

	//不加额外参数的std::async调用，让系统决定是否创建新线程
	/*std::future<int> result = std::async(mythread);
	问题焦点在于这个写法，任务到底有没有被推迟执行。

	通过wait_for返回状态来判断：*/
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::future<int>result = std::async(mythread);
	std::cout << "continue......!" << std::endl;
	//枚举类型
	std::future_status status = result.wait_for(0s);	
	if (status == std::future_status::timeout)
	{
		//线程还没执行完
		std::cout << "超时，线程还没有执行完毕" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		//表示线程成功返回
		std::cout << "线程成功执行完毕，返回" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::deferred)//延迟
	{
		//线程被延迟执行，它采用了std::launch::deferred
		std::cout << "线程被延迟执行" << std::endl;
		std::cout << result.get() << std::endl;
	}

}