#ifndef FUNC_HPP
#define FUNC_HPP
#pragma once
#pragma warning(disable:4996)
#include<vector>
#include<algorithm>
#include <iostream>
#include<string>
#include<iterator>
#include<list>
#include<array>
#include<fstream>
#include<cstdio>
#include<ranges>
#include<numeric>
#include<cctype>
#include<thread>
#include<numeric>//提供std::accumulate
#include<iterator>

namespace sort_ {
	template <typename Iterator>		//多个有序的序列合并到一起排序
	void merge(Iterator start, int length, int size)
	{
		for (int i = 1; i < size; i++)
			std::inplace_merge(start, start + length * i, start + length * (i + 1));
	}

	template<class T>			//并行归并
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
	class auto_timer {				//计时器
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
/*
	{
     auto_timer timer("任务名");
    // 耗时代码
	}
*/
	//变参变量模板
	template<auto... args>
	constexpr auto Mul_ = (...*args);
	//位运算交换，像傻子一样
	void swap(auto& a, auto& b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}
	//并行版accumulate
	template<typename Iterator, typename T>
	struct accumulate_block
	{
		void operator()(Iterator first, Iterator last, T& result)
		{
			result = std::accumulate(first, last, result);
		}
	};
	template<typename Iterator, typename T>
	T parallel_accumulate(Iterator first, Iterator last, T init)
	{
		unsigned long const length = std::distance(first, last);//返回从 first 到 last 的路程。
		if (!length)
			return init;
		unsigned long const min_per_thread = 25;
		unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;//如果是十个元素，那么结果为1
		unsigned long const hardware_threads = std::thread::hardware_concurrency();//返回值支持的并发线程数。若该值非良定义或不可计算，则返回 ​0，我电脑为16
		unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);//16返回16,min(16,1)，返回1，num_threads为1
		unsigned long const block_size = length / num_threads;//10/1，那么size为10
		std::vector<T> results(num_threads);//1
		std::vector<std::thread>threads(num_threads - 1);//以thread对象为元素，初始化为1-1,0
		Iterator block_start = first;//一开始，开始迭代器位置为开始first
		for (unsigned long i = 0; i < (num_threads - 1); ++i)//1-1,0，10个元素会直接跳过
		{
			Iterator block_end = block_start;//结束迭代器
			std::advance(block_end, block_size);//advance第一个参数迭代器，第二个参数移动的元素个数，在这里的作用是划分，让结束迭代器移动，这样开始和结束中间的元素就是线程处理的元素
			threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));//一个函数对象，两个参数，构造了匿名thread对象开启线程
			block_start = block_end;//增加，当上一个线程开启完毕后让开始迭代器赋值为上一个的末尾迭代器
		}
		accumulate_block<Iterator, T>() (block_start, last, results[num_threads - 1]);//10个元素则在这里就计算完，55
		for (auto& entry : threads)
			entry.join();

		return std::accumulate(results.begin(), results.end(), init);//accumulate求和算法，init为起始值，在多线程求出每一堆元素的和后放入result，这一步操作是让他们的值加起来
	}
	//归并
	void merge(int arr[], int start, int end, int mid, int* temp) {
		int i_start = start;
		int i_end = mid;
		int j_start = mid + 1;
		int j_end = end;

		int Length = 0;
		while (i_start <= i_end && j_start <= j_end) {
			if (arr[i_start] < arr[j_start])
				temp[Length++] = arr[i_start++];
			else
				temp[Length++] = arr[j_start++];
		}
		while (i_start <= i_end) {
			temp[Length++] = arr[i_start++];
		}
		while (j_start <= j_end) {
			temp[Length++] = arr[j_start++];
		}
		for (int i = 0; i < Length; i++) {
			arr[start + i] = temp[i];
		}
	}
	void mergeSort(int arr[], int start, int end, int* temp) {
		if (start >= end) {
			return;
		}
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid, temp);
		mergeSort(arr, mid + 1, end, temp);
		merge(arr, start, end, mid, temp);
	}

	//快排
	template<typename T>
	void quickSort(int left, int right, std::vector<T>& arr) {
		if (left >= right)
			return;
		int i = left, j = right, base = arr[left];//取最左边的数为基准数
		while (i < j) {
			while (arr[j] >= base && i < j)
				j--;
			while (arr[i] <= base && i < j)
				i++;
			if (i < j) {
				std::swap(arr[i], arr[j]);
			}
		}
		arr[left] = arr[i];
		arr[i] = base;
		quickSort(left, i - 1, arr);
		quickSort(i + 1, right, arr);
	}
	template<typename T>
	void quickSort(int left, int right, T arr[]) {
		if (left >= right)
			return;
		int i = left, j = right, base = arr[left];//取最左边的数为基准数
		while (i < j) {
			while (arr[j] >= base && i < j)
				j--;
			while (arr[i] <= base && i < j)
				i++;
			if (i < j) {
				std::swap(arr[i], arr[j]);
			}
		}
		arr[left] = arr[i];
		arr[i] = base;
		quickSort(left, i - 1, arr);
		quickSort(i + 1, right, arr);
	}

	//选择
	template<typename T>//从小到大升序
	void selectSort(T arr[], int len) {
		for (int i = 0; i < len; i++) {
			int min = i;
			for (int j = i + 1; j < len; j++) {
				if (arr[j] < arr[min]) {
					min = j;
				}
			}
			if (min != i) {
				std::swap(arr[min], arr[i]);
			}
		}
	}
	//插入
	void insertion_sort(int arr[], int len) {
		int i, j, key;
		for (i = 1; i < len; i++) {
			key = arr[i];
			j = i - 1;
			while ((j >= 0) && (arr[j] > key)) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}
	//冒泡
	void bubbleSort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] < arr[j + 1])std::swap(arr[j], arr[j + 1]);
			}
		}
	}
	//手动实现Stack
	template<typename T>
	class Stack
	{
	public:
		void push(T elem) {
			v.push_back(elem);
		}
		T pop() {
			T temp = v[v.size() - 1];
			v.pop_back();
			return temp;
		}
		T& top() {
			return v[v.size() - 1];
		}
		int size() {
			return v.size();
		}
		bool empty() {
			return v.empty();
		}
	private:
		std::vector<T>v;
	};
	//Stack计算10进制转任何进制
	void convert(Stack<char>& S, _int64 n, int base) {
		static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		while (n > 0) {
			S.push(digit[n % base]);
			n /= base;
		}
	}
	template<typename T>
	void Inverted(T n[], int str, int end) {	//数组逆置
		if (str < end) {
			std::swap(n[str], n[end]);
			Inverted(n, str + 1, end - 1);
		}
		return;
	}
	template<typename T>
	int sum(T n[], int start, int end) {//也可以使用accumulate算法
		if (start == end)return n[start];
		int mid = (start + end) >> 1;
		return sum(n, start, mid) + sum(n, mid + 1, end);
	}//二分递归，数组求和
	double average(int n[], int start, int end) {
		return sum(n, start, end) / static_cast<double>(end + 1);
	}//二分递归，数组求平均
	int fib(int n) {
		return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
	}//时间复杂度O(2^n)，空间消耗很高
	int fib2(int n) {
		int f = 0, g = 1;
		while (0 < n--) {
			g = g + f;
			f = g - f;
		}
		return g;
	}//时间复杂度O(n),空间复杂度只需要O(1)
	//给数组移位，默认左移，时间复杂度O(n^2)，很垃圾的遍历
	template<typename T, size_t size>
	void arrayShift(T(&v)[size], int n, bool k = true) {
		T temp;
		if (k) {
			for (int i = 0; i < n; i++) {
				temp = v[0];
				for (int j = 0; j < size - 1; j++) {
					v[j] = v[j + 1];
				}
				v[size - 1] = temp;
				temp = 0;
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				temp = v[size - 1];
				for (int j = size - 1; j > 0; j--) {
					v[j] = v[j - 1];
				}
				v[0] = temp;
				temp = 0;
			}
		}
	}
	//重载版本array
	template<typename T, size_t size>
	void arrayShift(std::array<T,size>&v, int n, bool k = true) {
		T temp;
		if (k) {
			for (int i = 0; i < n; i++) {
				temp = v[0];
				for (int j = 0; j < size - 1; j++) {
					v[j] = v[j + 1];
				}
				v[size - 1] = temp;
				temp = 0;
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				temp = v[size - 1];
				for (int j = size - 1; j > 0; j--) {
					v[j] = v[j - 1];
				}
				v[0] = temp;
				temp = 0;
			}
		}
	}
	//其实,algorithm提供了rotate算法，很优质，我刚看见，那么这个重载用它吧,使用方式很简单，可以看253
	template<typename T>
	void arrayShift(T&&begin,T&&mid,T&&end) {				//我们使用和库函数一样的调用方式，反正就是个套娃。
		std::rotate(begin,mid,end);
	}
	template<typename T, size_t size>	//普通数组版本删除元素,效率很低的方式，按照下标删除
	void erase(T(&v)[size], int lo)
	{
		for (int i = lo; i < size - 1; i++)
		{
			v[i] = v[i + 1];
			v[i + 1] = 0;
		}
	}
	template<typename T>		//提供一个动态数组版本
	void earse(T*& p, int size, int lo)
	{
		T* temp = new T[size - 1];
		for (int i = lo; i < size - 1; i++)
		{
			p[i] = p[i + 1];
			p[i + 1] = 0;
		}
		std::copy_if(p, p + size, temp, [](T a) {return a != 0; });
		delete[]p;
		p = temp;
	}
	//去除有序序列重复项vector版本，低效方式，时间复杂度O(n^2)
	template<typename T>
	int uniquify(std::vector<T>& v) {
		int oldSize = v.size(); int i = 0;
		while (i < v.size() - 1) {
			if (v[i] == v[i + 1]) {
				v.erase(v.begin() + i);
			}
			else {
				i++;
			}
		}
		return oldSize - v.size();
	}
	//我们提供一个高明的O(n)的方式
	template<typename T>
	int uniquify2(std::vector<T>& v) {
		int i = 0, j = 0;
		while (++j < v.size())
			if (v[i] != v[j])v[++i] = v[j];
		v.resize(++i);
		return j - i;
	}
	//裸数组版本,把重复的替换为0放到后面，动态数组另说
	template<typename T, size_t size>
	int uniquify2(T(&v)[size]) {
		int i = 0, j = 0;
		while (++j < size)
			if (v[i] != v[j])v[++i] = v[j];
		std::fill(std::begin(v) + i, std::end(v), 0);
		return j - i - 1;
	}
}
namespace find_ {
	template<typename Comparable>
	int binarySearch(const std::vector<Comparable>& a, const Comparable& x)
	{
		int low = 0, hight = a.size()-1;
		while (low <= hight)
		{
			int mid = (low + hight) / 2;

			if (a[mid] < x) {
				low = mid + 1;
			}
			else if (a[mid] > x) {
				hight = mid - 1;
			}
			else
				return mid;		//找到的情况
		}
		return -1;
	}
	template<typename Comparable>
	int binarySearch(const Comparable *a, const Comparable x,Comparable len)
	{
		int low = 0, hight =len-1 ;
		while (low <= hight)
		{
			int mid = (low + hight) / 2;

			if (a[mid] < x) {
				low = mid + 1;
			}
			else if (a[mid] > x) {
				hight = mid - 1;
			}
			else
				return mid;		//找到的情况
		}
		return -1;
	}
	template<class T>	//另一种方式，更加平均的二分查找
	auto binSearch(T* A, T const& e, T lo, T hi) {
		while (1 < (hi - lo)) {
			T mi = (lo + hi) >> 1;
			e < A[mi] ? hi = mi : lo = mi;
		}
		return e == A[lo] ? lo : -1;
	}

}
namespace pow_ {
	double pow_(int x, size_t n)
	{
		if (n == 0)
			return 1;

		if (n == 1)
			return x;

		if (n % 2 == 0)
			return pow_(x * x, n / 2);
		else
			return pow_(x * x, n / 2) * x;
	}
	double pow_(int x, int n)
	{
		n = -n;
		return 1 / pow_(x, static_cast<size_t>(n));
	}
}
namespace maxAmin {	//主要是之前没有注意algorithm提供了这个算法std::cout<<*std::max_element(std::begin(num), std::end(num));，min也是同理，注意这个函数的返回值是地址，需要*取地址即可
	template<typename T,size_t size>
	auto max(T(&n)[size]) {
		T Max{};
		for (size_t i = 0; i < size; i++) {
			if (n[i] > Max)Max = n[i];
		}
		return Max;
	}
	template<typename T>
	auto max(std::vector<T>n) {
		T Max{};
		for (size_t i = 0; i < n.size(); i++) {
			if (n[i] > Max)Max = n[i];
		}
		return Max;
	}
	template<typename T, size_t size>
	auto min(T(&n)[size]) {
		T Min = n[0];
		for (size_t i = 1; i < size; i++) {
			if (n[i] < Min)Min = n[i];
		}
		return Min;
	}
	template<typename T>
	auto min(std::vector<T>n) {
		T Min = n[0];
		for (size_t i = 1; i < n.size(); i++) {
			if (n[i] < Min)Min = n[i];
		}
		return Min;
	}
}
namespace show_ {
	template<typename T,size_t i>
	void print(const T(&n)[i], const std::string s=" ") {
		std::copy(std::begin(n),std::end(n), std::ostream_iterator<T, char>(std::cout, s.data()));
		std::cout << std::endl;
	}
	template<typename T,size_t size>
	void print(const std::array<T,size> v, const std::string s = " ") {
		std::copy(std::begin(v), std::end(v), std::ostream_iterator<T, char>(std::cout, s.data()));
		std::cout << std::endl;
	}
	void print(const char* s) {
		std::cout << s << std::endl;											//重载特殊情况，字符串常量输出
	}
	void print(char* s) {
		std::cout << s << std::endl;											//重载特殊情况，字符串常量输出
	}
	template<typename T>
	void print(const std::vector<T>n,const std::string s=" ") {
		std::copy(std::begin(n), std::end(n), std::ostream_iterator<T, char>(std::cout, s.data()));
		std::endl(std::cout);
	}
	template<typename T>
	void print(T v) {
		std::cout << v << std::endl;
	}
	template<typename T>
	void print(const std::list<T>& L,std::string s=" ") {
		for (auto it = L.begin(); it != L.end(); it++) {										//list容器版本
			std::cout << *it << s;
		}
		std::cout << std::endl;
	}
	template<typename _Type1, typename _Type2, typename... _Types>
	void print(_Type1 _Value1, _Type2 _Value2, _Types... _Values)//c++17折叠表达式
		requires (sizeof...(_Types) > 0 || (!std::is_same_v<char*, _Type2> && !std::is_same_v<const char*, _Type2>))//requires是c++20的
	{
		std::cout << _Value1 << " " << _Value2 << " ";
		((std::cout << _Values <<" "), ...);
	}
	namespace object {			//这真是无奈之举，这个匹配，object命名空间内的除了遍历vector和array的数组外，标准数据类型直接打印也可行
		template<typename T>
		std::ostream& operator<<(std::ostream& os, const std::vector<T>& data)
		{
			for (auto& str : data)
			{
				os << str<<" ";
			}
			return os;
		}
		template<typename T, size_t size>
		std::ostream& operator<<(std::ostream& os, const std::array<T, size>& data)
		{
			for (auto& str : data)
			{
				os << str<<" ";
			}
			return os;
		}
		void print() {}
		template<typename T, typename...Types>
		void print(T first, Types...args) {
			std::cout << first << '\n';
			print(args...);
			return;
		}
	}
	namespace range {	//没办法重载多了就是匹配问题，我能这里使用c++20的range
		void print_impl(std::ostream& out, std::ranges::range auto&& r)
		{
			for (auto&& elem : r)
			{
				out << elem << " ";
			}
			std::cout << std::endl;
		}
		void print_impl(std::ostream& out, auto&& elem)
		{
			out << elem << " ";
			std::cout << std::endl;
		}
		void print(auto&&...args)
		{
			(print_impl(std::cout, args), ...);
		}
	}
	namespace rangeClass {		//也可以写成一个类，主要是为了防止让print_impl暴露在外部接口，因为print同名的缘故所以我们无法写在一起
		class print {
		public:
			void operator()(auto&&...args)
			{
				(print_impl(std::cout, args), ...);
			}
		private:
			void print_impl(std::ostream& out, std::ranges::range auto&& r)
			{
				for (auto&& elem : r)
				{
					out << elem << " ";
				}
				std::cout << std::endl;
			}
			void print_impl(std::ostream& out, auto&& elem)
			{
				out << elem << " ";
				std::cout << std::endl;
			}
		};
	}
}
namespace input_ {
	template<typename T, size_t size>
	void input(T(&v)[size],std::string str="")//裸数组版本重载
	{
		if (str[0])std::cout << str;
		for (auto& i : v)std::cin >> i;
	}
	template<size_t size>
	void input(char(&v)[size], std::string str = "")//是上一个模板的偏特化，这倒是比之前的print高明
	{
		if (str[0])std::cout << str;
		std::cin.getline(v, size);
	}
	template<typename T>				//string对象的输入
	void input(T &v, std::string str = "")
	{
		if (str[0])std::cout << str;
		std::cin >> v;
	}
	template<typename T>					//vector版本
	void input(std::vector<T>&v, size_t size,std::string str="")
	{
		if (str[0])std::cout << str;
		v.resize(size);
		for (int i = 0; i < size; i++)std::cin >> v[i];
	}
	template<typename T,size_t size>
	void input(std::array<T, size>& v, std::string str = "")
	{
		if (str[0])std::cout << str;
		for (int i = 0; i < size; i++)std::cin >> v[i];
	}
	/*-----------------------------------------------------------------*/
	void print_impl(std::istream& out, std::ranges::range auto&& r)		//不得不承认，得益于C++20，一切皆可
	{
		for (auto&& elem : r)
		{
			out >> elem;
		}
	}
	void print_impl(std::istream& out, auto&& elem)
	{
		out >> elem;
	}
	void input(auto&&...args)
	{
		(print_impl(std::cin, args), ...);
	}
}
namespace file_ {			//写入数据做第一个参数表示此为template
	//获取当前时间的字符串
	std::string time_() {
		time_t timep;
		time(&timep);
		char tmp[256];
		strftime(tmp, sizeof(tmp), "%Y年%m月%d日_%H点%M分%S秒", localtime(&timep));
		std::string s{ tmp };
		return s;
	}
	//创建文件夹，默认在同级目录
	std::string newFolder(std::string name = time_(), std::string path = "") {
		std::string temp = "md ";
		temp += path;
		temp += name;
		//std::cout << "创建文件夹 " << temp << std::endl;
		system(temp.data());
		return temp.substr(3);
	}
	//删除文件夹
	std::string deleteFolber(std::string path) {
		std::string s = "rd ";
		system((s += path).data());
		return s.substr(3);
	}
	//以追加模式打开写文件
	std::string newWriteFile(std::string name = time_()+=".txt", std::string data = time_(), std::string path = "") {
		path += name;
		std::ofstream ofs;
		ofs.open(path, std::ios::app);
		ofs << data;
		ofs.close();
		return path;
	}
	//创建新的文件写入，一开始有就删除再创建
	void newlyFile(std::string name = time_()+=".txt", std::string data = time_(), std::string path = "") {
		path += name;
		std::ofstream ofs;
		ofs.open(path, std::ios::trunc);
		ofs << data;
		ofs.close();
	}
	
