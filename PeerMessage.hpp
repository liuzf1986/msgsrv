#pragma once

#include <netinet/in.h>
#include <sys/uio.h>
#include "FixedBuffer.hpp"


#define MAX_PEER_MSG   (5 * 10000)

typedef enum {
  PMPROTO_PROTOBUF,
  PMPROTO_JSON
} PMProto;


/**
 * Destruct inet peer.
 * if it's _fd is natural number, we can reply the peer with fd.
 * otherwise, we reply it with sockaddr_in.
 *
 * major cmd will indicate the module id that receive the message, high 16 bits
 * minor cmd is real command the module handle for, low 16 bits
 */

struct PMEmpty {
  uint8_t empty[0];
};

static_assert((sizeof(PMEmpty) == 0), "size PMEmpty != 0");

/**
 * Describe peer message information
 */
struct PMInfo {
  inline uint16_t majorCmd() const {
    return _cmd >> 16;
  }

  inline uint16_t minorCmd() const {
    return _cmd & 0xFFFF;
  }
  
  PMProto _proto;
  uint32_t _version;  
  uint32_t _cmd;
  uint32_t _seq;
};

/**
 * Describe peer message data that unpacked.
 */
typedef struct iovec PMData;

/**
 * Describe remote address, if peer has fd, then _fd is natural number.
 */
struct PMAddr {
  int _fd;
  struct sockaddr_in _addr;
};

/**
 * Describe message that will send to peer.
 */
#pragma pack(push)
#pragma pack(4)
template <class P1, class P2 = PMEmpty>
struct PMSent {
  PMInfo _info;
  PMData _data;
  P1 _ps;
  P2 _pe;
};
#pragma pack(pop)

/**
 * Describe message that receive from peer.
 */
#pragma pack(push)
#pragma pack(4)
template <int N = 1024>
struct PMRecv {
  PMInfo _info;
  PMData _data;
  enum { CAP = N };
 private:
  uint8_t _buf[N];
};
#pragma pack(pop)

