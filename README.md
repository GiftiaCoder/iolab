# iolab
### epolllab
因为工作涉及，就自己回来把以前写的epoll模型用面向对象的方式重构一遍，顺便深入研究一下epoll的机制
1. 目前发现在client的socket关闭（JDK 1.8）后，ubuntu和centos都会立即受到一个EPOLLRDHUP事件，但ubuntu在两分钟后还会额外收到一个EPOLLERR | EPOLLHUP | EPOLLIN事件
### liblog
1. 自己用于调试用的简单log api，用于向stdout和指定fd输出log，同时也能将log通过syslog输出
2. 函数调用栈的打印方式尚在研究中
