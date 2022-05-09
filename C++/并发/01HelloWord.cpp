#include<iostream>
#include<thread>
void hello() {
	std::cout << "Hello Word\n";
}
int main() {
	std::thread t(hello);
	t.join();
}