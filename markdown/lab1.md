

#### 练习1：理解通过make生成执行文件的过程。（要求在报告中写出对下述问题的回答）

列出本实验各练习中对应的OS原理的知识点，并说明本实验中的实现部分如何对应和体现了原理中的基本概念和关键知识点。

在此练习中，大家需要通过静态分析代码来了解：

1. 操作系统镜像文件ucore.img是如何一步一步生成的？(需要比较详细地解释Makefile中每一条相关命令和命令参数的含义，以及说明命令导致的结果)

   先编译很多（16）个.c文件成为内核文件，最后生成了`bootblock`文件**(引导文件)**和`kernel`文件**(系统内核文件)**，同时把他们放到虚拟磁盘哩。**估计就是最后拷贝成一个光盘。**

   ![3](D:\桌面\博客+PDF\ucore\3.jpg)

2. 一个被系统认为是符合规范的硬盘主引导扇区的特征是什么？

   ```c
   最大不能超过512个字节，因为最后2个字节要用作结束标志位
   buf[510]=0x55;
   buf[511]=0xAA;
   ```

   ```
   #include <stdio.h>
   #include <errno.h>
   #include <string.h>
   #include <sys/stat.h>
   
   int main(int argc, char *argv[]) {
       struct stat st;
       // 输入状态判断
       if (argc != 3) {
           fprintf(stderr, "Usage: <input filename> <output filename>\n");
           return -1;
       }
       // 读取文件头
       if (stat(argv[1], &st) != 0) {
           fprintf(stderr, "Error opening file '%s': %s\n", argv[1], strerror(errno));
           return -1;
       }
       // 问题1中输出的文件大小
       printf("'%s' size: %lld bytes\n", argv[1], (long long)st.st_size);
       // 文件大小超过510字节报错返回，因为最后2个字节要用作结束标志位
       if (st.st_size > 510) {
           fprintf(stderr, "%lld >> 510!!\n", (long long)st.st_size);
           return -1;
       }
       // 多余位用0填充
       char buf[512];
       memset(buf, 0, sizeof(buf));
       FILE *ifp = fopen(argv[1], "rb");
       int size = fread(buf, 1, st.st_size, ifp);
       // 文件实际大小需和文件头描述一致
       if (size != st.st_size) {
           fprintf(stderr, "read '%s' error, size is %d.\n", argv[1], size);
           return -1;
       }
       fclose(ifp);
       buf[510] = 0x55;
       buf[511] = 0xAA;
       // 写入结束位
       FILE *ofp = fopen(argv[2], "wb+");
       size = fwrite(buf, 1, 512, ofp);
       if (size != 512) {
           fprintf(stderr, "write '%s' error, size is %d.\n", argv[2], size);
           return -1;
       }
       fclose(ofp);
       printf("build 512 bytes boot sector: '%s' success!\n", argv[2]);
       return 0;
   }
   
   ```

   ![image-20210111212011266](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20210111212011266.png)

补充材料：

如何调试Makefile

当执行make时，一般只会显示输出，不会显示make到底执行了哪些命令。

如想了解make执行了哪些命令，可以执行：

```
$ make "V="
```

要获取更多有关make的信息，可上网查询，并请执行

```
$ man make
```

#### 练习2：使用qemu执行并调试lab1中的软件。（要求在报告中简要写出练习过程）

为了熟悉使用qemu和gdb进行的调试工作，我们进行如下的小练习：

1. 从CPU加电后执行的第一条指令开始，单步跟踪BIOS的执行。

   ![Lab2-1](/home/zhengjiaquan/文档/markdown/Lab2-1.png)

   

   

   

   

2. 在初始化位置0x7c00设置实地址断点,测试断点正常。

