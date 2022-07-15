#include<json/json.h>
#include<iostream>
#include<fstream>
/*Json如下
[
	"luffy",
	19,
	170,
	false,
	[
		"ace",
		"sabo"
	],
	{
		"girlfriend" : "Hancok",
		"sex" : "man"
	}
]
*/
using namespace Json;//命名空间
void writeJson() {
	Json::Value root;
	root.append("luffy");
	root.append(19);
	root.append(170);
	root.append(false);

	Value subArray;
	subArray.append("ace");
	subArray.append("sabo");
	root.append(subArray);

	Value obj;
	obj["sex"] = "man";
	obj["girlfriend"] = "Hancok";
	root.append(obj);
#if 1
	std::string json = root.toStyledString();//该换行就换行，看着直观
#else
	Json::FastWriter W;	//使用这种方式写入到磁盘文件中是没有格式的,就是都挤在一行
	std::string json = W.write(root);
#endif

	std::ofstream ofs("test.json");
	ofs << json;
	ofs.close();
}

void readJson() {
	std::ifstream ifs("test.json");
	Json::Reader rd;
	Json::Value root;
	rd.parse(ifs, root);//将文件的数据写入root对象

	if (root.isArray()) {//判断是否为json数组
		for (auto i : root) {
			if (i.isInt()) {
				std::cout << i.asInt() << ",";
			}
			else if (i.isString()) {
				std::cout << i.asString() << ",";
			}
			else if (i.isBool()) {
				std::cout << i.asBool() << ",";
			}
			else if (i.isArray())
			{
				for (auto j : i)
					std::cout << j.asString() << ",";
			}
			else if (i.isObject())
			{
				Json::Value::Members keys = i.getMemberNames();
				for (auto k : keys)
					std::cout << k << ":" << i[k] << ",";
			}
			std::endl(std::cout);//换行
		}
	}
	else if (root.isObject()) {//对象

	}
}

int main() {
	writeJson();//写
	readJson();//读
	//实际我们写的时候没必要写的那么复杂，我们只是试试这些成员函数，因为json文件格式是有序的，我们想要解析什么样的json文件那就写成什么样就好
}