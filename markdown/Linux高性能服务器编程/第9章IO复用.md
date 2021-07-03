### select系统调用

- 在一段指定时间内，监听用户感兴趣的文件描述符上的可读，可写和异常事件。

`int select(int nfds,fd_set* readfds,fd_set* writefds,fd_set* exceptfds,struct timeval*timeout);`

- nfds表示监听的文件描述符总数
- readfds、writefds和exceptfds分别指向可读，可写和异常事件对应的文件描述符集合。
- timeout设置select函数的超时时间。

### poll系统调用

- poll系统调用和select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否用就绪者。

`int poll(struct pollfd* fds,nfds_t nfds,int timeout)`

- fds参数是一个pollfd结构类型的数组，它指定所有我们感兴趣的文件描述符上发生的可读、可写和异常事件。

```c++
struct pollfd
{
	int fd;//文件描述符
	short events;//注册的事件
	short revents;//实际发生的事件
}
```

- fd成员指定文件描述符，events成员告诉poll监听fd上的哪些事件，它是一系列安位或，revents成员则由内核修改，同志应用程序fd上实际发生了哪些事件。
- nfds参数指定被监听事件集合fds的大小。
- timeout参数指定poll的超时值，单位是毫秒。

### epoll系列系统调用

### epoll

- epoll是linux特有的I/O复用函数。它在实现和使用上与select、poll与很大差异。首先epoll使用一组函数来完成任务，而不是单个函数。其次，epoll把用户关心的文件描述符上的事件放在内核里的一个事件表中。从而无需像select和poll那样每次调用都需要重复传入文件描述符集或事件集。但epoll需要使用一个额外的文件描述符，来唯一表示内核中的事件表。

`int epoll_create(int size)`

- size只是给内核一个提示，告诉它事件表需要多大，该函数返回的文件描述符作用其他所有epoll系统调用的第一个参数，以指定要访问的内核事件表。

- 下面函数用来操作epoll的内核事件表

`int epoll_ctl(int epfd,int op,iint fd,struct epoll_event* event);`

- fd参数是要操作的文件描述符，op参数则指定操作类型，增改删。

- event参数指定事件，它是epoll_event结构指针类型。epoll_event的定义如下：

  ```c++
  struct epoll_event{
  	_uint32_t events;//epoll事件
  	epoll_data_t data;//用户数据
  }
  ```

#### epoll_wait

- 在一段超时时间内等待一组文件描述符的事件，其原型如下：

`int epoll_wait(int epfd,struct epoll_event*events,int maxevents,int timeout);`

该函数成功时返回就绪的文件描述符的个数，失败时返回-1并设置errno。

- maxevents参数指定最多监听多少个事件，要大于0。
- epoll_wait函数如果检测到事件，就将所有就绪的事件从内核事件表中赋值到它的第二个参数events指向的数组中。这个数组只用于输出epoll_wait检测到的就绪事件，而不像select和poll的数组参数那样即用与用户注册的事件，又用于输出内核检测到的就绪事件。这就极大地提高了应用程序索引就绪文件描述符的效率。

#### LT和ET（文件描述符的操作模式）

- LT电平触发（默认），这种模式下epoll相对于一个效率较高的poll。当epoll_wait检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理该事件。等下次调用epoll_wait的时候会再次向应用程序通告该事件。
- ET边沿触发，当epoll_wait检测到其上有事件发生并将此事件通知应用程序1后，应用程序必须立即处理该事件，因为后续的epoll_wait调用将不再向应用程序通知这事件。
- ET模式很大程度上降低了同一个epoll事件被重复触发的次数，效率比LT高。

### 三组I/O复用函数的比较

- select没有将文件描述符和事件绑定。 只能处理可读，可写以及异常事件。每次需要重置。
- poll中，把文件描述符和事件定义在其中，任何事件都被统一处理，从而使得编程接口简洁许多。并且每次内核修改的是pollfd结构体的revents成员，而events成员保持不变，因此下次调用poll时应用程序无需重置pollfd的结构体。

