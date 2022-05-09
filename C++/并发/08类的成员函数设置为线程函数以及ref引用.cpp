#include<iostream>
#include<thread>

void update_data_for_widget(int w, int& data) {}
void oops_again(int w) {
	int data;
	//std::thread t(update_data_for_widget, w, data);	//错误方式，是值传递
	std::thread t(update_data_for_widget, w, std::ref(data));
	//24页下半部分
	t.join();
}
class X {
public:
	inline void do_lengthy_work() { std::cout << "class\n"; };
};
void test() {
	X my_x;
	//类似于std::bind，参数传递语义:若要将某个类的成员函数设定为线程函数，我们则应该传入一个函数指针，指向该成员函数。此外，我们还要给出合适的对象指针，作为该函数的第一个参数；
	std::thread t(&X::do_lengthy_work, &my_x);
	//25页上半部分
	t.join();
}
int main() {
	oops_again(1);
	test();
}