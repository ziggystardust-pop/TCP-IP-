# UDP

## 1. UDP socket 的特点

UDP提供的是不可靠的传输方式，性能相比TCP可能会更好（有些情况），实现更简单

UDP和TCP的差异：
UDP不提供流控制机制，TCP的生命在于流控制，与对方socket连接和断开的过程也属于流控制的一部分

TCP的速度一般比UDP慢，每次交换的数据量越大，TCP的传输速率越接近UDP

## 2. UDP工作原理

![image-20210516204129740](D:\TCP_IP\TCP-IP网络编程学习笔记\chapter6\image-20210516204129740.png)

IP的作用是让离开主机B的UDP数据包准确的传递到主机A，但是把UDP包交给A的某一UDP socket是UDP完成的

UDP常用于实时传输视频，音频

为什么TCP会比UDP慢：

（1）收发数据前后进行的连接设置和清除过程

（2）可靠性的流控制的添加

## UDP实现的客户端/服务端

UDP无需经过连接过程，只有创建socket和数据交换

```c++
//UDP 服务器和客户端都只需要一个socket

// TCP中服务端socket与客户端是一对一关系
// 与10个客户端收发数据，则负责传送数据的服务端socket要10个

// 只需一个UDP socket即可向任意主机传送数据
```

![image-20210516205829355](D:\TCP_IP\TCP-IP网络编程学习笔记\chapter6\image-20210516205829355.png)

```c++
   ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen);

//sock UDP socket文件描述符
//buff 保存待传输数据的缓冲地址值
//nbytes 待传输的数据长度，以字节为单位
//flags 可选项参数，没有则传递0
//to，目标地址的sockaddr结构体变量的地址
//addrlen 地址值的结构体变量长度

//成功则返回传输的字节数，失败返回-1
```
```c++

       ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

```

![image-20210516210844010](D:\TCP_IP\TCP-IP网络编程学习笔记\chapter6\image-20210516210844010.png)