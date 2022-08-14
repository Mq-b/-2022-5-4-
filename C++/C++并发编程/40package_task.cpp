#include <thread>  
#include <future>   // std::packaged_task, std::future
#include <iostream>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::packaged_task<int(int, int)> task(std::move(sum));
    //只有当std::packaged_task设置了有效的函数或可调用对象，valid才返回true。
    std::cout << std::boolalpha << task.valid() << std::endl;
    std::future<int> future = task.get_future();
    // std::promise一样，std::packaged_task支持move，但不支持拷贝
    std::thread t(std::move(task), 1, 2);
    std::cout << std::boolalpha << task.valid() << std::endl;//线程已经开启，false
    // 等待异步计算结果
    std::cout << "1 + 2 => " << future.get() << std::endl;
    t.join();
    return 0;
}