-- 在 tb_user 表中，有一个联合索引，这个联合索引涉及到三个字段，顺序分别为：profession，
-- age，status。
-- 对于最左前缀法则指的是，查询时，最左变的列，也就是profession必须存在，否则索引全部失效。
-- 而且中间不能跳过某一列，否则该列后面的字段索引将失效。 接下来，我们来演示几组案例，看一下
-- 具体的执行计划：
explain select * from tb_user where profession = '软件工程' and age = 31 and status= '0';
explain select * from tb_user where profession = '1 软件工程' and age = 31;
explain select * from tb_user where profession 1 = '软件工程';
-- 以上的这三组测试中，我们发现只要联合索引最左边的字段 profession存在，索引就会生效，只不
-- 过索引的长度不同。 而且由以上三组测试，我们也可以推测出profession字段索引长度为47、age
-- 字段索引长度为2、status字段索引长度为5。

explain select * from tb_user where age = 31 and status = '0';
explain select * from tb_user where status = '0';
-- 而通过上面的这两组测试，我们也可以看到索引并未生效，原因是因为不满足最左前缀法则，联合索引
-- 最左边的列profession不存在。

-- 查询一张表的索引
show index from tb_user;

-- 注意 ： 最左前缀法则中指的最左边的列，是指在查询时，联合索引的最左边的字段(即是
-- 第一个字段)必须存在，与我们编写SQL时，条件编写的先后顺序无关。   比如下面这个
explain select * from tb_user where age = 31 and status = '0' and profession = '软件工程';

-- 最后强调一下这个最左是指的使用index查询语句查询到的联合索引的id为1的第一个出现的就是最左索引