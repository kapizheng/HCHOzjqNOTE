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
2. 在初始化位置0x7c00设置实地址断点,测试断点正常。
3. 从0x7c00开始跟踪代码运行,将单步跟踪反汇编得到的代码与bootasm.S和 bootblock.asm进行比较。
4. 自己找一个bootloader或内核中的代码位置，设置断点并进行测试。

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