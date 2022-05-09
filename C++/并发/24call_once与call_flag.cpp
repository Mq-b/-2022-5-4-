#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
/*功能
    保证某个函数对象只执行一次
    传入一个flag，内部通过该flag的改变来控制代码只调用一次

注意
    控制只调用一次的前提是同一个flag， 不同flag没办法达到控制的目的
    如果已经有线程执行过了，则新来的线程不会再执行
    如果有线程正在执行，则新来的线程会阻塞等待   
    如果正在执行的线程抛出异常，则不算执行完成，其他线程会重新执行
*/

std::once_flag flag;

void Test(int &i) {
    std::call_once(flag, [&]()mutable {
        cout << i << endl;
        ++i;
        this_thread::sleep_for(chrono::milliseconds(100));//匿名对象
        });
    cout << "exec end!!!" << endl; //每个线程都会阻塞等待call_once的函数执行完成
}

int main()
{
    int n = 1;
    vector<jthread> v(100);
    for (uint32_t i = 0; i < 10; i++) {
        v[i] = jthread(Test, std::ref(n));
    }
}