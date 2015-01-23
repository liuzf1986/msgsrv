#pragma once

#include <memory>
#include <stack>
#include <string.h>

#include "Utils.hpp"

/** 
 * This must compile in gcc, 
 */

using namespace std;

struct BitmapLayer {
  BitmapLayer(size_t size) : _bits(nullptr), _lwords(0), _tailBits(0) {
    if(size > 0) {
      /* allocate uint64_t array */
      _lwords = calculate_lwords(size);
      _bits = new uint64_t[_lwords];
      _tailBits = (size & 0x3F);

      /* set all bits initial */
      memset((void*)_bits, 0xFF,(_lwords << 3));

      /* fix last uint64_t */
      if(0 != _tailBits) {
        _bits[_lwords - 1] = ((_bits[_lwords - 1]) & (-1UL << ((sizeof(uint64_t) << 3) - _tailBits)));
      }

      printf("tail = %lu \n", _tailBits );
    }
  }

  ~BitmapLayer() {
    delete[] _bits;
    _bits = nullptr;
    _lwords = 0;
  }

  /* calculate how much uint64_t contain size's bits */
  inline size_t calculate_lwords(size_t size) {
    return (size + (sizeof(unsigned long) << 3) - 1) >> 6;
  }

  void _print_dbg() const {
    for(int i = 0; i < _lwords; i ++) {
      printf("%lx ", _bits[i]);
    }
  }
  
  uint64_t* _bits;
  size_t _lwords;   // indicate how much long ints.
  size_t _tailBits; // how much valid bits in tail uint64_t
};

class BitmapTree {
 public:
  BitmapTree(size_t size) {
    static_assert((8 == sizeof(unsigned long)), "long word is not 8 bytes");
    stack<BitmapLayer*> layers;
    size_t lsize = size;

    while (lsize > 1) {
      BitmapLayer* layer = new BitmapLayer(lsize);
      layers.push(layer);
      lsize = layer->_lwords;
    }

    _deep = layers.size();

    for(int i = 0; i < ARRAY_SIZE(_layers); i++) {
      if(!layers.empty()) {
        _layers[i] = layers.top();
        layers.pop();
      } else {
        _layers[i] = nullptr;
      }
    }
  }
  ~BitmapTree() {
    _deep = 0;
    for(int i = 0; i < ARRAY_SIZE(_layers); i++) {
      if(nullptr != _layers[i]) {
        delete _layers[i];
      } else {
        break;
      }
    }
  }

  uint8_t getDeep() const {
    return _deep;
  }

  void _print_dbg() const {
    for(int i = 0; i < _deep; i++) {
      _layers[i]->_print_dbg();
      printf("\n");
    }
  }

 private:
  /* find first seted bit in uint64_t */
  inline int firstBitSet(uint64_t lword) {
    return __builtin_clzl(lword);
  }
  
  /* 5 layer max deep, can describe 64 ^ 8 = 2 ^ 48 objs */
  BitmapLayer* _layers[8];
  uint8_t _deep;
};









