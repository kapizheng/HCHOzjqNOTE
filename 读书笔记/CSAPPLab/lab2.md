### 指令

```gdb 执行文件名```

- 再调用`layout asm`切换到汇编模式

### IF的底层有两种形式

- 一种是条件控制，该方法是一开始直接cmp，然后跳转

- 一种是条件传送，该方法是一开始计算出所有的结构，最后采用条件传送方式赋值。

### switch跳转指令底层原理

- 会先生成一个静态表，该表存放的是每个跳转的分支的地址。
- 然后对需要判断的数值进行一个优化，直接按照其索引去该静态表中拿去数据即可。

lea是讲计算好的值赋值给要赋值得地址

move是讲该地址上的值赋值过去。假如是mov $20(%ebp),%eax,就是将*（ebp+20）

### 汇编中的call和ret

- 先明白两个寄存器：rsp和rip
- rsp表示栈指针，也就是当前栈的栈顶。
- rip表示当前汇编代码运行到了哪里。
  - 当调用call，会先将参数传进去，再将返回地址（也就是call的下一行汇编代码地址）压入栈中。
  - 再将rip变为要调用的函数的地址。
  - 当调用ret的时候，会将rsp的数据取出，放到rip上，且同时将rsp向上移动一下，也就是pop一下。

- 所谓的栈中，存放的只是局部变量+返回地址，每次压栈的时候都会将返回地址压进去。

### 函数的参数一般少于6个的话，会存放到寄存器上，多余6个才会放到栈上。

建议做此实验前，好好了解一下gdb的常规使用，objdump只需要知道-d是反汇编为汇编代码就够了。

这里简单的介绍一下gdb吧。

- gdb 目标文件
- gdb之后在里面使用的指令
  - b 打断点
    - b *十六进制地址
    - b 函数名
  - d 删除断点
    - d 数字 删除第几个
  - p /xdt 寄存器，地址：分别用十六进制，10进制、8进制显示。
  - x 列出数字感觉和p差不多，但是p可以强转。
  - r 执行，直到到了断点就停止。
  - c断点后继续执行，直到到达下一个断点。
  - info r显示所有的寄存器上的内容。

### phase1

```assembly
0000000000400ee0 <phase_1>:
  400ee0:       48 83 ec 08             sub    $0x8,%rsp
  400ee4:       be 00 24 40 00          mov    $0x402400,%esi
  400ee9:       e8 4a 04 00 00          callq  401338 <strings_not_equal>
  400eee:       85 c0                   test   %eax,%eax
  400ef0:       74 05                   je     400ef7 <phase_1+0x17>
  400ef2:       e8 43 05 00 00          callq  40143a <explode_bomb>
  400ef7:       48 83 c4 08             add    $0x8,%rsp
  400efb:       c3                      retq
```

- 该phase1比较简单，主要是掌握`test+je`是检测`eax`是否为0就足够了。`je`是将两个操作数与起来，假如相同跳到`400ef7`
- 要注意的是`eax`一般用来放返回值，而`esi`用来放参数。
- 这个实验带上<>的字符串都是字面意思D:
- 那么这个实验翻译为大白话就是：将`0x402400`放到`esi`上，调用`strings_not_equel`函数，返回值放到eax上，假如为0，也是就字符串一样就跳过`bomb`。
- 直接查看0x402400上的字符串就好了，可以使用`x/s 地址'

### phase 2

```assembly
0000000000400efc <phase_2>:
  400efc:       55                      push   %rbp
  400efd:       53                      push   %rbx
  400efe:       48 83 ec 28             sub    $0x28,%rsp
  400f02:       48 89 e6                mov    %rsp,%rsi
  400f05:       e8 52 05 00 00          callq  40145c <read_six_numbers>
  400f0a:       83 3c 24 01             cmpl   $0x1,(%rsp)
  400f0e:       74 20                   je     400f30 <phase_2+0x34>
  400f10:       e8 25 05 00 00          callq  40143a <explode_bomb>
  400f15:       eb 19                   jmp    400f30 <phase_2+0x34>
  400f17:       8b 43 fc                mov    -0x4(%rbx),%eax
  400f1a:       01 c0                   add    %eax,%eax
  400f1c:       39 03                   cmp    %eax,(%rbx)
  400f1e:       74 05                   je     400f25 <phase_2+0x29>
  400f20:       e8 15 05 00 00          callq  40143a <explode_bomb>
  400f25:       48 83 c3 04             add    $0x4,%rbx
  400f29:       48 39 eb                cmp    %rbp,%rbx
  400f2c:       75 e9                   jne    400f17 <phase_2+0x1b>
  400f2e:       eb 0c                   jmp    400f3c <phase_2+0x40>
  400f30:       48 8d 5c 24 04          lea    0x4(%rsp),%rbx
  400f35:       48 8d 6c 24 18          lea    0x18(%rsp),%rbp
  400f3a:       eb db                   jmp    400f17 <phase_2+0x1b>
  400f3c:       48 83 c4 28             add    $0x28,%rsp
  400f40:       5b                      pop    %rbx
  400f41:       5d                      pop    %rbp
  400f42:       c3                      retq
```

D:不想写了（bushi

