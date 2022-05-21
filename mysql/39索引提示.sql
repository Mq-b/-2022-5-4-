create index idx_user_pro on tb_user(profession);   -- 创建单列索引

-- 之前已经为这个字段创建了联合索引 我们再次创建单列索引 我们查看它会使用那个
explain select * from tb_user where profession='软件工程';
-- 使用的是联合索引  这是mysql自动优化的选择


-- SQL提示 是优化数据库的一个重要手段 简单来说 就是在SQL语句中加入一些人为的提示来达到优化操作的目录
-- use index           相当于给mysql建议用我的索引idx_user_pro
explain select * from tb_user use index(idx_user_pro) where profession='软件工程';  -- 单列索引
-- ignore index        忽略的意思 忽略idx_user_pro索引
explain select * from tb_user ignore index(idx_user_pro) where profession='软件工程';
-- force index         强制使用指定的索引idx_user_pro 
explain select * from tb_user force index(idx_user_pro) where profession='软件工程';