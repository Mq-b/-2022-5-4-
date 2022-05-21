-- 先删除之前添加的单列索引
drop index idx_user_age on tb_user;
drop index idx_user_pro   on tb_user;
-- 尽量使用覆盖索引(查询使用了索引，并且需要范围的列，在该索引中已经全部能够找到) 减少select
explain select * from tb_user where profession='软件工程' and age = 31 and status = '0';    -- 联合查询

explain select id,profession,age,status from tb_user where professio ='软件工程' and age=31 and status = '0';

explain select id,professio,age,status name from tb_user where professio = '软件工程' and age=31 and status= '0';

explain select * from tb_user where professio= '软件工程' and age =31 and status = '0';

-- Extra 含义
-- Using where; Using
-- Index
-- 查找使用了索引，但是需要的数据都在索引列中能找到，所以不需
-- 要回表查询数据
-- Using index
-- condition
-- 查找使用了索引，但是需要回表查询数据

-- 回表查询看黑马P84 10分钟开始