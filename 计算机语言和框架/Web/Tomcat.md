- 安装目录不建议中文

- 安装：解压

- 卸载：删除

- 开启：bin/setup.bat

- 问题：
  - 黑窗口一闪而过
    
    - 没有配置JAVA_HOME路径
  - 端口被占用（重启了两次都没关）

    - 暴力：找到占用的端口号，找到对应的进程，杀死进程

    - 温柔：修改自身端口号

    - conf/server.xml

      一般会将tomcat的默认端口改为80，80端口号是http协议的默认端口号

      **好处**：访问时候不用输入端口号

- 关闭：ctrl+c或者（强制）直接关闭启动窗口

- 配置：

  1. 项目部署

     - 直接放到webapps目录下面

     - /hello：项目的访问路径
     - 简化部署：将项目打包为一个压缩包，再改后缀名为war。最后将war包放到webapps目录瞎，war会自动解压。

  2. 配置文件，就可以部署到别的目录上

     - server.xml文件中
     - ```<context docBase="D:\hello" path="/aaa"/>```
     - docBase：项目存放的路径
     - /aaa为虚拟目录，也就是broswer打开的路径

  3. 在conf\Catalina\localhost创建任意名称的xml文件，在文件中编写

     `<Context docBase="D:\hello"/>`

     - 虚拟目录：xml文件的名称

- 热部署：百度