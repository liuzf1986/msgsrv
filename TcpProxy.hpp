#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <thread>
#include <memory>
#include <mutex>

#include "InetSock.hpp"

using namespace std;

/**
 * User epoll for TcpProxy
 */

class TcpProxy {
 public:
  
 private:
  thread _looper;
};
