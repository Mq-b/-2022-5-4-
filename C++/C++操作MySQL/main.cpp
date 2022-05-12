#include "MySQL.h"

int main()
{
	DataBase* d1 = new DataBase;
	//连接
	d1->Connect("localhost", "root", "123456", "itcast", 0);
	printf("\n");
	//查询表
	d1->Query("emp");
	printf("\n");
	//添加内容
	//d1->Implement("insert into emp(id,workno,name,gender,age,idcard,workaddress,entrydate) values(7,'0007','归故里', '男', 20, '1235647895455','江西','2005-11-08')");
	printf("\n");
	//查询表
	d1->Query("emp");
	printf("\n");
	return 0;
}
