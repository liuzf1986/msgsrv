#pragma once

#include <netinet/in.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


class InetSock {
 public:
  InetSock(int fd);

  void enableReuseAddr(bool enable);
  void enableReusePort(bool enable);

  inline ssize_t send(const void *buf, size_t len, int flags);
  inline ssize_t recv(void* buf, size_t len, int flags);
  

 protected:
  int _fd;
};

class TcpServerSock : InetSock {
 public:
  int bind(const struct sockaddr_in& sockaddr);
};
  
class TcpClientSock : InetSock {
  
};

class UdpServerSock : InetSock {
  
};

class UdpClientSock : InetSock {
  
};







