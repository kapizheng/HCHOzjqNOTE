## 抽象

#### 抽象方法：

就是加上abstract关键字，然后去掉大括号，直接分号结束。

#### 抽象类：

抽象方法所在的类，必须是抽象类才行。在class之前协商abstract就可以。

不能直接用抽象类和抽象方法。

1、不能直接创建new抽象类对象。

2、必须使用一个子类来继承抽象父类。

3、子类必须覆盖重写父类当中所有的抽象方法。

**注意**：

1、抽象类不能创建对象。

2、抽象类中，可以有构造方法，提供子类创建对象时候，初始化父类对象用的。

3、抽象类中，不一定包含抽象方法。

4、抽象类的子类，必须重写抽象父类中所有的抽象方法。

## 接口

**接口是一种公共的规范标准**

**接口是多个类的公共规范**

**接口是一种引用数据类型**

```java
public interface 接口名称{
	//接口内容
}
//使用
public class 实现类名称 implements 接口名称{
}
```

#### 如果是Java7，那么接口中可以包含的内容有

**1、常量**

需要用`public static final`三个关键字修饰。



**2、抽象方法**

```java
public interface Interface {
    void get();
    void set();
    void hello();
}

```

```java
public class Implement implements Interface{
    @Override
    public void get(){
        System.out.println("em");
    }

    @Override
    public void set() {
        System.out.println("set");
    }

    @Override
    public void hello() {
        System.out.println("hello");
    }
}
```



```java
public class Java_try {

    public static void main(String[] args) {
        Implement now=new Implement();
        now.get();
        now.set();
        now.hello();
    }

}

```



#### 如果是Java8，那么接口额外包含有：

**3、默认方法**

可以通过接口实现类对象，直接调用。

可以被接口实现类进行覆盖重写。

**4、静态方法**

将default换成static就可以，改方法与实现类有关，与对象无关。

不能用接口实现类的对象来调用接口当中的静态方法。

直接通过接口名称调用。

#### 如果是Java9，那么可以额外包含：

**5、私有方法**

需要抽取一个公共方法，用来解决两个默认方法之间重复代码的问题。

但是这个共有方法不应该让实现类使用，应该是私有的。

```Java
//普通私有方法
private 返回值类型 方法名称(参数列表){
	方法体
}
//静态私有方法
private static 返回值类型 方法名称(参数列表){
	方法体
}

```

#### **注意事项**：

1、继承多个接口的时候用","分开，就可以遇到重名的方法只写一个就可以了。

2、如果实现类实现的多个接口中有默认方法，一定要对默认方法进行覆盖重写。

3、一个类如果直接父类中的方法和接口中的默认方法名字冲突，优先用父类的方法。

**接口中是多继承的，类是单继承的。**

多个父接口中的抽象方法如果重复，没关系。

多个父接口中的默认方法如果重复，有关系，需要重写。

### 多态

```java
父类名称 对象名 = 子类名称();
接口名称 对象名 = new 实现类名称();
```

访问成员变量的两种方式

1、直接通过对象名称访问成员变量，看等号左边是谁，找不到向上找。

2、间接通过成员方法访问，该方法属于谁优先用谁，没有则向上找。子类没有覆盖重写就找父类的。

访问成员方法的两种方式

**看new是谁，就优先用谁，没有则向上找。**

> 口诀：
>
> 成员变量，编译看左边，运行看左边。
>
> 成员方法，编译看左边，运行看右边。

#### 向上转型：

一旦向上转型为父类，就无法调用子类原本特有的方法。

解决方案：用对象的向下转型还原，将父类对象，（还原）为本来的子类对象。

```java
子类名称 对象名=(子类名称)父类对象;
```

注意事项：还原的不是本来的类型就会报错。

#### Instanceof

```jav
对象 instanceof 类名称
这将会得到一个Boolean值结尾，也就是判断前面的对象能不能当后面类的实例。适用于向下类型转换的时候。
```

#### final

> 修饰一个类，修饰一个方法，修饰一个局部变量，修饰一个成员变量。

**修饰一个类：**当前这个类不能有任何子类。（太监类），其所以的儿子不能被覆盖重写。

**修饰一个方法**：这个方法就是最终方法，不能被覆盖重写，对于一个类的方法来说，abstract和final方法不能一起使用，矛盾。