3. 从0x7c00开始跟踪代码运行,将单步跟踪反汇编得到的代码与bootasm.S和 bootblock.asm进行比较。

   bootasm.S与gdb中汇编代码一样，但是我不太了解汇编,应该只是格式不一样。

   ![lab2-2](/home/zhengjiaquan/文档/markdown/lab2-2.png)

   ![Lab2-3](/home/zhengjiaquan/文档/markdown/Lab2-3.png)

   发现报了好久的错是自己没装cgdb...

   完成

4. 自己找一个bootloader或内核中的代码位置，设置断点并进行测试。

   这个就不需要怎么调试了吧

> 提示：参考附录“启动后第一条执行的指令”，可了解更详细的解释，以及如何单步调试和查看BIOS代码。
>
> 提示：查看 labcodes_answer/lab1_result/tools/lab1init 文件，用如下命令试试如何调试bootloader第一条指令：
>
> ```
>  $ cd labcodes_answer/lab1_result/
>  $ make lab1-mon
> ```

补充材料： 我们主要通过硬件模拟器qemu来进行各种实验。在实验的过程中我们可能会遇上各种各样的问题，调试是必要的。qemu支持使用gdb进行的强大而方便的调试。所以用好qemu和gdb是完成各种实验的基本要素。

默认的gdb需要进行一些额外的配置才进行qemu的调试任务。qemu和gdb之间使用网络端口1234进行通讯。在打开qemu进行模拟之后，执行gdb并输入

```
target remote localhost:1234
```

即可连接qemu，此时qemu会进入停止状态，听从gdb的命令。

另外，我们可能需要qemu在一开始便进入等待模式，则我们不再使用make qemu开始系统的运行，而使用make debug来完成这项工作。这样qemu便不会在gdb尚未连接的时候擅自运行了。

***gdb的地址断点\***

在gdb命令行中，使用b *[地址]便可以在指定内存地址设置断点，当qemu中的cpu执行到指定地址时，便会将控制权交给gdb。

***关于代码的反汇编\***

有可能gdb无法正确获取当前qemu执行的汇编指令，通过如下配置可以在每次gdb命令行前强制反汇编当前的指令，在gdb命令行或配置文件中添加：

```
define hook-stop
x/i $pc
end
```

即可

***gdb的单步命令\***

在gdb中，有next, nexti, step, stepi等指令来单步调试程序，他们功能各不相同，区别在于单步的“跨度”上。

```
next 单步到程序源代码的下一行，不进入函数。
nexti 单步一条机器指令，不进入函数。
step 单步到下一个不同的源代码行（包括进入函数）。
stepi 单步一条机器指令。
```

跟着报告做就好了

```labinit和gdbinit,一个是正式的一个用来启动的```



#### 练习3：分析bootloader进入保护模式的过程。（要求在报告中写出分析）

BIOS将通过读取硬盘主引导扇区到内存，并转跳到对应内存中的位置执行bootloader。请分析bootloader是如何完成从实模式进入保护模式的。

提示：需要阅读**小节“保护模式和分段机制”**和lab1/boot/bootasm.S源码，了解如何从实模式切换到保护模式，需要了解：

- 为何开启A20，以及如何开启A20
- 如何初始化GDT表
- 如何使能和进入保护模式

![Lab2-4](/home/zhengjiaquan/文档/markdown/Lab2-4.png)

接下去得看文档，感觉记不住。。理解就好了

如何进入保护模式，要把A20开了，因为A20是为了让超过16条地址线的时候只能访问1mb空间

#### 练习4：分析bootloader加载ELF格式的OS的过程。（要求在报告中写出分析）

通过阅读bootmain.c，了解bootloader如何加载ELF文件。通过分析源代码和通过qemu来运行并调试bootloader&OS，

- bootloader如何读取硬盘扇区的？
- bootloader是如何加载ELF格式的OS？
- <img src="/home/zhengjiaquan/文档/markdown/Lab2-5.png" alt="Lab2-5" style="zoom:75%;" />

校验魔数，然后读取到内存。

提示：可阅读“硬盘访问概述”，“ELF执行文件格式概述”这两小节。

#### 硬盘访问概述

