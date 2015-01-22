#pragma once

#include <memory>

/**
 * Fixed size buffer pool implementation.
 *
 * we must garentee the ALLOC class will alloc N byte each time
 * we called alloc
 */

template <int C, int N>
struct FixedBufferPool {
  static void* alloc() {
    return poolBuf;
  }

  static void release(void* buf) {
    return;
  }
private:
  static void* _poolBuf;
};

template<int C, int N> void* FixedBufferPool<C, N>::poolBuf = malloc(C * N);

template <int C, int N, typename ALLOC=FixedBufferPool<C, N> >
class FixedBuffer {
 public:
  FixedBuffer() : _len(0) {
    _bufptr = ALLOC::alloc();
  }
  
  ~FixedBuffer() {
    ALLOC::release(_bufptr);
  }

  /* can not by copyed */
  FixedBuffer(const FixedBuffer& ) = delete;
  FixedBuffer& operator= (const FixedBuffer& ) = delete;

  inline void setLength(size_t len) {
    _len = len;
  }
  
  inline size_t getLength() const {
    return _len;
  }

  inline void* getBuffer() const {
    return _bufptr;
  }
  
  inline size_t getCapacity() const {
    return CAP;
  }
 private:
  enum {CAP=N};  // static describe capacity of th buffer
  size_t _len;   // data length
  void* _bufptr; // buffer address
};

