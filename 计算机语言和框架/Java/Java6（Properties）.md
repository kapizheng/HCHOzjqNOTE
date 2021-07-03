### Properties的基本使用

```java
package Lambda;
import java.io.IOException;
import java.util.Properties;
import java.util.Set;

public class Demo01{
    public static void main(String[] args) throws IOException {
        Properties prop = new Properties();
        prop.setProperty("123","123");
        prop.setProperty("12","123132");
        Set<String> set = prop.stringPropertyNames();
        for (String s : set) {
            System.out.println(prop.getProperty(s));
        }
    }
}
```

**写入到文件里**

```java
package Lambda;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;
import java.util.Set;
public class Demo01{
    public static void main(String[] args) throws IOException {
        Properties prop = new Properties();
        prop.setProperty("5156","123");
        prop.setProperty("12","123132");
        Set<String> set = prop.stringPropertyNames();
        for (String s : set) {
            System.out.println(prop.getProperty(s));
        }
        prop.store(new FileWriter("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\pro2.txt"),"save data");

    }
}
```

**从文件中读取**

```java
package Lambda;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;
import java.util.Set;
public class Demo01{
    public static void main(String[] args) throws IOException {
        Properties prop = new Properties();
        FileReader fileReader = new FileReader("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda\\pro.txt");

        prop.load(fileReader);
        Set<String> se = prop.stringPropertyNames();
        for (String s : se) {
            System.out.println(s+"="+prop.getProperty(s));
        }
    }
}
```

### BufferedOutputStream

```java
package Lambda;
import java.io.*;
import java.util.Properties;
import java.util.Set;
public class Demo01{
    public static void main(String[] args) throws IOException {
        FileOutputStream fos=new FileOutputStream("C:\\Users\\zjq\\IdeaProjects\\Java_try\\src\\Lambda");
        BufferedOutputStream bos= new BufferedOutputStream(fos);
        bos.write("123123".getBytes());
        bos.flush();
        bos.close();
        fos.close();
    }
}
```

**格式转换**

![image-20201008191828706](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20201008191828706.png)