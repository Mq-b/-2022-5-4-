#include<iostream>
#include<string>
#include<map>
int main(){

	std::pair<int,char>p{1,'A'};
	std::cout<<p.first<<' '<<p.second<<std::endl;

	std::pair<int,char>p2=std::make_pair<int,char>(2,'B');
	std::cout<<p2.first<<' '<<p2.second<<std::endl;

	std::pair<int,char>p3(p2);
	std::cout<<p3.first<<' '<<p3.second<<std::endl;

	std::map<std::string,size_t>m;
	m.insert(std::pair<std::string,size_t>("A",1));
	std::cout<<m["A"]<<std::endl;

	system("pause");
	return 0;
}