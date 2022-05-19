#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<algorithm>
#include <chrono>
class auto_timer {
	std::chrono::system_clock::time_point start;

public:
	// start record when entering scope
	explicit auto_timer(const char* task_name = nullptr) {
		if (task_name) std::cout << task_name << " running , ";
		start = std::chrono::system_clock::now();
	}

	// end record when leaving scope
	~auto_timer() {
		auto cost = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start);
		std::cout << "cost: " << double(cost.count()) / 1000000.0 << " ms" << std::endl;
	}
};

template<typename Iterator>
void F(Iterator start, Iterator end) {
	std::sort(start, end);
}
template <typename Iterator>
void merge(Iterator start, int length, int size)
{
	for (int i = 1; i < size; i++)
		std::inplace_merge(start, start + length * i, start + length * (i + 1));
}
template<typename Iterator>
void Sort_(Iterator start, Iterator end) {
	const size_t length = std::distance(start, end);
	size_t max_thread = std::min(length / 100, std::thread::hardware_concurrency());
	if (!max_thread)
		max_thread = 1;
	const size_t size = length / max_thread;
	std::vector<std::thread>threads;
	Iterator block_start = start;

	for (size_t i = 0; i < (max_thread - 1); i++) {
		Iterator block_end = block_start;
		std::advance(block_end, size);
		threads.emplace_back(F<Iterator>, block_start, block_end);
		block_start = block_end;
	}
	F(block_start, end);
	for (auto& i : threads)
		i.join();
	merge(start, size, max_thread);
}
template<class T>
void Sort(std::vector<T>& data)
{
	const intptr_t size = data.size();
	intptr_t stride = 2048;

	//从stride = 1开始归并排序非常缓慢
	//因此这里对data进行初排序
	//从一个较大的stride开始归并排序
	if (stride != 1) {
#pragma omp parallel for schedule(dynamic, 2048 / stride + 1)
		for (intptr_t i = 0; i < size; i += stride) {
			auto left = data.begin() + i;
			auto right = i + stride < size ? data.begin() + i + stride : data.end();
			std::sort(left, right);
		}
	}

	//并行归并排序
#pragma omp parallel
	{
		intptr_t _stride = stride;
		do
		{
			_stride *= 2;

#pragma omp for schedule(dynamic, 2048 / _stride + 1)
			for (intptr_t i = 0; i < size; i += _stride) {
				//对[i, i+_stride/2)和[i+_stride/2, i+_stride)进行归并
				auto left = data.begin() + i;
				auto mid = (i + i + _stride) / 2 < size ? data.begin() + (i + i + _stride) / 2 : data.end();
				auto right = i + _stride < size ? data.begin() + i + _stride : data.end();
				inplace_merge(left, mid, right);
			}
		} while (_stride < size);
	}
}
int main() {
	srand(time(0));
	std::vector<int>V;
	for (int i = 10000000; i > 0; i--)
		V.push_back(rand());
	/*for (auto i : V)
		std::cout << i << ' ';*/
		//std::cout << std::endl;

	{
		auto_timer timer("并行排序");
		Sort_(V.begin(), V.end());
	}

	std::vector<int>V2;
	for (int i = 10000000; i > 0; i--)
		V2.push_back(rand());
	{
		auto_timer timer("库排序");
		std::sort(V2.begin(), V2.end());
	}
	std::vector<int>V3;
	for (int i = 10000000; i > 0; i--)
		V3.push_back(rand());
	{
		auto_timer timer("并行归并");
		Sort(V3);
	}
	std::vector<int>V4{ 10,9,8,7,6,5,4,3,2,1 };
	{
		{
			auto_timer timer("并行排序");
			Sort_(V4.begin(), V4.end());
			for (auto i : V4)
				std::cout << i << ' ';
		}
	}
	/*for (auto i : V)
		std::cout << i << ' ';*/
}