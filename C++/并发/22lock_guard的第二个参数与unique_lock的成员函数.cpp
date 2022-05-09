#include<iostream>
#include<thread>
#include<mutex>
std::mutex myMutex1;
void G(int&i) { std::cout << i++ << std::endl; }
//lock_guard可以带第二个参数：
/*.1 std::adopt_lock：

    表示这个互斥量已经被lock()，即不需要在构造函数中lock这个互斥量了。
    前提：必须提前lock,否则会报异常
    之前的lock_guard中也可以用这个参数*/
void test01() {
    int i = 0;          //如果把i写到全局那么就好会打印到19，主要是此函数在另一个线程运行的时候被上锁
    static std::mutex my_mutex;
    my_mutex.lock();    //要先lock()后序才能用std::adopt_lock参数
    std::unique_lock<std::mutex>A{ my_mutex,std::adopt_lock };
    for (int n = 0; n < 10; n++)G(i);
    std::chrono::milliseconds dura(100);//1秒=1000毫秒
    std::this_thread::sleep_for(dura);//休息一定的时长
    A.unlock(); //可写可不写，主要是表示可以这样
}

/*2.2 std::try_to_lock：

    尝试用mutex的lock()去锁定这个mutex，但如果没有锁定成功，会立即返回，不会阻塞在那里；
    使用try_to_lock的原因是防止其他的线程锁定mutex太长时间，导致本线程一直阻塞在lock这个地方
    前提：不能提前lock();  
    owns_locks()方法判断是否拿到锁，如拿到返回true
    我们考虑使用try_to_lock，线程尝试获取锁，如果没有锁定成功，它不会阻塞在那里，可以去执行其他代码。*/

void InMsg()noexcept
{
    auto id = std::this_thread::get_id();
    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> guard(myMutex1, std::try_to_lock);
        if (guard.owns_lock())  //判断是否拿到锁
        {
            //std::chrono::microseconds time(100);
            //std::this_thread::sleep_for(time);
            std::cout << id << "push\n";
        }
        else
        {
            
            std::cout << id << "wait\n";
        }
    }
}

/*2.3 std::defer_lock：
    如果没有第二个参数就对mutex进行加锁，加上defer_lock是始化了一个没有加锁的mutex
    不给它加锁的目的是以后可以调用unique_lock的一些方法
    前提：不能提前lock*/
void test03() {                     //成员函数lock()加锁，unlock()解锁
    std::unique_lock<std::mutex>sbguard1(myMutex1,std::defer_lock);//没有加锁的myMutex1
    sbguard1.lock();     
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
    sbguard1.unlock();//只是示范一下，没必要一定这样写
}
void test03_() {
    std::unique_lock<std::mutex>sbguard1(myMutex1);//去掉那些一样可以，只不过可以更加灵活
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
}

//try_lock()成员函数，和std::try_to_lock有点相似
void test04() {
    std::unique_lock<std::mutex>sbguard1(myMutex1,std::defer_lock);
    if (sbguard1.try_lock() == true)//返回true表示拿到锁了          try_lock()要和std::defer_lock配合使用
    {
        //其他代码
        printf("拿到锁\n");
    }
    else
    {
        printf("没拿到锁\n");
        //没拿到锁处理的代码
    }
}

//release()成员函数，返回它所管理的mutex对象指针，并释放所有权；也就是说，这个unique_lock和mutex不再有关系
void test05() {
    std::unique_lock<std::mutex>abguard1(myMutex1);
    std::mutex *ptx=abguard1.release();//现在你有责任自己解锁这个myMutex1
    //ptx->lock();
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
    ptx->unlock();
}


//四：unique_lock所有权的传递mutex，
//std::unique_lock<std::mutex>sbguard1(myMutex1):  所有权概念
//sbguard1拥有myMutex1的所有权
//subguard1可以把自己对mutex（myMutex1)的所有权转移给其他的unique_lock对象；
//所以，unique_lock对象这个mutex的所有权属于 可以转移，但是不能复制
void test06() {
    std::unique_lock<std::mutex>abguard1(myMutex1);
    //std::unique_lock<std::mutex>abguard2(abguard1); //复制所有权，报错
    std::unique_lock<std::mutex>sbguard3(std::move(abguard1));//移动语义，相当于sbguard3和myMutex绑定在一起
                                                              //现在sbguard1指向空,sbguard3指向myMutex1
}

std::unique_lock<std::mutex>rtn_unique_lock()
{
    std::unique_lock<std::mutex>tmpguard(myMutex1);
    return tmpguard; //从函数返回一个局部的unique_lock对象是可以的。
                     //返回这种局部对象tmpguard会导致系统生成临时unique_lock对象，并调用unique_lcok的移动构造函数
}

void test07() {
    std::unique_lock<std::mutex>sbguard = rtn_unique_lock();//第二种所有权转移的方式
}

int main() {
    //std::jthread a(test01), a2(test01);
    
    //std::jthread b(InMsg),b2(InMsg);
    
    //std::jthread c(test03), c2(test03),c3(test03);

    //std::jthread d(test04), d2(test04);

    //std::jthread e(test05), e2(test05);

	return 0;
}