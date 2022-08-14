#include<iostream>
#include<thread>
#include<mutex>

//1:unique_lock取代lock_guard
//unique_lock是个类模板，工作中，一般lock_guard（推荐使用）；lock_guard取代了mutex的lock和nulcok();
//unique_lock比lock_guard灵活很多；效率上差一点，内存多一点

int v = 1;

void critical_section(int change_v)noexcept {
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // 执行竞争操作
    v = change_v;
    std::cout << v << std::endl;
    // 将锁进行释放
    lock.unlock();

    // 在此期间，任何人都可以抢夺 v 的持有权

    // 开始另一组竞争操作，再次加锁
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int main() {
    std::jthread t1(critical_section, 2), t2(critical_section, 3);//只有两种可能2334或者3423，这主要看这两个线程谁先开启
    return 0;
}