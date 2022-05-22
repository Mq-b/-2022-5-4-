-- 先删除之前的索引
drop index id_user_phone_name on tb_user;
drop index idx_user_name on tb_user;

-- 排序效率
explain select id,age,phone from tb_user order by age;
-- 创建索引
create index idx_user_age_phone on tb_user(age,phone);
-- 有索引后效率较高
explain select id,age,phone from tb_user order by age;
explain select id,age,phone from tb_user order by age,phone;
explain select id,age,phone from tb_user order by age desc ,phone desc; -- 倒序排序一样使用索引

explain select id,age,phone from tb_user order by phone ,age;
-- 排序时,也需要满足最左前缀法则,否则也会出现 filesort。因为在创建索引的时候， age是第一个
-- 字段，phone是第二个字段，所以排序时，也就该按照这个顺序来，否则就会出现 Using filesortF.

create index idx_user_age_pho_ad on tb_user(age asc,phone desc); -- 创建索引

-- 查看排序缓冲区大小   默认256k
show variables like 'sort_buffer_size';