bootloader让CPU进入保护模式后，下一步的工作就是从硬盘上加载并运行OS。考虑到实现的简单性，bootloader的访问硬盘都是LBA模式的PIO（Program IO）方式，即所有的IO操作是通过CPU访问硬盘的IO地址寄存器完成。

一般主板有2个IDE通道，每个通道可以接2个IDE硬盘。访问第一个硬盘的扇区可设置IO地址寄存器0x1f0-0x1f7实现的，具体参数见下表。一般第一个IDE通道通过访问IO地址0x1f0-0x1f7来实现，第二个IDE通道通过访问0x170-0x17f实现。每个通道的主从盘的选择通过第6个IO偏移地址寄存器来设置。

表一 磁盘IO地址和对应功能

第6位：为1=LBA模式；0 = CHS模式        第7位和第5位必须为1

| IO地址 | 功能                                                         |
| ------ | ------------------------------------------------------------ |
| 0x1f0  | 读数据，当0x1f7不为忙状态时，可以读。                        |
| 0x1f2  | 要读写的扇区数，每次读写前，你需要表明你要读写几个扇区。最小是1个扇区 |
| 0x1f3  | 如果是LBA模式，就是LBA参数的0-7位                            |
| 0x1f4  | 如果是LBA模式，就是LBA参数的8-15位                           |
| 0x1f5  | 如果是LBA模式，就是LBA参数的16-23位                          |
| 0x1f6  | 第0~3位：如果是LBA模式就是24-27位     第4位：为0主盘；为1从盘 |
| 0x1f7  | 状态和命令寄存器。操作时先给命令，再读取，如果不是忙状态就从0x1f0端口读数据 |

当前 硬盘数据是储存到硬盘扇区中，一个扇区大小为512字节。读一个扇区的流程（可参看boot/bootmain.c中的readsect函数实现）大致如下：

1. 等待磁盘准备好
2. 发出读取扇区的命令
3. 等待磁盘准备好
4. 把磁盘扇区数据读到指定内存

#### 练习5：实现函数调用堆栈跟踪函数 （需要编程）

我们需要在lab1中完成kdebug.c中函数print_stackframe的实现，可以通过函数print_stackframe来跟踪函数调用堆栈中记录的返回地址。在如果能够正确实现此函数，可在lab1中执行 “make qemu”后，在qemu模拟器中得到类似如下的输出：

```
……
ebp:0x00007b28 eip:0x00100992 args:0x00010094 0x00010094 0x00007b58 0x00100096
    kern/debug/kdebug.c:305: print_stackframe+22
ebp:0x00007b38 eip:0x00100c79 args:0x00000000 0x00000000 0x00000000 0x00007ba8
    kern/debug/kmonitor.c:125: mon_backtrace+10
ebp:0x00007b58 eip:0x00100096 args:0x00000000 0x00007b80 0xffff0000 0x00007b84
    kern/init/init.c:48: grade_backtrace2+33
ebp:0x00007b78 eip:0x001000bf args:0x00000000 0xffff0000 0x00007ba4 0x00000029
    kern/init/init.c:53: grade_backtrace1+38
ebp:0x00007b98 eip:0x001000dd args:0x00000000 0x00100000 0xffff0000 0x0000001d
    kern/init/init.c:58: grade_backtrace0+23
ebp:0x00007bb8 eip:0x00100102 args:0x0010353c 0x00103520 0x00001308 0x00000000
    kern/init/init.c:63: grade_backtrace+34
ebp:0x00007be8 eip:0x00100059 args:0x00000000 0x00000000 0x00000000 0x00007c53
    kern/init/init.c:28: kern_init+88
ebp:0x00007bf8 eip:0x00007d73 args:0xc031fcfa 0xc08ed88e 0x64e4d08e 0xfa7502a8
<unknow>: -- 0x00007d72 –
……
```

请完成实验，看看输出是否与上述显示大致一致，并解释最后一行各个数值的含义。

