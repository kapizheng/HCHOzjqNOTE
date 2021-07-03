## Collection

### 1、常用功能

```java
package toy;

import java.util.ArrayList;
import java.util.Collection;

/*
Collection接口，里面定义了所有单列集合共性的方法
任意的单列集合都可以使用Collection接口中的方法

* */
public class ttt {
    public static void main(String[] args){
        Collection<String> Cs=new ArrayList<>();

        System.out.println(Cs);
        //add
        Cs.add("123");
        System.out.println(Cs);
        Cs.add("231");
        //remove
        Cs.remove("123");
        System.out.println(Cs);
        //contains
        System.out.println(Cs.contains("231"));
        //isempty
        boolean ok=Cs.isEmpty();
        System.out.println(ok);
        Cs.clear();
        ok=Cs.isEmpty();
        System.out.println(ok);
        System.out.println(Cs);
    }
}
```

### 2、iterator迭代器

```java
package toy;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

/*
Collection接口，里面定义了所有单列集合共性的方法
任意的单列集合都可以使用Collection接口中的方法

* */
public class ttt {
    public static void main(String[] args){
        Collection<String> col1 = new ArrayList<>();
        col1.add("em");
        col1.add("emm");
        col1.add("afds");
        Iterator<String> it = col1.iterator();
        //iterator获得指向集合的-1索引

        while(it.hasNext()){
            System.out.println(it.next());
        }

        for(it= col1.iterator();it.hasNext();){
            System.out.println(it.next());
        }
//        boolean I=it.hasNext();
//        System.out.println(I);
//        String str=it.next();
//        System.out.println(str);
//        str=it.next();
//        System.out.println(str);
//        str=it.next();
//        System.out.println(str);

        //增强for循环，其目标只能是集合或者数组
        for(String now:col1){
            System.out.println(now);
        }

    }
}
```

### 3、泛型

泛型类：

```java
package j2;
//如果接口的实现类（或者是父类的子类）只需要使用唯一的一次。
//这种情况可以省略掉类的定义，而改为使用[匿名内部类]
public class M<E> {
    private E str;

    public E getStr() {
        return str;
    }

    public void setStr(E str) {
        this.str = str;
    }
}
```

泛型方法：

```java
package j2;

public class M {

    public <z> void show(z m){
        System.out.println(m);
    }
    public static <e> void showw(e E){
        System.out.println(E);
    }//静态方法名
}
package toy;
import j2.M;

public class ttt {
    public static void main(String[] args){
        M m=new M();
        m.show(123);
        M.showw("fasdf");
    }
}
```

含有泛型的接口

```java
package j2;

public interface M<m>{
    void show(m z);
}
package j2;

public class ImplM implements M<String>{

    @Override
    public void show(String s) {
        System.out.println(23);
    }
} 
package toy;
import j2.ImplM;
import j2.M;

public class ttt {
    public static void main(String[] args){
        M m=new ImplM();
        m.show("123");
    }
}
```

类定义由于实现对象时来决定：

```java
package j2;

public interface M<m>{
    void show(m z);
}
package j2;

public class ImplM<E> implements M<E>{

    @Override
    public void show(E s) {
        System.out.println(23);
    }
}
package toy;
import j2.ImplM;
import j2.M;

public class ttt {
    public static void main(String[] args){
       M<String> ms=new ImplM<>();
       ms.show("123");
    }
}


```

泛型通配符

```java
package toy;
import j2.ImplM;
import j2.M;

import java.util.ArrayList;
import java.util.Iterator;

public class ttt {
    public static void main(String[] args){
       ArrayList<String> list1 =new ArrayList<>();
       ArrayList<Integer> list2 = new ArrayList<>();
       list1.add("adsfads");
       list1.add("adfsa");
       list1.add("adsf");
       list2.add(123);
       list2.add(123);
       list2.add(2342);
       print(list1);
       print(list2);
    }
    
    public static void print(ArrayList<?> list){
        Iterator<?> it = list.iterator();
        while(it.hasNext()){
            System.out.println(it.next());
        }
    }
}
```

### 4、List

- 有序的（存储和取出元素的顺序有序），有索引的
- 允许存储重复元素

```java
package toy;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ttt {
    public static void main(String[] args){
        List<Integer> list = new ArrayList<>();
        list.add(123);
        list.add(234);
        System.out.println(list);

        list.add(1,23132);
        System.out.println(list);

        Integer remove = list.remove(2);
        System.out.println(remove);

        Integer set = list.set(1, 12311);
        System.out.println(set);

        for(int i=0;i<list.size();i++){
            Integer now=list.get(i);
            System.out.println(now);
        }

        Iterator<Integer> it=list.iterator();
        while (it.hasNext()){
            System.out.println(it.next());
        }
        for (Integer integer : list) {
            System.out.println(integer);
        }
    }
}
```

**ArrayList**：不同步，多线程，数组实现。查询快，增删慢。

**LinkedList**：底层是链表结构，查询慢，增删快。

```java
package toy;
import j2.Int;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class ttt {
    public static void main(String[] args){
        LinkedList<Integer> list = new LinkedList<>();
        list.addFirst(123);
        list.addFirst(234);
        list.addLast(2342);
        System.out.println(list);

        Integer a=list.getFirst();
        System.out.println(a);
        Integer b=list.getLast();
        System.out.println(b);

        Integer integer = list.removeFirst();
        System.out.println(integer);
        integer = list.removeLast();
        System.out.println(integer);
    }
}
```

