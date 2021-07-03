## 类

### 匿名对象

只有右边的对象，没有左边的名字和赋值运算符。

`new person().方法名/变量名`

方法或者变量只用一次的情况可以使用。

### Random

在包`java.util.Random`里面。

```java
import java.util.Random;
public class Java_try {

    public static void main(String[] args) {
        Random ran = new Random();
        int r=ran.nextInt();
        System.out.println(r);
    }
}

```

**其他用法**

表示：[0,9]

```java
import java.util.Random;
public class Java_try {

    public static void main(String[] args) {
        Random ran = new Random();
        for(int i=0;i<10;i++){
            System.out.println(ran.nextInt(10));
        }
    }
}
```

### Arraylist

```java
import java.util.ArrayList;
import java.util.Random;
public class Java_try {

    public static void main(String[] args) {
        Random ran = new Random();

        ArrayList<Person> list=new ArrayList<>();//尖括号里面可以不写东西，默认为左边尖括号里的内容。

        Person zjq=new Person("zjq",20);
        Person zjh=new Person("zjh",19);
        list.add(zjq);
        boolean ok=list.add(zjh);//返回值表示插入是不是成功的。
        System.out.println(ok);

        Person now=list.get(1);//操作索引值标是从0开始的
        System.out.println(now);

        Person del=list.remove(1);
        System.out.println(del);

        int size=list.size();//长度
        System.out.println(size);

        for (int i = 0; i < list.size(); i++) {//遍历
            System.out.println(list.get(i));
        }//快速写法：list.fori

        //!!!泛型只能是引用类型，不能是基本类型。
        //基本类型有对应的引用类型。
        //其中除了int->Integer和char->Character,其他都是首字母大写。
        ArrayList<Integer> Int=new ArrayList<>();
        Int.add(100);Int.add(100);
        System.out.println(Int);
    }
}

```

### 字符串String

字符串的底层实现其实是`byte[]`字节数组，是一个常量。

```java
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Java_try {

    public static void main(String[] args) {
        //初始化
        String str=new String();
        System.out.println(str);

        char [] chars={'a','b','c'};
        String str2=new String(chars);
        System.out.println(str2);

        byte [] bytes={12,23,12};
        String str3=new String(bytes);
        System.out.println(str3);

        String str4="hewllo";//直接写上双引号就是字符串对象。
        System.out.println(str4);
        
        
        
        //字符串常量池：程序当中直接写上双引号字符串，就在字符串常量池中。
        //对于基本类型来说：==是进行数值比较
        //对于引用类型来说：==是进行[地址值]比较
        String s1="hello";
        String s2="hello";
        char [] c2={'h','e','l','l','o'};
        String  s3=new String(c2);
        System.out.println(s1==s2);
        System.out.println(s1.equals(s2));
        System.out.println(s1==s3);
        System.out.println(s3.equals(s1));

        String s9=null;
//        System.out.println(s9.equals(s1));//会报错，出现空指针异常

        //equals的用法
        String b="ABC";
        String s="abc";
        System.out.println(b.equals(s));//false
        System.out.println(b.equalsIgnoreCase(s));//true，忽略了大小写，只有英文字母。

        int len=b.length();
        System.out.println("b的长度"+len);

        char ch=b.charAt(0);
        System.out.println(ch);
        String F="helloworld";
        int index=F.indexOf("llo");
        System.out.println(index);//索引从0开始

        String jq="123456789";
        System.out.println(jq.substring(3));//[3,+)
        System.out.println(jq.substring(2,3));//[2,3)

        String sa="hello";
        System.out.println(sa);
        sa="java";
        System.out.println(sa);//虽然sa的打印出来是变了的，但是是sa指向'hello"的地址变成了"java"

        String chs="hewllo";
        char [] cc=chs.toCharArray();
        System.out.println(cc[0]);

        byte [] by=chs.getBytes();
        for (int i = 0; i < by.length; i++) {
            System.out.println(by[i]);
        }

        String ss="How do you do?";
        String ss2=ss.replace('o','*');
        System.out.println(ss2);

        String x="你大爷的！";
        String  y=x.replace("你大爷的","*****");
        System.out.println(y);

        String abc="aaa,bbb,ccc";
        String [] arr=abc.split(",");
        //split的参数其实是一个正则表达式，要注意：如果按照英文句号切分，必须写"\\."
        for(int i=0;i<arr.length;i++){
            System.out.println(arr[i]);
        }
        abc="aaa.bbb.ccc";
        arr=abc.split("\\.");
        for(int i=0;i<arr.length;i++){
            System.out.println(arr[i]);
        }
        Scanner in=new Scanner(System.in);
        String S=in.next();
        char []CH=S.toCharArray();
        for (int i = 0; i < CH.length; i++) {
            System.out.println(CH[i]);
        }
    }
}

```

### static

**修饰变量**：只要成员变量用了static，这个变量就属于类的而不是对象的。

**修饰对象**：可以不创建对象使用方法（静态static），类名称使用。

**注意**：静态只能访问静态，不能直接访问非静态。因为在内存中先有静态的再有非静态的

​		静态方法不能使用`this`，因为`this`是由对象调用的，但是静态方法和类名称无关系，所以不能用`this`。

**静态代码块**：

```java
Class 类名{
	static 方法名{
    }
}
```

特点：当第一次访问静态方法时候，静态代码块执行唯一的一次。

用途：用来对静态变量进行一次性的赋值。

### Arrays

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Java_try {

    public static void main(String[] args) {
        int[] intArray={10,20,30};
        String insstr= Arrays.toString(intArray);
        System.out.println(insstr);
        int[]  array1={2,1,3,10,6};
        Arrays.sort(array1);//如果是字符串，默认按字母升序。
    }

}

```

### Math

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Java_try {

    public static void main(String[] args) {
        System.out.println(Math.abs(3.14));
        System.out.println(Math.abs(0));
        System.out.println(Math.abs(-2.5));
        System.out.println("==========");
        System.out.println(Math.ceil(3.9));//4.0
        System.out.println(Math.ceil(3.1));//4.0
        System.out.println(Math.ceil(3.0));//3.0
        System.out.println("===========");
        System.out.println(Math.floor(30.1));//30.0
        System.out.println(Math.floor(30.9));//30.0
        System.out.println(Math.floor(31.0));//31.0
        System.out.println("===========");
        System.out.println(Math.round(20.4));//20
        System.out.println(Math.round(10.5));//11
        System.out.println("===========");
        System.out.println(Math.PI);
    }

}

```

### 继承和抽象类

```java
public class 父类名称{
	///。。。
}
public class 子类名称 extends 父亲名称{
	///。。。
}
```

**继承中成员变量的访问特点**：

在父子类的继承关系中，如果成员变量重名，则创建子类对象时，访问有两种方法。

1、直接通过子类对象访问成员变量。

​	等号左边是谁，就优先用谁，没有就向上找。

2、间接通过成员方法访问成员变量。

​	该方法属于谁，就优先用谁，没有就向上找。

**super**：`super.变量名`表示父类的成员变量名。

**重写**：参数列表一样			**重载**：参数列表不一样

**Object**：是所有类的公共最高父类。

**权限**：子类方法的权限必须大于等于父类方法的权限修饰符。

**构造方法**： 生成子类对象的时候，先构造父类，再构造子类。

**super方法**：构造子类的时候在子类构造的第一个语句就是了。

**super和this两种构造调用**：不能同时使用，必须唯一。

**Java**是单继承
