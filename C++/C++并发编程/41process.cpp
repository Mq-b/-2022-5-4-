#include <iostream> 
#include <thread>   
#include <string>   
#include <future>   
#include <chrono>   

void read(std::future<std::string>&& future) {
    // future会一直阻塞，直到有值到来
    std::cout << std::this_thread::get_id() << std::endl;
    std::cout << future.get() << std::endl;
}
std::string sum(std::string a,std::string b) {
    return a+b;
}
void working(std::promise<std::string>&& p,std::string a,std::string b) {
    std::cout << std::this_thread::get_id() << std::endl;
    auto num = sum(a,b);
    p.set_value(num);
}
int main() {
    // promise 相当于生产者
    std::promise<std::string> promise;
    // future 相当于消费者, 右值构造
    std::future<std::string> future = promise.get_future();
    // 另一线程中通过future来读取promise的值
    std::jthread thread(read, std::move(future));//此线程得到值
    std::jthread(working, std::move(promise), "192.168.139.127:", "你好");//此线程设置值
    return 0;
}
//std::promise相当于和future绑定了，我们在一个线程里面传入了future，试图get获取值，然鹅在另一个线程中传入了promise，用来设置future的值。
//比如我们可以用promise所在线程进行读取文件的任务，再使用set_value设置future，让future所在线程对获取到的数据进行别的操作