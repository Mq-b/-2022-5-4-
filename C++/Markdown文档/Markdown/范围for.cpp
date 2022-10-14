#include<iostream>

#define for_each(a,b)\
for(auto i:X(a,b))	 \


struct X {
	X(int* v, int n) :p(v), n(n){}

	auto* begin() {
		return this->p;
	}
	auto* end() {
		return this->p + n;
	}
private:
	int* p;
	int n;
};

int main() {
	int array[]{ 1,2,3,4,5 };
	for_each(array, 5) {
		std::cout << i << std::endl;
	}
}
