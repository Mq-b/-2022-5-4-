/*
    函数原型: void *mmap (void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    参数:
    addr指定文件应被映射到进程空间的起始地址，一般被指定一个NULL，此时选择起始地址的任务留给内核来完成。
    len是映射到调用进程地址空间的字节数，它从被映射文件开头offset个字节开始算起。
    prot 参数指定共享内存的访问权限。可取如下几个值的或：PROT_READ（可读） , PROT_WRITE （可写）, PROT_EXEC （可执行）, PROT_NONE（不可访问）。
    flags由以下几个常值指定：MAP_SHARED , MAP_PRIVATE , MAP_FIXED，其中，MAP_SHARED , MAP_PRIVATE必选其一，而MAP_FIXED则不推荐使用。offset参数一般设为0，表示从文件头开始映射。
    fd为即将映射到进程空间的文件描述字，一般由open()返回，同时，fd可以指定为-1，此时须指定flags参数中的MAP_ANON，表明进行的是匿名映射（不涉及具体的文件名，避免了文件的创建及打开，很显然只能用于具有亲缘关系的进程间通信）。
    offset参数一般设为0，表示从文件头开始映射, 代表偏移量。需要是4k的整数倍

    返回值:
    函数的返回值为最后文件映射到进程空间的地址，进程可直接操作起始地址为该值的有效地址。
*/

/*
    mmap函数最保险的调用方式！！！！！！！:
    fd=open("文件名",O_RDWR);
    mmap(NULL,有效文件大小,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
*/
/*mmap内存映射是所有进程通信中效率最高的方式*/
