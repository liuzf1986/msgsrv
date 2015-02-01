#pragma once

#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <mutex>
#include <memory>

using namespace std;

/**
 * append lock free
 * flush locked, we assume that log increase in reasonable speed.
 *
 * we use high 4 bits to describe buffer index.
 * ----|--------------------------
 */

template <typename OPS, int C, int N>
class Logger {
 public:
  typedef Logger<OPS, N> self;
  enum {
    VERBOSE,
    DEBUG,
    INFO,
    WARRING,
    ERROR
  } LEVEL;
  
  Logger(int cacheSize, unique_ptr<OPS>& outputStream) : _mutex(), _opsptr(std::move(outputStream)) {
  }
  ~Logger() {}

  template <typename T>
  size_t stringFromNumeric(char buf[], T value) {
    static const char digits[] = "9876543210123456789";
    static const char* zero = digits + 9;
    static_assert(sizeof(digits) == 20);

    T i = value;
    char* p = buf;

    do
    {
      int lsd = static_cast<int>(i % 10);
      i /= 10;
      *p++ = zero[lsd];
    } while (i != 0);
  
    if (value < 0)
    {
      *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
  }

  size_t convertHex(char buf[], uintptr_t value)
  {
    static const char digitsHex[] = "0123456789ABCDEF";
    static_assert(sizeof digitsHex == 17);

    uintptr_t i = value;
    char* p = buf;

    do
    {
      int lsd = static_cast<int>(i % 16);
      i /= 16;
      *p++ = digitsHex[lsd];
    } while (i != 0);

    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
  }

  self& operator<<(bool v) {
    
  }
  
  self& operator<<(short) {
    
  }
  
  self& operator<<(unsigned short) {
    
  }
  
  self& operator<<(int) {
    
  }
  self& operator<<(unsigned int) {
    
  }
  
  self& operator<<(long) {
    
  }
  
  self& operator<<(unsigned long) {
    
  }
  
  self& operator<<(long long) {
    
  }
  
  self& operator<<(unsigned long long) {
    
  }
  
  self& operator<<(const void*) {
    
  }
  
  self& operator<<(float v) {
    
  }
  
  self& operator<<(double) {
    
  }
  
  // self& operator<<(long double);
  self& operator<<(char v) {
    
  }
  
  // self& operator<<(signed char);
  // self& operator<<(unsigned char);
  self& operator<<(const char* str) {
    
  }
  
  self& operator<<(const unsigned char* str) {
    
  }
  
  self& operator<<(const string& v) {
    
  }
  
  self& operator<<(const std::string& v) {
    
  }

 private:
  void flush() {
    
  }
  
  void swapCache() {
    lock_guard<mutex> lock(_mutex);
    constexpr int cacheCnt = (sizeof(_cache) / sizeof(_cache[0]));
    static_assert(cacheCnt == 2, "maybe to degree size count wrong");
    /* flush older cache,  */
    _opsptr->flush(_cache[_curIdx], _cur - _cache[_curIdx]);
    
    _curIdx = (_curIdx + 1) % cacheCnt;
    _cur = _cache[_curIdx];
  }
  
  
  char _cache[C][N];
  char* _cur;
  mutable mutex _mutex;
  unique_ptr<OPS> _opsptr;
};












