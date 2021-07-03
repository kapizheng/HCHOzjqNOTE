### java笔记

#### 杂项

- javac不能用是路径问题

- 一个源文件至多只能声明一个public的类，文件名必须和public的类名一样且扩展名为`.java`。
- 常用的DOS命令
  - cd 目录路径
  - cd...返回父目录
  - dir查看子目录列表
  - cls清除屏幕
  - tab自动补齐

#### 变量

- 静态变量从属于类，生命周期伴随类始终，而不是对象。
- 常量的表示方法`final type varName = value;`
- float赋值要后面要加f/F，不然会默认为double。会报错。
- 大数，和精确数字类要用`import java.math.*;`

- java的char用的是Unicode编码，可以有65536个编码
- 余数的结果符号与左操作符相同

#### 运算符号

&，&&，|，||，

逻辑与，短路与，逻辑或，短路或

短路的和C和CPP一样，节省时间。逻辑需要两个都判断。

#### Scanner

1、`import java.util.Scanner;`

```
Scanner scanner=new Scanner(System.in);
System.out.println("请输入afdjsa");
String name=scanner.nextLine();
System.out.pringln("请输入")
int age=scanner.nextInt();
```

#### statis

的方法可以在类里调用，不需要`new`

- 一个java程序只有一个public类

#### 垃圾回收机制

- 引用计数法——>循环应用无法用这个方法。
- 引用可达法，跑图，剩下没遇到就是垃圾

- 年轻代，年老代，持久代

  - 年轻代久了就到年老代

    - MinorGC：清除年轻代区域（Eden区满了就会触发一次）

      复制到survivor1和survivor2里面，这两个只有一个在用，一个为空

    - MajorGC：清除年老代区域

    - FullGC：两种都清理。成本高。

- System.gc()：建议系统调用垃圾回收

#### 对象的创建

- ![image-20191213002751473](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20191213002751473.png)

- this是一个已经创建好的对象地址。
  - this.变量
  - this(变量序列)调用类里的构造器。
  - 对象才可以调用

#### static修饰

- 修饰的成员属于类，不属于对象。
- 静态方法不能使用非静态方法和变量。
- static有块的说法，加载的时候每次都先执行static块，然后再构造

#### 传值和传地址

传值就直接是类型，如果是地址应该是类名。引用的一些特性。

new会新建一个对象，也就是用不同地址改了创建。new赋值给一个变量应该是赋值了该地址，但是原来的地址没改变。

![image-20191213210625179](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20191213210625179.png)

类似于传递的是一个__指针变量的拷贝__，赋值给这个变量地址和改变这个地址上的东西是不一样的。类似于CPP中的引用

#### package

package打包。import使用包。

静态导入：`import static java.lang.Math.*`

命名：xxx.xxx。可以倒着写。

java提供的包：

- java.lang包含一些Java语言的核心类：String，Math，System，Thread等。不需要导入就可以使用
- java.awt包含了抽象窗口工具集
- java.net包含执行与网络相关操作的类
- java.io包含能够提供多种输入输出的类
- java.util包含一些实用工具类，如定义系统特性，使用日期等。

#### 继承

- extends的用法：A extends B，A继承于B

- instanceof：用来判断一个对象是不是这个类或者是其子类

  `stu instanceof Student`输出true

#### 重写override

“==“子类和父类的方法名形参列表相同。

”<="子类的放回类型和声明异常类型，子类要小于等于父类。

“>="访问权限子类要大于父类。

#### ==和equal

equal可以自己写，可以借助IDE，有源码

#### super父类

继承类都会有一个super方法

#### 继承

同一个类<同一个包<子类<所有类

private<default<protected<public

- 类前面不加public就只能当前包使用，加了就可以别的包用

- 自动向上转型，强制向下转型。

#### final

修饰变量，改变量为常量

修饰方法，该方法不可被子类重写，但是可被重载

修饰类，该类不能被继承

#### 数组

`int []arr=new arr[10]`

声明了一个10个元素的数组。

```
//静态初始化
int []a={2,3,4,23};
user[] b={
	new user(1001,"123");
	new user(1001,"233");
}
//默认初始化
int []c=new int(3);
//动态初始化化
int []a=new int(2);
a[0]=1;a1[1]=1;
```

`for_each`用来读取数组或者集合中所有元素。

```Java
for(int m:a){
	System.out.println(m);
}
```

 