#pragma once
#include <stdint.h>
#include <vector>

using namespace std;

/**
 * implement like netty ChannelBuffer
 */

class ChannelBuffer {
  static const size_t DEF_INIT_SIZE = 1024;
 public:
  explicit ChannelBuffer(size_t initSize = DEF_INIT_SIZE)
      : _buffer(initSize),
        _readerIndex(0),
        _readerMarked(-1),
        _writerIndex(0),
        _writerMarked(-1) {}

  int32_t peekInt32() {
    
  }

  int16_t peekInt16() {
    
  }

  int8_t peekInt8() {
    
  }

  
  
  void markReadIdx();
  void resetReadIdx();
  
  void markWriteIdx();
  void resetWriteIdx();

  void discardReadBytes();
  
 private:
  vector<uint8_t> _buffer;
  uint32_t _readerIndex;
  int32_t _readerMarked;
  uint32_t _writerIndex;
  int32_t _writerMarked;
};



















