-- 查看sql的执行频率      也就是查看查询次数 修改次数之类的
-- session 是查看当前会话 ;
-- global 是查询全局数据 ;
SHOW GLOBAL STATUS LIKE 'Com_______';

-- Com_delete: 删除次数
-- Com_insert: 插入次数
-- Com_select: 查询次数
-- Com_update: 更新次数

-- 查询慢查询系统变量   默认没有打开
show variables like 'slow_query_log';
-- 如果要开启慢查询日志，需要在MySQL的配置文件（/etc/my.cnf）中配置如下信息：
-- # 开启MySQL慢日志查询开关
-- slow_query_log=1
-- # 设置慢日志的时间为2秒，SQL语句执行时间超过2秒，就会视为慢查询，记录慢查询日志
-- long_query_time=2

-- 然后  Linux下重启MySQL命令如下
-- systemctl restart mysqld

-- cd /var/lib/mysql                       转到Linux下存放查询慢日志的目录
--cat hspEdu01-slow.log                    查看文件内容
-- tail -f hspEdu01-slow.log               使用tail -f指令查找慢日志文件的实时更新
-- 再另一边执行sql语句  就会显示了           慢查询日志会记录着这些慢的sql语句
-- 我们刚才设置了必须查询时间超过两秒的才会记录