	//以追加模式打开写文件(template，重载)
	template<typename T>
	std::string newWriteFile(T data, std::string name = time_() += ".txt", std::string path = "") {
		path += name;
		std::ofstream ofs;
		ofs.open(path, std::ios::app);
		ofs << data;
		ofs.close();
		return path;
	}
	//创建新的文件写入，一开始有就删除再创建(templat,重载)
	template<typename T>
	void newlyFile(T data, std::string name = time_() += ".txt", std::string path = "") {
		path += name;
		std::ofstream ofs;
		ofs.open(path, std::ios::trunc);
		ofs << data;
		ofs.close();
	}
	//A开头表示数组，比如vector裸数组，array	其实按道理来说是可以和上面重载的，但是，之前想string对象版本会有问题，字符串优先匹配数组模板的重载，不想处理，懂吧
	// 以追加模式打开写文件(template,array)
	template<typename T, size_t size>
	void A_newWriteFile(T(&data)[size], std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::app);
		for (int i = 0; i < size; i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}
	//创建新的文件写入，一开始有就删除再创建(templat,array)
	template<typename T, size_t size>
	void A_newlyFile(T(&data)[size], std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::trunc);
		for (int i = 0; i < size; i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}

	// app写file(template,vector)
	template<typename T>
	void A_newWriteFile(std::vector<T> data, std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::app);
		for (int i = 0; i < data.size(); i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}
	//trunc写file(template,vector)
	template<typename T>
	void A_newlyFile(std::vector<T> data, std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::trunc);
		for (int i = 0; i < data.size(); i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}

