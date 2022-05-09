#include<iostream>
#include<thread>

void some_function(){}
void some_other_function(){}

void test1() {
	std::thread t1(some_function);

	std::thread t2 = std::move(t1);
	t1 = std::thread(some_other_function);


	std::thread t3;
	t3 = std::move(t2);
	//t1崩了,因为t1已经关联了起始线程
	t1 = std::move(t3);
	
	/*没被join或者detach的std::thread对象就是joinable的
	joinable的对象在赋值的时候就会terminate
	不是std::move的时候挂掉的，是赋值的时候挂掉的，也就是最后一句*/

	//如果std::thread::operator=仍有关联的运行中进程，即joinable==true，则调用析构std::terminate()
	//否则赋值other的状态，给*this并设置other为默认构造的状态
}
int main() {
	test1();
}
//27面上半部分介绍了，同时查看参考文档