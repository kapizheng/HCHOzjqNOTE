### 通用socket地址

- sockaddr
- sockaddr_storage

### 专用socket地址

- sockaddr_un
- sockaddr_in
- sockaddr_in6

### IP地址转换函数

- inet_addr(const char*strptr);将点分10进制表示的IPv4地址转换为用网络字节序整数表示的IPv4地址。失败返回INADDR_NONE。
- inet_aton(const char*cp,struct in_addrinp):函数完成和inet_addr同样的功能但是转化结果存储于参数inp指向的地址。成功返回1，失败返回0。
- inet_ntoa(struct in_addr in):函数将用网络字节序整数表示的IPv4转化为用点分十进制字符串表示的IPv4地址。该函数是不可重入，也就是函数被调用的时候，无法保证里面内容和之前一样。
- `inet_pton(int af,const char*src,void*dst)`