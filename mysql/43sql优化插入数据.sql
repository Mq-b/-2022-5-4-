-- insert 优化
-- 批量插入
inset into tb_test values(1,'Tom'),(2,'Cat'),(3,'Jerry');

-- 手动提交事务
start transaction;
-- 插入语句
commit;

-- 主键顺序插入提升效率     就是按照有序插入

