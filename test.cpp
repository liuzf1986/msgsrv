#include "FixedBuffer.hpp"

typedef FixedBuffer<20, 5> testbuf5;
typedef FixedBuffer<20, 10> testbuf10;

extern void foo();

int main(int argc, char *argv[])
{
  testbuf5* f = new testbuf5();
  testbuf5* f2 = new testbuf5();
  testbuf10* t = new testbuf10();

  printf("f %p \n", f->getBuffer());
  printf("f2 %p \n", f2->getBuffer());
  printf("t %p \n", t->getBuffer());


  printf("=============================== \n");

  foo();
  
  return 0;
}


