	// app写file(template,array<>)
	template<typename T, size_t size>
	void A_newWriteFile(std::array<T, size> data, std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::app);
		for (int i = 0; i < size; i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}
	//trunc写file(template,array<>)
	template<typename T, size_t size>
	void A_newlyFile(std::array<T, size> data, std::string path = time_() += ".txt") {
		std::ofstream ofs;
		ofs.open(path, std::ios::trunc);
		for (int i = 0; i < size; i++)ofs << data[i] << " ";
		ofs << std::endl;
		ofs.close();
	}
	//删除文件的数据
	void deleteData(std::string name ,std::string path = "") {
		path += name;
		std::ofstream ofs(path, std::ios::trunc);
		ofs.close();
	}
	//删除文件
	bool deleteFile(std::string path) {
		if (remove(path.data()) == 0) {
			//std::cout << "删除成功" << std::endl;
			return true;
		}
		else {
			std::cout << "删除失败" << std::endl;
			return false;
		}
	}
	//读取文件
	std::string readFile(std::string path) {
		std::ifstream ifs;
		ifs.open(path, std::ios::in);
		if (!ifs.is_open())
		{
			std::cout << "文件打开失败" << std::endl;
			return "";
		}
		std::string data{};
		while (ifs >> data);
		ifs.close();
		return data;
	}
	//打印输出文件内容
	void print(std::string path) {
		show_::print(readFile(path));
	}
	/*为什么读取的模板函数这么少？因为我发现貌似使用字符串是最方便的了，需要的话调用库函数进行转换即可，有一说一因为我加了空格这比较麻烦*/
}
//继承vector容器，让Vector保留了初始化列表同时增加了处理负数下标的功能，下面两个没有放入命名空间，而且有些bug
template<typename T>
class Vector :public std::vector<T> {
public:
	using std::vector<T>::vector;	//继承基类的构造函数
	Vector() : std::vector<T>() {}
	T operator[](int n) {
		return n >= 0 ? this->std::vector<T>::operator[](n) : this->std::vector<T>::operator[](this->size() + n);
	}
};
template<typename T, size_t size_>
class Array {
public:
	Array() = default;
	Array(std::initializer_list<T> init)
	{
		std::copy(init.begin(), init.end(), arr);
	}
	decltype(auto) operator[](int n) {
		return n >= 0 ? arr[n] : arr[size_ + n];
	}
	size_t size() {
		return size_;
	}
	T* begin() {
		return arr;
	}
	T* end() {
		return arr + size_;
	}
	decltype(auto) sum() {
		return std::accumulate(arr, arr + size_, 0);
	}
	T averager() {
		return sum() / size_;
	}
	void Inverted() {
		std::reverse(std::begin(arr), std::end(arr));
	}
	size_t uniquify() {	//去重
		int i = 0, j = 0;
		while (++j < size_)
			if (arr[i] != arr[j])arr[++i] = arr[j];
		std::fill(std::begin(arr) + i, std::end(arr), 0);
		return j - i - 1;
	}
	decltype(auto) find(T a) {
		return std::find(std::begin(arr), std::end(arr), a);
	}
private:
	T arr[size_];
};

