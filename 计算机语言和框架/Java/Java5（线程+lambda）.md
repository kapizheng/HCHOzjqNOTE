### 线程

第一种方法：继承Thread类

```java
package j2;
public class C extends Thread{
    public void run()
    {
        for(int i=0;i<20;i++){
            System.out.println("run:"+i);
        }
    }
}
package toy;
import j2.C;

import java.util.*;

public class ttt {
    //抢占式调度，谁优先级高用谁的
    public static void main(String[] args) {
        C c=new C();

        c.start();
        for (int i = 0; i < 20; i++) {
            System.out.println(Thread.currentThread().getName()+"-->"+i);
        }
    }
}
```

第二种方法：实现Runnable接口

```java
package toy;
import j2.C;

import java.util.*;
package j2;

public class C implements Runnable{
    public void run(){
        for (int i = 0; i < 20; i++) {
            System.out.println(Thread.currentThread().getName()+"-->"+i);
        }
    }
}

public class ttt {
    //抢占式调度，谁优先级高用谁的
    public static void main(String[] args) {
        C c=new C();
        Thread t = new Thread(c);
        t.start();
        for (int i = 0; i < 20; i++) {
            System.out.println(Thread.currentThread().getName()+"-->"+i);
        }
    }
}
```

- 避免了单继承的局限性。

- 增强了程序的扩展性，降低了程序的耦合性，实现Runnable接口的方式，把设置线程任务和开启新线程任务分开。

- 匿名内部类的用法。

### 线程安全

#### 同步代码块：`synchronized`关键字可以用于某个区块中，表示只对这个区块的资源进行互斥访问。

```java
synchronized(同步锁){
    需要同步操作的代码
}
```

- 会降低效率，但是安全性提高

#### 同步方法

```java
修饰符 synchronized 方法名(){

}
```

### Lock锁

Lock接口

有`lock`和`unlock`锁

### 等待与唤醒

```java
package toy;
import j2.C;

import java.util.*;

public class ttt {
    //抢占式调度，谁优先级高用谁的
    public static void main(String[] args) {
        Object obj = new Object();

        new Thread(){
            @Override
            public void run(){
                while(true){
                    synchronized (obj){
                        System.out.println("告诉老板要的包子的数量和种类");

                        try {
                            obj.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        System.out.println("包子好了");
                    }
                }

            }
        }.start();

        new Thread(){
            @Override
            public void run(){

                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (obj){
                    System.out.println("唤醒顾客说做好了，可以吃包子了");
                    obj.notify();
                }
            }
        }.start();
    }
}
```

### wait和sleep带参

表示时间到了就会跳到别的状态

### lambda表达式

```java
(参数列表)->{
    代码块
}
```

```java
package Lambda;

public interface Calculator {
    public int all(int a,int b);
}
package Lambda;

public class Demo01{

    public static void main(String[] args) {
        System.out.println(invokeCalc(2,1,new Calculator(){

            @Override
            public int all(int a, int b) {
                return a+b;
            }
        }));
    }
    public static int invokeCalc(int a,int b,Calculator C){
        return C.all(a,b);
    }

}
```

> - 括号中参数列表类型可以省略不写
> - 括号中的参数中如果职业一个类，那么类型和（）可以省略不写。
> - 如果（）中的代码只有一行，无论是不是有返回值可以省略括号和return;。要省略(),return,分号必须一起省略。

### File文件的构造方法

```java
package toy;

import java.io.File;

public class ttt {
    //抢占式调度，谁优先级高用谁的
    public static void main(String[] args) {
        File f1= new File("C:\\Users\\zjq\\Desktop");
        System.out.println(f1.exists());
    }
}//各种方法直接看api文档就好了。
```

### 文件过滤器

**FileFitter**

可以加lambda表达式

### 字节输出流

```java
package Lambda;
import java.io.FileOutputStream;
import java.io.IOException;

public class Demo01{

    public static void main(String[] args) throws IOException {

        FileOutputStream fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt");
        byte[] a={97,98,99,100,101};

        fos.write(a,1,3);fos.close();
        fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt",true);//追加写

        fos.write(a,1,3);
        fos.close();
        fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt",true);//追加写
        fos.write("\n".getBytes());
        for (int i = 0; i < 20; i++) {
            fos.write("你好".getBytes());
            fos.write("\r\n".getBytes());//换行
        }

    }
}
```

```c++
package Lambda;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Demo01{
    public static void main(String[] args) throws IOException {

        FileOutputStream fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt");
        byte[] a={97,98,99,100,101};
        fos.write(a,1,3);fos.close();
        fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt",true);//追加写
        fos.write(a,1,3);
        fos.close();

        fos = new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt",true);//追加写
        fos.write("\n".getBytes());
        for (int i = 0; i < 20; i++) {
            fos.write("你好".getBytes());
            fos.write("\r\n".getBytes());//换行
        }
        FileInputStream inf = new FileInputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt");
//        int len= inf.read();
//        System.out.println(len);
//        len= inf.read();
//        System.out.println(len);
//        len= inf.read();
//        System.out.println(len);
//        len= inf.read();
//        System.out.println(len);
//        len= inf.read();
//        System.out.println(len);
        //发现以上文件重复。
        int L=0;
        int I=0;
        int []A = new int[1000];
        while ((L=inf.read())!=-1){
            A[I++]=L;
        }
        inf = new FileInputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\a.txt");
        System.out.println("GE"+A.toString());
        byte []B=new byte[1000];
        int len = inf.read(B);
        System.out.println(len);
        System.out.println(new String(B));
    }
}

```

