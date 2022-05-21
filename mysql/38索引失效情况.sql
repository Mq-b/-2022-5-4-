-- 1.不要在索引列上进行运算操作 索引将失效
explain select * from tb_user where substring(phone,10,2)='15';


-- 2.字符串不加引号索引将失效  phon是varchar类型 所以不加单引号会进行隐式转换 不会使用索引 但是可以查询到
select * from tb_user where phone=17799990015;
-- 查询看看运行策略
explain select * from tb_user where phone=17799990015;


-- 3.模糊查询   如果仅仅是尾部进行模糊匹配 索引是不会失效。如果头部模糊匹配 索引失效
select * from tb_user where profession like'软件%';
-- 查询运行策略我们知道这个是尾部模糊匹配 索引不失效
explain select * from tb_user where profession like'软件%'; 
-- 尾部模糊查询两种     索引失效
explain select * from tb_user where profession like'%工程';
explain select * from tb_user where profession like'%工%';


-- 4.or连接条件 用or分割开的条件 如果or前的条件 如果一侧有索引 一侧没有 则整个索引都会失效
explain select * from tb_user where id=10 or age=23;    -- id有索引 age没有索引 索引失效
explain select * from tb_user where phone='17799990017' or age=23;  -- age没有索引 索引失效
-- 给age建立索引即可
create index idx_user_age on tb_user(age);


-- 5.数据分布影响 如果mysql评估使用索引比全表更慢 则不使用索引
explain select * from tb_user where phone>='17799990020';   -- 正常使用索引
explain select * from tb_user where phone>='17799990000';   -- 索引失效 all全盘扫描 因为这个条件是所有都不满足的
explain select * from tb_user where phone>='17799990010';   -- 索引依然失效 满足这个调剂的数据比不满足的少 
explain select * from tb_user where phone>='17799990013';   -- 索引生效 总共24条数据 设置的条件为大于等于13 满足条件的更多 所以使用索引


-- 6. is null  is not null 走不走索引取决于数据库表结构字段数据的分布情况 和5.差不多 数据稀有的就走索引 多的就不走
explain select * from tb_user where profession is null;         -- 走索引
explain select * from tb_user where profession  is not null;    -- 不走索引
update tb_user set profession = null;                           -- 所有字段更新为null
explain select * from tb_user where profession is null;         -- 不走索引
explain select * from tb_user where profession  is not null;    -- 走索引