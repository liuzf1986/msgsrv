#include <memory>

#include "BitmapTree.hpp"
#include "FixedBuffer.hpp"
#include "PeerMessage.hpp"

typedef PMRecv<> DefPeerMessage;
typedef FixedObjCreator<DefPeerMessage, MAX_PEER_MSG> PMCreator;


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

  #if 0
  BitmapTree bmpTree(66);
  printf("deep = %d \n", bmpTree.getDeep());
  bmpTree._print_dbg();
  
  for(int i = 0; i < 64; i++) {
    // bmpTree.bitRequire();
    printf("bit aquired = %ld \n", bmpTree.bitRequire());
  }
  bmpTree._print_dbg();

  for(int i = 0; i < 10; i ++) {
    off64_t off = bmpTree.bitRequire();
    printf("bit aquired = %ld \n", off);
    bmpTree.bitTurnback(off);
  }

  bmpTree._print_dbg();

  printf("================================================= \n");
  #endif

  DefPeerMessage* pm = PMCreator::create();

  printf(" pm = %p, ================================================= \n", pm);
  return 0;
}


















