#include<iostream>
#include<fstream>
template<typename T=std::wstring>
std::string newWriteFile(T data, std::string name = std::string("1") += ".txt", std::string path = "") {
	path += name;
	std::wofstream ofs;
	ofs.open(path, std::ios::app);
	ofs << data;
	ofs.close();
	return path;
}
int main() {
	std::locale::global(std::locale{ "" });
	newWriteFile(std::wstring(L"舒服"));
}
