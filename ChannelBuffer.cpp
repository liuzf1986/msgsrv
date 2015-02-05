
#include <assert.h>
#include <string.h>
#include "ChannelBuffer.hpp"
#include "Endian.hpp"

int64_t ChannelBuffer::peekInt64() {
  assert(getReadbleSize() >= sizeof(int64_t));
  int64_t temp;
  memcpy(&temp, peek(), sizeof(int64_t));
  return Endian::ntoh64(temp);
}

int32_t ChannelBuffer::peekInt32() {
  assert(getReadbleSize() >= sizeof(int32_t));
  int32_t temp;
  memcpy(&temp, peek(), sizeof(int32_t));
  return Endian::ntoh32(temp);
}

int16_t ChannelBuffer::peekInt16() {
  assert(getReadbleSize() >= sizeof(int16_t));
  int16_t temp;
  memcpy(&temp, peek(), sizeof(int16_t));
  return Endian::ntoh16(temp);
}

int8_t ChannelBuffer::peekInt8() {
  return *peek();
}

int8_t* ChannelBuffer::peek() {
  return begin() + _readerIndex;
}

int8_t* ChannelBuffer::hold() {
  return begin() + _writerIndex;
}

int64_t ChannelBuffer::readInt64() {
  int64_t ret = peekInt64();
  fixReaded(sizeof(int64_t));
  return ret;
}

int32_t ChannelBuffer::readInt32() {
  int32_t ret = peekInt32();
  fixReaded(sizeof(int32_t));
  return ret;
}

int16_t ChannelBuffer::readInt16() {
  int16_t ret = peekInt16();
  fixReaded(sizeof(int16_t));
  return ret;
}

int8_t ChannelBuffer::readInt8() {
  int8_t ret = peekInt8();
  fixReaded(sizeof(int8_t));
  return ret;
}

int8_t* ChannelBuffer::read(size_t size) {
  int8_t* ret = peek();
  fixReaded(size);
  return ret;
}

void ChannelBuffer::autoEnlarge(size_t size) {
  size_t append = size - getWrittableSize();

  if(append > 0) {
    if(append <= getCapacity()) {
      _buffer.resize(getCapacity() * 2);
    } else {
      _buffer.resize(getCapacity() + append);
    }
  }
}

void ChannelBuffer::writeInt64(int64_t value) {
  int64_t wval = Endian::hton64(value);
  write(static_cast<void*>(&wval), sizeof(int64_t));
}

void ChannelBuffer::writeInt32(int32_t value) {
  int32_t wval = Endian::hton32(value);
  write(static_cast<void*>(&wval), sizeof(int32_t));
}

void ChannelBuffer::writeInt16(int16_t value) {
  int16_t wval = Endian::hton16(value);
  write(static_cast<void*>(&wval), sizeof(int16_t));
}

void ChannelBuffer::writeInt8(int8_t value) {
  write(&value, sizeof(int8_t));
}

void ChannelBuffer::write(const void* data, size_t size) {
  autoEnlarge(size);
  memcpy(hold(), data, size);
  fixWritted(size);
}
  
void ChannelBuffer::markReadIdx() {
  _readerMarked = _readerIndex;
}

void ChannelBuffer::resetReadIdx() {
  _readerIndex = _readerMarked;
}
  
void ChannelBuffer::markWriteIdx() {
  _writerMarked = _writerIndex;
}

void ChannelBuffer::resetWriteIdx() {
  _writerIndex = _writerMarked;
}

void ChannelBuffer::fixReaded(size_t size) {
  _readerIndex += size;
  assert(_readerIndex <= _writerIndex);
  assert(_readerIndex <= getCapacity());

  if(_readerIndex == getCapacity()) {
    discardReadBytes();
  }
}

void ChannelBuffer::fixWritted(size_t size) {
  _writerIndex += size;
  assert(_writerIndex <= getCapacity());
}

size_t ChannelBuffer::getReadbleSize() const {
  return _writerIndex - _readerIndex;
}

size_t ChannelBuffer::getWrittableSize() const {
  return getCapacity() - _writerIndex;
}

size_t ChannelBuffer::getCapacity() const {
  return _buffer.size();
}

void ChannelBuffer::discardReadBytes() {
  _readerIndex = 0;
  _writerIndex = 0;
  _readerMarked = -1;
  _writerMarked = -1;
}

