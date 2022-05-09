#include <iostream>                
#include <thread>                
#include <mutex>                
#include <condition_variable>    // std::condition_variable

std::mutex mtx;              // 全局互斥锁.
std::condition_variable cv;  // 全局条件变量对象
bool ready = false;          // 全局标志位.

void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
   while (!ready) // 如果标志位不为 true, 则等待...
        cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后, 线程被唤醒, 继续往下执行打印线程编号id.
    std::cout << "thread " << id << '\n';
}
void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cv.notify_all(); // 唤醒所有线程.
}

int main()
{
    std::thread threads[10];    
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);
    std::cout << "10 threads ready to race...\n";
    go(); // go!
    for (auto& th : threads)
        th.join();
    return 0;
}                                   //lambda指的是可调用对象
//wait()用来等一个东西
//如果第二个参数，lambda返回值是true，那wait()直接返回；
//如果第二个参数lambda表达式返回值是false，那么wait()将解锁互斥量，并堵塞到本行
//那么堵塞到什么时候呢？堵塞到其他线程调用notify_one()成员函数为止
//如果wait()没有第二个参数：那么跟第二个参数lambda表达式返回值为false效果一样
//wait()将解锁互斥量，并堵塞到本行，堵塞到其他某个线程调用notify_one()成员函数为止

/*三、notify_all()

notify_one()：通知一个线程的wait()

notify_all()：通知所有线程的wait()*/