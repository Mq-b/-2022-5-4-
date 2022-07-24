#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int fd;
    fd=open("ps.out",O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd<0){//操作失败的情况
        perror("open ps.out error");
        exit(1);
    }
    dup2(fd,STDOUT_FILENO);//重定向stdout，定向到fd，它储存了文件描述符,标注输出会输出到ps.out文件中
    execlp("ps","ps","aux",NULL);//如果执行成功不会再执行下面的代码,也就没必要关闭文件之类的，依赖系统回收即可
    perror("execlp error");
}

/*返回值

open函数的返回值如果操作成功，它将返回一个文件描述符，如果操作失败，它将返回-1。
参数含义：
1、pathname:

在open函数中第一个参数pathname是指向想要打开的文件路径名，或者文件名。我们需要注意的是，这个路径名是绝对路径名。文件名则是在当前路径下的。
2、flags:

flags参数表示打开文件所采用的操作，我们需要注意的是：必须指定以下三个常量的一种，且只允许指定一个

    O_RDONLY：只读模式
    O_WRONLY：只写模式
    O_RDWR：可读可写

以下的常量是选用的，这些选项是用来和上面的必选项进行按位或起来作为flags参数。

    O_APPEND 表示追加，如果原来文件里面有内容，则这次写入会写在文件的最末尾。
    O_CREAT 表示如果指定文件不存在，则创建这个文件
    O_EXCL 表示如果要创建的文件已存在，则出错，同时返回 -1，并且修改 errno 的值。
    O_TRUNC 表示截断，如果文件存在，并且以只写、读写方式打开，则将其长度截断为0。
    O_NOCTTY 如果路径名指向终端设备，不要把这个设备用作控制终端。
    O_NONBLOCK 如果路径名指向 FIFO/块文件/字符文件，则把文件的打开和后继 I/O设置为非阻塞模式（nonblocking mode）

以下三个常量同样是选用的，它们用于同步输入输出

    O_DSYNC 等待物理 I/O 结束后再 write。在不影响读取新写入的数据的前提下，不等待文件属性更新。
    O_RSYNC read 等待所有写入同一区域的写操作完成后再进行
    O_SYNC 等待物理 I/O 结束后再 write，包括更新文件属性的 I/O

3、mode:

mode参数表示设置文件访问权限的初始值，和用户掩码umask有关，比如0644表示-rw-r–r–，也可以用S_IRUSR、S_IWUSR等宏定义按位或起来表示，详见open(2)的Man Page。要注意的是，有以下几点

    文件权限由open的mode参数和当前进程的umask掩码共同决定。
    第三个参数是在第二个参数中有O_CREAT时才作用，如果没有，则第三个参数可以忽略*/