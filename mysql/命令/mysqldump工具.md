Linux下备份mysql的db01数据库命令
`mysqldump -uroot -p1234 db01 > db01.sql` 

这个命令有众多的输出选项 比如我们备份的文件里如果不想包含建表语句 可以加个`-t`
`mysqldump -uroot -p1234 -t db01 > db01.sql` 