提示：可阅读小节“函数堆栈”，了解编译器如何建立函数调用关系的。在完成lab1编译后，查看lab1/obj/bootblock.asm，了解bootloader源码与机器码的语句和地址等的对应关系；查看lab1/obj/kernel.asm，了解 ucore OS源码与机器码的语句和地址等的对应关系。

要求完成函数kern/debug/kdebug.c::print_stackframe的实现，提交改进后源代码包（可以编译执行），并在实验报告中简要说明实现过程，并写出对上述问题的回答。

补充材料：

由于显示完整的栈结构需要解析内核文件中的调试符号，较为复杂和繁琐。代码中有一些辅助函数可以使用。例如可以通过调用print_debuginfo函数完成查找对应函数名并打印至屏幕的功能。具体可以参见kdebug.c代码中的注释。

**理解：**

![Lab2-6](/home/zhengjiaquan/文档/markdown/Lab2-6.png)

要完成实验首先必须了解函数栈的构建过程

- `ebp`为基址指针寄存器
- `esp`为堆栈指针寄存器(指向栈顶)
- `ebp`寄存器处于一个非常重要的地位，该寄存器中存储着栈中的一个地址（原`ebp`入栈后的栈顶），从该地址为基准，向上（栈底方向）能获取返回地址、参数值，向下（栈顶方向）能获取函数局部变量值，而该地址处又存储着上一层函数调用时的`ebp`值
   举一个实际的例子查看`ebp`与`esp`两个寄存器如何构建出完整的函数栈：
   `leave`等同于`movl %ebp, %esp`，`popl %ebp`两条指令

#### 练习6：完善中断初始化和处理 （需要编程）

请完成编码工作和回答如下问题：

1. 中断描述符表（也可简称为保护模式下的中断向量表）中一个表项占多少字节？其中哪几位代表中断处理代码的入口？

   64（8字节）

   ```c
   unsigned gd_off_15_0 : 16;        
   unsigned gd_ss : 16;  
   unsigned gd_off_31_16 : 16;   
   ```

   有三种中断：

   - trap(系统调用)
   - exception(异常)（同步中断，内部中断）
   - 设备中断（时钟，IO）异步中断，外部中断。

   **特权中断**

   有一些中断需要陷入内核去进行，当陷入进去之后还需要再跳出来。

2. 请编程完善kern/trap/trap.c中对中断向量表进行初始化的函数idt_init。在idt_init函数中，依次对所有中断入口进行初始化。使用mmu.h中的SETGATE宏，填充idt数组内容。每个中断的入口由tools/vectors.c生成，使用trap.c中声明的vectors数组即可。

3. 请编程完善trap.c中的中断处理函数trap，在对时钟中断进行处理的部分填写trap函数中处理时钟中断的部分，使操作系统每遇到100次时钟中断后，调用print_ticks子程序，向屏幕上打印一行文字”100 ticks”。

> 【注意】除了系统调用中断(T_SYSCALL)使用陷阱门描述符且权限为用户态权限以外，其它中断均使用特权级(DPL)为０的中断门描述符，权限为内核态权限；而ucore的应用程序处于特权级３，需要采用｀int  0x80`指令操作（这种方式称为软中断，软件中断，Tra中断，在lab5会碰到）来发出系统调用请求，并要能实现从特权级３到特权级０的转换，所以系统调用中断(T_SYSCALL)所对应的中断门描述符中的特权级（DPL）需要设置为３。

要求完成问题2和问题3  提出的相关函数实现，提交改进后的源代码包（可以编译执行），并在实验报告中简要说明实现过程，并写出对问题1的回答。完成这问题2和3要求的部分代码后，运行整个系统，可以看到大约每1秒会输出一次”100 ticks”，而按下的键也会在屏幕上显示。

提示：可阅读小节“中断与异常”。

最后总算是搞定了！！！

![Lab2-7](/home/zhengjiaquan/文档/markdown/Lab2-7.png)

# 关键在于好好读doc



