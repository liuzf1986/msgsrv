#pragma once

#include <stdint.h>
#include <endian.h>


class Endian {
 public:
  static inline uint16_t htons(uint16_t x) {
    return htobe16(x);
  }

  static inline uint32_t htonl(uint32_t x) {
    return htobe32(x);
  }

  static inline uint64_t htonll(uint64_t x) {
    return htobe64(x);
  }

  static inline uint16_t ntohs(uint16_t x) {
    return be16toh(x);
  }

  static inline uint32_t ntohl(uint32_t x) {
    return be32toh(x);
  }

  static inline uint64_t ntohll(uint64_t x) {
    return be64toh(x);
  }
};

