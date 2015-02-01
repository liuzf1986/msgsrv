#include <algorithm>
#include <stdint.h>
#include <string.h>
#include "Logger.hpp"


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




