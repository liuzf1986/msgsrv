#pragma once
#include <stdint.h>
#include <vector>

#include "Endian.hpp"

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

  /* peek data, but not update _readerIndex */
  inline int64_t peekInt64();
  inline int32_t peekInt32();
  inline int16_t peekInt16();
  inline int8_t peekInt8();

  /* return readable and writtable pointer */
  inline int8_t* peek();
  inline int8_t* hold();

  /* read data and update _readerIndex */
  inline int64_t readInt64();
  inline int32_t readInt32();
  inline int16_t readInt16();
  inline int8_t readInt8();
  inline int8_t* read(size_t size);

  /* write data and update _writerIndex */
  inline void autoEnlarge(size_t size);
  inline void writeInt64(int64_t value);
  inline void writeInt32(int32_t value);
  inline void writeInt16(int16_t value);
  inline void writeInt8(int8_t value);
  inline void write(const void* data, size_t size);
  
  /* reset index will overwrite index to last marked */
  inline void markReadIdx();
  inline void resetReadIdx();
  inline void markWriteIdx();
  inline void resetWriteIdx();
  inline void fixReaded(size_t size);
  inline void fixWritted(size_t size);

  /* get reference buffer size */
  inline size_t getReadbleSize() const;
  inline size_t getWrittableSize() const;
  inline size_t getCapacity() const;

  /* discard readable bytes will move readable bytes to begining of buffer and update index */
  inline void discardReadBytes();
  
 private:
  int8_t* begin() { return &*_buffer.begin(); }

  const int8_t* begin() const { return &*_buffer.begin(); }

  vector<int8_t> _buffer;
  uint32_t _readerIndex;
  int32_t _readerMarked;
  uint32_t _writerIndex;
  int32_t _writerMarked;
};












