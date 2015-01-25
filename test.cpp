#include <memory>

#include "BitmapTree.hpp"


int count_lwords(size_t size) {
  return (size + (sizeof(unsigned long) << 3) - 1) >> 6;
}

int main(int argc, char *argv[])
{
  // __builtin_clzl

  //  printf("0xFF first bit = %d \n", bsf_c(0xFF) );//__builtin_clzl(0xFFFFFFFFFFFFFFFF));
  //printf("0 first bit = %d \n", bsf_c(0));

  /*
  printf("count 0 = %d \n", count_lwords(0));
  printf("count 1 = %d \n", count_lwords(1));
  printf("count 64 = %d \n", count_lwords(64));
  printf("count 65 = %d \n", count_lwords(65));

  printf("xxx =%lx \n", -1UL << 5);
  */

  BitmapTree bmpTree(65);
  bmpTree._print_dbg();
    for(int i = 0; i < 3; i++) {
      bmpTree.bitRequire();
    }

  // printf("deep = %d \n", bmpTree.getDeep());
  bmpTree._print_dbg();
  printf("bit aquired = %d \n", bmpTree.bitRequire());
  bmpTree._print_dbg();

  
  
  return 0;
}


