**vector**：可边长的对象数组，同步单线程。可以索引操作

### 5、HashSet

无序序列，不允许有重复的元素，没有索引，底层是哈希表结构，查询速度非常快。

**哈希值**：是一个十进制的整数，由系统随机给出（就是对象的地址，是一个逻辑地址，而不是实际存在的地址）

其源码：`hashcode`方法的源码，native代表该方法调用的是本地操作系统的方法。

Set集合在调用add方法的时候，add方法会调用元素的hashCode方法和equals方法判断元素是否重复。

用在自定义类型元素中要重写hashCode方法和equals方法。

```java
package toy;
import java.util.*;

public class ttt {
    public static void main(String[] args){
        HashSet<String> set = new HashSet<>();
        String s1=new String("abc");
        String s2=new String("abc");

        set.add(s1);
        set.add(s2);
        set.add("重地");
        set.add("通话");
        set.add("abc");
        System.out.println(set);
    }
}
```

**LinkedHashSet**集合

底层是一个哈希表(数组+链表/红黑树)+链表，多了一条链表,保证元素有序，不允许重复。

### 6、可变参数

底层是数组，传递参数个数，可以是0个，1个，2个。

```java
package toy;
import java.util.*;

public class ttt {
    static void show(int ...ar){
        for (int i = 0; i < ar.length; i++) {
            System.out.println(ar[i]);
        }
    }
    public static void main(String[] args){
        show(1,2,4,5);
    }
}
```

- 一个方法的参数列表，只能有一个可变参数

- 如果方法的参数有多个，那么可变参数必须卸载参数列表前面。

### 7、Collections工具类

**.sort()**排序的集合里面存储的元素，必须实现Comparable，重写接口中的方法compareTo定义排序的规则.

**CompareTo接口的排序规则:自己(this)-参数:升序**

- comparable:自己和别人比较,自己要实现comparable接口,重写比较compareTo方法
- comparator相当于多一个裁判.

**sort(集合,comparator)**,可以用匿名内部类

### 8、map集合

jdk1.8前：数组+单向链表

jdk1.8之后：数组+单向链表+红黑树

**LinkedHashMap集合底层是哈希表+链表（保证迭代的顺序）LinkedHashMap集合是一个有序的集合，存储元素和取出元素的顺序是一致的**。

```java
package toy;
        import java.util.*;

public class ttt {
    public static void main(String[] args) {
        //方法put的返回值
        //存储键值对的时候，key不重复，返回值是null
        //存储键值对的时候，key重复，会使用新的value替换map中重复的值，并返回被替换的值
        Map<String, String> mp = new HashMap<>();
        String v1 = mp.put("昵称", "fbb");
        String v2 = mp.put("nq", "fbb");
        System.out.println(v1 + " " + v2);
        mp.put("冷风", "lilili");
        System.out.println(mp);

        //key存在就返回删除的值
        //key不存在就返回null
        String 昵称 = mp.remove("昵称");
        System.out.println(昵称);
        昵称 = mp.remove("昵称");
        System.out.println(昵称);

        //key存在就返回对应的值
        //key不存在就返回null    }
        昵称 = mp.get("昵称");
        System.out.println(昵称);
        昵称 = mp.get("nq");
        System.out.println(昵称);

        boolean yes=mp.containsKey("昵称");
        System.out.println(yes);
        yes=mp.containsKey("nq");
        System.out.println(yes);
    }
}
```

### 9、Entry对象（键值对对象）

```java

        Set<Map.Entry<String,String>> set=mp.entrySet();
        Iterator<Map.Entry<String, String>> iterator = set.iterator();
        while (iterator.hasNext()){
            String a=iterator.next().getKey();
            String b=iterator.next().getValue();
            System.out.println(a+"="+b);
        }
        for (Map.Entry<String, String> tt : set) {
            System.out.println(tt.getKey()+"="+tt.getValue());
        }
```

**HashMap中要用自定义类型键值必须重写HashCode方法和equals方法**

### 10、LinkedHashMap

不重复，有序

```java
package toy;
import java.util.*;

public class ttt {
    public static void main(String[] args) {
        //方法put的返回值
        //存储键值对的时候，key不重复，返回值是null
        //存储键值对的时候，key重复，会使用新的value替换map中重复的值，并返回被替换的值
        Map<String, String> mp = new HashMap<>();
        String v1 = mp.put("昵称", "fbb");
        String v2 = mp.put("nq", "fbb");
        mp.put("冷风", "lilili");
        mp.put("冷风", "lilili");
        System.out.println(mp);

        LinkedHashMap<String,String> mpp= new LinkedHashMap<>();
        mpp.put("昵称", "fbb");
        mpp.put("nq", "fbb");
        mpp.put("冷风", "lilili");
        mpp.put("冷风", "lilili");
        System.out.println(mpp);

    }
}
```

### 11、HashTable

**HashMap可以存null，而HashTable不可以存null键**

Properties集合是一个唯一和IO流相结合的集合。

### 12、调试程序

![image-20201004203137673](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20201004203137673.png)