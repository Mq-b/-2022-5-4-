select * from stu where id=1 lock in sharo modo -- 为id为1的行设置行锁

-- 针对唯一索引进行检索时，对已存在的记录精选等值匹配时 将会自动优化为行锁

-- innoDB的行锁是针对于索引加的锁 不通过索引条件检索数据 那么innoDB将对表中的所有记录加锁 此时就会升级为表锁

-- 具体看PDF吧