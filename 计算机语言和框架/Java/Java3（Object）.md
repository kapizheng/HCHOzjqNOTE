## Object类

> 是Java语言的根类。

#### toString方法

直接打印对象的名字，其实就是调用对象的toString方法p=p.toString();

**重写**

需要重写Object类的toString方法，可以Alt+Enter

重写equals方法

## 日期时间类

### 2.1Date类

```java
Date d2 = new Date(10000000);
//把毫秒转换为时间。
Daate date = new Date();
long time = date.getTime();
//把当前时间转换为毫秒
```

### 2.2DateFormat类

> 抽象类，时间格式化的子类

```java
构造方法：
    SimpleDateFormat(String pattern)
    用给定的模式和默认语言环境的日期格式符号构造
    参数：
    	String pattern:传递指定的格式
    模式：区分大小写的
         Y	年
         M  月
         d	日
         H	时
         m  分
         s	秒
      写对应的模式，会把模式替换为对应的日期和时间。
            "yyyy-mm-dd HH:mm:ss"
            "yyyy年mm月dd日 HH时mm分ss秒"
            
对象名.format();//把内容格式
对象名.parse();//把内容解析
```

```java
package toy;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.SimpleTimeZone;

public class ttt {
    public static void main(String[] args) throws ParseException {
        SimpleDateFormat now = new SimpleDateFormat("yyyy年MM月dd日 HH时mm分ss秒");

        Date date = new Date();
        String text = now.format(date);
        System.out.println(date);
        System.out.println(text);

        Date dd=now.parse("2008年08月08日 17时01分10秒");//声明了一个解析异常，如果字符串和构造方法中不一样，就会抛出
        System.out.println(dd);
    }
}

```

### Calendar

> 抽象类

```java
package toy;


import java.util.Calendar;
import java.util.Date;

public class ttt {
    public static void main(String[] args){
        Calendar ca=Calendar.getInstance();
        ca.set(Calendar.YEAR,9999);
        ca.set(Calendar.MONTH,10);
        ca.set(Calendar.DAY_OF_MONTH,10);
        ca.set(999,9,9);

        int year=ca.get(Calendar.YEAR);
        System.out.println(year);
        int mouth=ca.get(Calendar.MONTH)+1;
        System.out.println(mouth);
        int day=ca.get(Calendar.DAY_OF_MONTH);
        System.out.println(day);

        ca.add(Calendar.YEAR,2);
        System.out.println(Calendar.YEAR);

        //把日历转换成日期
        Calendar C=Calendar.getInstance();
        Date dd=C.getTime();
        System.out.println(dd);
    }
}

```

![image-20200928221813189](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20200928221813189.png)

###  System类

```java
package toy;


import java.util.Arrays;
public class ttt {
    public static void main(String[] args){
        System.out.println(System.currentTimeMillis());//获得当前毫秒数
        int[]src = {1,2,3,4,5};
        int[] dest={6,7,8,9,10};
        System.out.println("复制前："+Arrays.toString(dest));
        System.arraycopy(src,0,dest,0,3);
        System.out.println("复制后"+Arrays.toString(dest));
    }
}
```

### StringBuilder

是字符串缓冲区，可以提高字符串的操作效率（看成一个长度可以变化的字符串）。底层也是一个数组，但是没有被final修饰，可以改变长度。

**链式编程**，只要返回的是对象，就可以继续.方法名()

```java
package toy;


        import java.util.Arrays;
public class ttt {
    public static void main(String[] args){
       StringBuilder bu1 = new StringBuilder();
        System.out.println("bu1"+bu1);
        StringBuilder bu3 = new StringBuilder("abs");
        StringBuilder bu2 = bu1.append("aaa");//append的返回值是它本身。
        System.out.println("bu2"+bu2);
        System.out.println(bu1==bu2);
        //StringBuilder和String可以相互转换
        String str="hello";
        System.out.println("Str:"+str);
        StringBuilder bu = new StringBuilder(str);
        bu.append("23");
        System.out.println("bu:"+bu);
    }
}
```

### 包装类

**装箱**：从基本类型转换为对应的包装类对象。

**拆箱**：从基本类型转换为对应的基本类型。

```java
Integer i = new Integer(4);
Integer iii = Integer.valueOf(4);
Integer in=1;
//自动拆箱
//in=in+2;相当于in.inValue()+3=2;
//in=in+2;就相当于in=new Integer(3)
```

> ArrayList<Integer> List = new ArrayList<>();
>
> list.add(1);
>
> int a=list.get(0);

ArrayList无法直接存储整数，可以存储Integer包装类