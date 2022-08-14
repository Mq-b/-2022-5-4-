#include<thread>
#include<atomic>
#include<assert.h>
#include<iostream>
std::atomic<int>x(0),y(0),z(0);
std::atomic<bool>go(false);
unsigned const loop_count = 10;
struct read_values {
	int x, y, z;
};
read_values valuesl[loop_count];
read_values values2[loop_count];
read_values values3[loop_count];
read_values values4[loop_count];
read_values values5[loop_count];
void increment(std::atomic<int>* var_to_inc, read_values* values) {
	while (!go)
		std::this_thread::yield();//就是先让别的线程去执行，降低当前线程的优先级，如果没有别的线程，依旧会执行此线程
	for (unsigned i = 0; i < loop_count; ++i) {
		values[i].x = x.load(std::memory_order_relaxed);
	}
}
int main() {
	

}