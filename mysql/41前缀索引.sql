-- 前缀索引
-- 当字段类型为字符串(varchar,test等)时 有时候需要索引很长的字符串 这会让索引变得很大 查询时 浪费大量的磁盘IO 影响查询效率 
-- 此时可以只将字符串的一部分前缀 建立索引 这样可以大大节约索引空间 从而提高索引效率
-- 语法
create index id xxxx on table name(column(n));
-- 前缀长度
-- 可以根据索引的选择性来决定 而选择性是指不重复的索引值 和数据表的记录总数的比值 索引选择性越高则查询效率越高
-- 唯一索引的选择性是1 这是最好的索引选择性 性能也是最好的
select count(distinct email)/count(*) from tb_user;
select count(distinct substring(email,1,5))/count(*) from tb_user;

-- 我们发现5个字符最合适 就创建前缀索引
create index idx_email_5 on tb_user(email(5));

-- 查询试试有没有用到这个索引
select * from tb_user where email='lvbu666@163.com';