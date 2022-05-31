Linux下备份mysql的db01数据库命令
`mysqldump -uroot -p1234 db01 > db01.sql` 

这个命令有众多的输出选项 比如我们备份的文件里如果不想包含建表语句 可以加个`-t`
`mysqldump -uroot -p1234 -t db01 > db01.sql` 

语法 ：
mysqldump [options] db_name [tables]
mysqldump [options] --database/-B db1 [db2 db3...]
mysqldump [options] --all-databases/-A
连接选项 ：
-u, --user=name 指定用户名
-p, --password[=name] 指定密码
-h, --host=name 指定服务器ip或域名
-P, --port=# 指定连接端口
输出选项：
--add-drop-database 在每个数据库创建语句前加上 drop database 语句
--add-drop-table 在每个表创建语句前加上 drop table 语句 , 默认开启 ; 不开启 (--skip-add-drop-table)
-n, --no-create-db 不包含数据库的创建语句
-t, --no-create-info 不包含数据表的创建语句
-d --no-data 不包含数据
-T, --tab=name 自动生成两个文件：一个.sql文件，创建表结构的语句；一个.txt文件，数据文件
**用于备份的文件不存在会自动创建**

使用 **`show variables like'%secure_file_priv%';`可以查看mysql信任觉得安全的目录**也就是备份应所在的目录

再举个例子 通过mysql下的source指令可以把之前备份的sql语句执行 假如不小心删除的就可以恢复 如下
`source /root/db01.sql`注意得确保mysql在db01的数据库下 很常用
同时也可以导入执行了-T的备份语句产生的txt文件 例如`mysqlimport -uroot -p1234 test/city.txt` 不展开讲 注意路径和文件名匹配