-- 创建表共享读锁   给score表加上读锁
lock tables score read;

-- 释放表锁
unlock tables;

-- 读锁不影响自身和其他客户端的读操作 但是创建读锁的客户端如果进行update等写操作会报错
-- 而别的客户端则是会堵塞状态 直到创建读锁的客户端释放锁

-- 创建表独占写锁
lock tables score write;

-- 释放和读锁一样
unlock tables;

-- 表独占写锁创建之后可以在当前客户端进行读写操作   别的客户端不管是读还是写都是堵塞状态    必须等到释放表锁后才能执行完成