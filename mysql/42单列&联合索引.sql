explain select id,phone,name from tb_user where phone='17799990010' and name='韩信';
-- 多表联合查询时 mysql优化会评估哪个字段的索引效率更高 会选择该索引完成本次查询

-- 创建联合索引     在创建联合索引的时候我们要考虑顺序 最左前缀法则 比如现在如果要使用这个联合索引必须要用phone
create unique index idx_phone_name on tb_user(phone,name);