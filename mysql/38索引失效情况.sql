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