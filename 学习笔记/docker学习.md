### docker学习

镜像：对一个系统的一个打包。

容器：将镜像运行起来的一个程序。



- 查找镜像

`docker search centos`

- 拉取镜像

`docker pull centos`

- 查看镜像

`docker images`

- 用镜像启动一个容器后进行修改

`docker run -it centos:latest /bin/bash`

-i：表示打开并保持stdout

-t：表示分配一个终端。

运行后采用exit是容器状态为exit，而不是后台运行。要想让容器一直运行，可以用快捷键Ctrl+p Ctrl+q退出，此时容器状态为Up。

-d：后台运行。

- 退出容器

`exit`

- 查看docker中运行的容器

`docker ps -a`

- 将容器变为镜像

`docker commit -m "centos with git"-a "qixianhu" $id$ xianhu/centos:git`

`xianhu;/centos:git`指定目标镜像的用户名，仓库名和tag信息。

- 运行有git的镜像

`docker run -it xianhu/centos:git /bin/bash`

- 启动，停止，重启容器命令

```
[root@xxx ~]# docker start container_name/container_id
[root@xxx ~]# docker stop container_name/container_id
[root@xxx ~]# docker restart container_name/container_id
```

- 后台启动一个容器后，如果想进入到这个容器，可以使用attach命令：

```text
[root@xxx ~]# docker attach container_name/container_id
```

- 删除容器的命令前边已经提到过了：

```text
[root@xxx ~]# docker rm container_name/container_id
```

### Dockerfile是用来创建镜像的

：感觉这个内容不太需要学，一般没怎么用到，因为现在都是用的公司项目写，所以跳过

### Docker中的仓库

- Docker维护了一个DockerHub的公共仓库，里面有很多镜像。除了下载，我们还能push
- 如何push到DockerHub的知识就跳过不学了。





### docker的一些tips：

- docker可以运行在linux的Windows中，分别叫做Linuxdocker和Windowdocker，使用一些命令可以进行切换。在Windows中使用linuxdocker需要开启bios的硬件虚拟化。
- lastest标签的镜像不保证这是仓库中最新的镜像。