namespace stdl = std::ranges;//命名空间别名
class Test {
public:
	 auto number()->std::initializer_list<int> const {
		return { 1,2,3,4,5,6,7,8,9,10 };
	}
};

template<typename T,typename A>//模板推导绑定成员函数
void test(T f,A func) {
	stdl::copy((f->*func)(), std::ostream_iterator<int>{std::cout, " "});
}

//线程安全的栈容器类
struct empty_stack :std::exception
{
	const char* what()noexcept { return ""; }
};
template<typename T>
class threadsfe_stack {
private:
	std::stack<T>data;
	mutable std::mutex m;
public:
	threadsfe_stack(){}
	threadsfe_stack(const threadsfe_stack& other)
	{
		std::lock_guard<std::mutex>lock(other.m);
		data = other.data;
	}
	threadsfe_stack& operator=(const threadsfe_stack&) = delete;
	void push(T new_value)
	{
		std::lock_guard<std::mutex>lock(m);
		data.push(std::move(new_value));
	}
	std::shared_ptr<T>pop()
	{
		std::lock_guard<std::mutex>lock(m);
		if (data.empty())throw empty_stack();
		std::shared_ptr<T>const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex>lock(m);
		if (data.empty())throw empty_stack();
		value = data.top();
		data.pop();
	}
	bool empty()const
	{
		std::lock_guard<std::mutex>lock(m);
		return data.empty();
	}
};
//包装thread
class joining_thread {
	std::thread t;
public:
	joining_thread()noexcept = default;
	template<typename Callable,typename ...Args>
	explicit joining_thread(Callable&& func,Args&&...args):t{std::forward<Callable>(func),std::forward<Args>(args)...}
	{}
	joining_thread(joining_thread&& other)noexcept :t{ std::move(other.t) }
	{}
	joining_thread& operator=(joining_thread&& other)noexcept {
		if (t.joinable()) 
			t.join();
		t = std::move(other.t);
		return *this;
	}
	joining_thread& operator=(std::thread other)noexcept {
		if (t.joinable())
			t.join();
		t = std::move(other);
		return *this;
	}
	~joining_thread()noexcept {
		if (t.joinable())
			t.join();
	}
	void swap(joining_thread& other)noexcept {
		t.swap(other.t);
	}
	std::thread::id get_id()const noexcept {
		return t.get_id();
	}
	bool joinable()const noexcept {
		return t.joinable();
	}
	void join() {
		t.join();
	}
	void detach() {
		t.detach();
	}
	std::thread& as_thread()noexcept {
		return t;
	}
	const std::thread& as_thread()const noexcept {
		return t;
	}
};
//线程安全队列
template<typename T>
class threadsafe_queue {
private:
	mutable std::mutex mut;
	std::queue<T>data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue(){}
	threadsafe_queue(threadsafe_queue const& other) {
		std::lock_guard<std::mutex>lk(other.mut);
	}
	void push(T new_value) {
		std::lock_guard<std::mutex>lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	void wait_and_pop(T& value) {
		std::unique_lock<std::mutex>lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
	}
	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock<std::mutex>lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		std::shared_ptr<T>res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}
	bool try_pop(T& value) {
		std::lock_guard<std::mutex>lk(mut);
		if (data_queue.empty())
			return false;
		value = data_queue.front();
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T>try_pop() {
		std::lock_guard<std::mutex>lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T>res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}
	bool empty()const {
		std::lock_guard<std::mutex>lk(mut);
		return data_queue.empty();
	}
	std::string operator"" s(unsigned long long value)noexcept {
	return std::to_string(value);
	}
};
//数字转二进制O(log)
std::string countOnes(unsigned int n,std::string& str) {
	int ones = 0;
	while (n > 0) {
		ones = (1 & n);//取数字n的最后一位，只会是0或者1,1表示最后一位是奇数，0则不是
		str += std::to_string(ones);
		n >>= 1;
	}
	std::ranges::reverse(str);//反转
	return str;
}

//任意进制转10进制

void func()
{
    int r,i=0,ans=0;
    std::string n;
    std::cin>>r>>n;//R表示进制,N表示要转换的数，ans表示要转换的结果。
    while(n.size()!=i)
    {
        ans*=r;       //我这里是把1看成0，把0看成1来算的。这样比较方便。其实都一样。
        ans+=n[i]-'0';
        i++;
    }
    std::cout<<ans<<std::endl;
 } 
#endif
