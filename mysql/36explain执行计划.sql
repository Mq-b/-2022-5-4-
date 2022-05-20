-- EXPLAIN 或者 DESC命令获取 MySQL 如何执行 SELECT 语句的信息，包括在 SELECT 语句执行
-- 过程中表如何连接和连接的顺序。

-- 语法
-- -- 直接在select语句之前加上关键字 explain / desc
-- EXPLAIN SELECT 字段列表 FROM 表名 WHERE 条件 ;