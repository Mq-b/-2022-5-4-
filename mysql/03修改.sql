-- 修改id为1的数据中name修改为itheima
update user set name='itheima' where id=1;

-- 修改为id为1的数据，将name修改为小昭，gender修改为女
update user set name='小昭',gender='女' where id=1;

-- 将所有员工入职日期修改为 2008-01-01
update user set entrydate='2008-01-01';-- 不带 'where' 的 'Update' 语句会立刻更新所有表行

-- 删除 gender为女的员工
delete from user where gender='女';

-- 删除所有员工
delete from user;

/*
    update user set name='itheima' where id=1;

    update user set name='小昭'，gender='女' where id=1;

    update user set entrydate='2008-01-01';

    delete from user where gender='女';

    delete from user
*/