- 由于select和poll每次调用都返回整个用户注册的事件集合，所以应用程序索引就绪文件描述符的时间复制度为O(n)。
- epoll则采用与select和poll完全不同的方式来管理用户注册的事件。它在内核维护一个事件表，每次提供了一个独立的系统调用epoll_ctl来控制住其中添加、删除、修改事件。这样每次epollwait调用都直接从该内核事件表中获取用户注册的事件，而无需反复从用户空间读入这些事件。epoll_wait系统调用的events参数只用来返回就绪的事件，使得应用程序索引就绪文件描述符复杂度到O(1)
- poll和epoll_wait分别用nfds和maxevents参数指定最多监听多少个文件描述符和事件。允许最大文件描述符为，65535。虽然用户可修改这个限制，但可能会导致不可预知的后果。

- select和poll都只能工作在相对低效的LT模式，而epoll则可工作在ET高效模式。并且epoll还支持EPOLLONESHOT事件，该事件可进一步减少可读，可写和异常事件被触发次数。
- 从实现原理上来说：select和poll采用是轮询的方式。而epoll_wait不同，采用的是回调方式，内核检测到就绪的文件描述符时，就触发回调函数，回调函数将文件描述符上对应的事件插入内核就绪事件队列。
- 当活动连接比较多的时候，epoll_wait的效率未必比select和poll高，因为此时回调函数被触发过于频繁。所以epoll适合用于连接数比较多，但活动比较少的情况。

### 第一个Project

```c++
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1023

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
}

int unblock_connect(const char *ip, int port, int time)
{
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    //将文件描述符设置为不阻塞。
    int fdopt = setnonblocking(sockfd);

    ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (ret == 0)
    {
        //如果连接成功，恢复sockfd属性，并立即返回
        printf("connect with server immediately\n");
        fcntl(sockfd, F_SETFL, fdopt);
        return sockfd;
    }
    else if (errno != EINPROGRESS)
    {
        //如果没有立即建立，那么只有当erron是EINPROGRESS才表示连接还在进行。
        printf("unblock connect not support\n");
        return -1;
    }
    fd_set readfds;
    fd_set writefds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &writefds);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(sockfd + 1, NULL, &writefds, NULL, &timeout);
    if (ret <= 0)
    {
        // select超时或出错，立即返回
        printf("connection time out\n");
        close(sockfd);
        return -1;
    }
    if (!FD_ISSET(sockfd, &writefds))
    {
        printf("no events on sockfd found\n");
        close(sockfd);
        return -1;
    }
    int error = 0;
    socklen_t length = sizeof(error);
    //调用getsockopt来获取并清除sockfd上的错误
    if (getsockopt(sockfd, SOL_SOCKET,SO_ERROR,&error,&length)<0)
    {
        printf("get socket optrion failed\n");
        close(sockfd);
        return -1;
    }
    if (error != 0)
    {
        printf("connection failed after select with the error:%d\n", error);
        return -1;
    }
    printf("connection read after select with the socket: %d\n", sockfd);
}

int main()
{
    const char*ip = "172.0.0.1";
    int port = atoi("8088");
    int sockfd = unblock_connect(ip,port,10);
    if(sockfd<0){
        return 1;
    }

    close(sockfd);
    return 0;
}
```

### 第二个项目

```c++
#define _GUN_SOURCE 1
//使用到了POLLRDHUP事件，就需要先定义_GUN_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 64

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("参数太少");
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    // server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("connection failed\n");
        close(sockfd);
        return 1;
    }
    struct pollfd fds[2]; //注册文件描述符0和文件描述符sockfd上的可读事件
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;

    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe(pipefd);
    assert(ret!=-1);
    while(1){
        ret = poll(fds,2,-1);
        if(ret<0){
            printf("poll failure\n");
            break;
        }
        if(fds[1].revents&POLLRDHUP){
            printf("server close the connection\n");
            break;
        }else if(fds[1].revents&POLLIN){
            memset(read_buf,'\0',BUFFER_SIZE);
            recv(fds[1].fd,read_buf,BUFFER_SIZE-1,0);
            printf("%s\n",read_buf);
        }
        if(fds[0].revents&POLLIN){
            ret = splice(0,NULL,pipefd[1],NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
            ret = splice(pipefd[0],NULL,sockfd,NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
        }
    }
    close(sockfd);
}

```