**修饰一个变量**：一旦使用final来修饰局部变量，这个变量就不能修改。

> 对基本类型来说，不可变是指数据不可变。
>
> 对引用类型来说，不可变是指地址不可变。

**修饰一个成员变量**：这个变量不可变，但是因为成员变量有默认值，引用后必须进行手动赋值。要么直接赋值，要么构造赋值。

#### 四种权限修饰符

|         类型         | public | protected | (default) | private |
| :------------------: | :----: | :-------: | :-------: | :-----: |
|     同类(我自己)     |  YES   |    YES    |    YES    |   YES   |
|     同包(我邻居)     |  YES   |    YES    |    YES    |   NO    |
|  不同包子类(我儿子)  |  YES   |    YES    |    NO     |   NO    |
| 不同包非子类(陌生人) |  YES   |    NO     |    NO     |   NO    |

#### 内部类

1、成员内部类

2、局部内部类（包含匿名内部类）

成员内部类的定义格式：

```java
修饰符 class 外部类名称{
    修饰符 class 内部类名称{
        
    }
}
注意：内用外，随意访问，外用内需要用内部对象
```

如何使用内部成员类？有两种方式

1、间接方式：在外部类的方法当中，使用内部类。

2、直接方式：公式。

```java
类名称.内部类名称 对象名 = new 外部类名称().new 内部类名称()
```

```java
package j2;

public class C {
    public  class B{
        int a;
        public void show()
        {
            System.out.println("hahah");
        }
    }
    public void showB(){
        new B().show();
    }
    String name;
    public String getName(){
        return name;
    }
}
package j2;

public class M {
    public static void main(String[] args) {
        C c=new C();
        c.name="123";
        System.out.println(c.name);
        System.out.println(c.getName());
        c.showB();
        C.B b=new C().new B();
        b.show();
    }
}

```

如果出现了内部类命名与外部类一样，如下

```java
package j2;

public class C {
    int a=10;
    public  class B{
        int a=20;
        public void show()
        {
            System.out.println(a);
            System.out.println(this.a);
            System.out.println(C.this.a);
        }
    }
}
package j2;

public class M {
    public static void main(String[] args) {

        C.B now=new C().new B();
        now.show();
    }
}
```

> 如果一个类是定义在一个方法内部的，那么这就是一个局部内部类。"局部"，只有当前所属的方法才能使用它，出了这个方法外面就不能用了。

```java
修饰符 class 外部类名称{
	修饰符返回值类型 外部类方法名称(参数列表){
		class 局部内部类名称{
        
        }
	}
}
package j2;
/*
* 1、外部类：public/(default)
* 2、成员内部类：public/protected/(default)/private
* 3、局部内部类：什么都不能写
* 4、局部内部类，如果希望访问所在方法的局部变量，那么这个局部变量必须是[有效final的]
* 从Java8开始，只要局部变量事实补变，那么final关键字可以省略。
* */
public class C {
    public void c()
    {
        class Inner {
            int num=10;
            public void inner() {
                System.out.println(num);
            }
        }
        Inner in=new Inner();
        in.inner();
    }
}
package j2;

public class M {
    public static void main(String[] args) {
        C c=new C();
        c.c();
    }
}


```

#### 匿名内部类

```java
package j2;

public interface Int {
    void method();
}
package j2;

public class IntChi implements Int{
    @Override
    public void  method(){
        System.out.println("emmm");
    }

}
package j2;
//如果接口的实现类（或者是父类的子类）只需要使用唯一的一次。
//这种情况可以省略掉类的定义，而改为使用[匿名内部类]
public class M {
    public static void main(String[] args) {
        Int now=new IntChi();
        now.method();

        Int obj=new Int(){
            @Override
            public void method(){
                System.out.println("em23m");
            }
        };
        obj.method();

    }
}
```

**注意事项**：

1、匿名内部类，在创建对象的时候，只能使用唯一的一次，如果多次创建对象，且实现内容一样，那么必须再单独定义一次。

2、匿名对象，在[调用方法]的时候，只能调用唯一的一次。如果希望同一个对象，调用多次方法，那么必须给对象起一个名字。

3、匿名内部类是省略了[实现类/子类名称]，但是匿名对象是省略了[对象名称]

**强调**：匿名内部类和匿名对象不是一回事！！！
