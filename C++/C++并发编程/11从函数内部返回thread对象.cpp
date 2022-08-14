#include<iostream>
#include<thread>

void some_function() { std::cout << "1\n"; }
void some_other_function(int i) { std::cout << i << '\n'; }
std::thread f() {
	return std::thread(some_function);
}
std::thread g() {
	std::thread t(some_other_function, 42);
	return t;
}
void test() {
	std::thread t1=f();
	t1.join();
	std::thread t2=g();
	t2.join();
}
int main() {
	test();
}