select profession,count(*) from tb_user group by profession; -- 查询分组
explain select profession,count(*) from tb_user group by profession;  -- 效率

-- 创建联合索引
create index idx_user_pro_age_sta on tb_user(profession,age,status);
explain select profession,count(*) from tb_user group by profession;  -- 效率
explain select age,count(*) from tb_user group by age;
explain select age,count(*) from tb_user group by profession,age; -- 满足最左前缀法则
explain select age,count(*) from tb_user where profession='软件工程' group by age; -- 满足最左前缀法则