```c++
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define USER_LIMIT 5   //最大用户数量
#define BUFFER_SIZE 64 //读取缓冲区大小
#define FD_LIMIT 65535

struct client_data
{
    sockaddr_in address;
    char *write_buf;
    char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("参数太少");
        return 1;
    }
    //设置服务器ip地址等东西
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;

    bzero(&address, sizeof(address));
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    
    int ret=0;
    //将socket和IP地址绑定
    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    
    assert(ret != -1);

    //设置最大可监听数，也就是5个客户端
    ret = listen(listenfd, 5);
    assert(ret != -1);
    //创建users数组

    client_data *users = new client_data[FD_LIMIT];
    pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for (int i = 1; i <= USER_LIMIT; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    //将文件描述符0设置为服务器socket
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;
    //轮询
    
    while (1)
    {
        //注册事件。
        ret = poll(fds, user_counter + 1, -1);
        if (ret < 0)
        {
            printf("poll failure\n");
            break;
        }
        for (int i = 0; i < user_counter + 1; ++i)
        {
            if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN)) //为服务端，且事件为可读
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                //阻塞读取
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
                if (connfd < 0)
                {
                    printf("error is:%d\n", errno);
                    continue;
                }
                //用户数太多了
                if (user_counter >= USER_LIMIT)
                {
                    const char *info = "too many users\n";
                    printf("%s", info);
                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }
                // 不然就将用户给设置一下
                user_counter++;
                //存放一下socket
                users[connfd].address = client_address;
                //不阻塞connect
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                //要设置可接受事件，和初始化输出事件
                //可读，可关闭，错误
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                printf("comes a new user,now have %d users\n", user_counter);
            }
            else if (fds[i].revents & POLLERR)
            {
                printf("get an error from %d\n", fds[i].fd);
                char errors[100];
                memset(errors, '\0', 100);
                socklen_t length = sizeof(errors);
                if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0)
                {
                    printf("get socket option failed\n");
                }
                continue;
            }
            else if (fds[i].revents & POLLRDHUP)
            {
                //如果用户关闭连接，则服务器也关闭对应的连接，并将其用户总数减1
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                printf("a client left\n");
            }
            else if (fds[i].revents & POLLIN)
            {
                int connfd = fds[i].fd;
                memset(users[connfd].buf, '\0', BUFFER_SIZE);
                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE - 1, 0);
                printf("get %d bytes of client data %s from %d\n", ret, users[connfd].buf, connfd);
                if (ret < 0)
                {
                    if (errno != EAGAIN)
                    {
                        close(connfd);
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }
                else if (ret == 0)
                {
                }
                else
                {
                    //接受客户端数据，通知其他socket连接准备写数据
                    for (int j = 1; j <= user_counter; ++j)
                    {
                        if (fds[j].fd == connfd)
                        {
                            continue;
                        }
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if (fds[i].revents & POLLOUT)
            {
                int connfd = fds[i].fd;
                if (!users[connfd].write_buf)
                {
                    continue;
                }
                ret = send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
                users[connfd].write_buf = NULL;
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }
    delete[] users;
    close(listenfd);
    return 0;
}

```

### 第三个项目（未测试，只是理解了代码）

```C++
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("参数太少");
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    
    //创建TCPsocket
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    int ret;
    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    // 创建UDPsocket，并将其绑定到端口port上
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int updfd = socket(PF_INET, SOCK_DGRAM, 0);
    assert(updfd >= 0);

    ret = bind(updfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(epollfd, listenfd);
    addfd(epollfd, updfd);
    while (1)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (number < 0)
        {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
                addfd(epollfd, connfd);
            }
            else if (sockfd == updfd)
            {
                char buf[UDP_BUFFER_SIZE];
                memset(buf, '\0', UDP_BUFFER_SIZE);
                struct sockaddr_in client_address;
                socklen_t client_length = sizeof(client_address);
                ret = recvfrom(updfd, buf, UDP_BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_address, &client_length);
                if (ret > 0)
                {
                    sendto(updfd, buf, UDP_BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_address, client_length);
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                char buf[TCP_BUFFER_SIZE];
                while (1)
                {
                    memset(buf, '\0', TCP_BUFFER_SIZE);
                    ret = recv(sockfd, buf, TCP_BUFFER_SIZE - 1, 0);
                    if (ret < 0)
                    {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                        {
                            break;
                        }
                        close(sockfd);
                        break;
                    }
                    else if (ret == 0)
                    {
                        close(sockfd);
                    }
                    else
                    {
                        send(sockfd, buf, ret, 0);
                    }
                }
            }else {
                printf("something else happened\n");
            }
        }
    }
    close(listenfd);
}
```

写完了三个项目，还是对客户端操作的一些步骤不太熟悉，应该多拿出代码来记一下。

附带一个觉得不错的blog

https://www.cnblogs.com/Anker/p/3265058.html