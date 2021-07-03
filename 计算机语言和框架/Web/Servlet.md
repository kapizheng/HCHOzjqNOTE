####  server applet

​	运行在服务器上的小程序

- servlet实现类

- web.xml

```java
<servlet>
        <servlet-name>demo</servlet-name>
        <servlet-class>cn.itcast.web.servlet.servlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>demo</servlet-name>
        <url-pattern>/pp</url-pattern>
    </servlet-mapping>
```

servlet是单例的，多个用户访问有进程安全问题

```java
package cn.itcast.web.servlet;

import javax.servlet.*;
import java.io.IOException;

public class servlet implements Servlet {
    //在servlet被创建的时候执行
    @Override
    public void init(ServletConfig servletConfig) throws ServletException {
        System.out.println("sout");
    }

    @Override
    public ServletConfig getServletConfig() {
        return null;
    }
    //在servletc每一次被访问的时候执行
    @Override
    public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
        System.out.println("hehe");
    }

    @Override
    public String getServletInfo() {
        return null;
    }
    //在服务器正常关闭的时候执行
    @Override
    public void destroy() {
        System.out.println("soutend");
    }
}
```

- servlet3.0：
  - 支持注解配置，可以不需要web.xml了。
  - 定义一个类实现servlet接口

### 3.0

```java
package cn.itcast.web.servlet;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import java.io.IOException;

@WebServlet(urlPatterns = "/heh")
public class servlet implements Servlet {
    //在servlet被创建的时候执行
    @Override
    public void init(ServletConfig servletConfig) throws ServletException {
        System.out.println("sout");
    }

    @Override
    public ServletConfig getServletConfig() {
        return null;
    }
    //在servletc每一次被访问的时候执行
    @Override
    public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
        System.out.println("hehe");
    }

    @Override
    public String getServletInfo() {
        return null;
    }
    //在服务器正常关闭的时候执行
    @Override
    public void destroy() {
        System.out.println("soutend");
    }
}
```

