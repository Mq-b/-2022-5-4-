#include<iostream>
#include<vector>

int main() {
	std::vector v{ 1,2,3,4,5,6,7,8,9,10 };
	v.reserve(100);//设置容量，确保不因为重新申请内存而导致迭代器失效

	auto p = v.begin() + 5;
	std::cout << *p << std::endl;
	//不管是插入还是删除操作都在迭代器p的后面，所以不会导致迭代器失效
	v.push_back(10);
	v.insert(p + 1, 10);
	v.erase(p + 1, p + 2);
	v.pop_back();
	std::cout << *p << std::endl;
}
// 1：插入更改容量，迭代器失效(push_back,insert)
// 2: 迭代器在被修改元素前，迭代器有效
// 3：迭代器在被修改元素后，迭代器失效
