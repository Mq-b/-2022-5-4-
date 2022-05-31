`ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '密码';` 更改密码

查看数据库db01中的course表的id字段的信息
`mysqlshow -uroot -p1234 db01 course id --count`如果只想看数据库就不加表和字段即可