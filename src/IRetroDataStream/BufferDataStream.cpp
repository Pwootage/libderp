#include <cstring>
#include "libderp/BufferDataStream.hpp"

libderp::BufferDataStream::BufferDataStream(size_t startingSize) {
  reserve(startingSize);
}

size_t libderp::BufferDataStream::size() const {
  return buff.size();
}

size_t libderp::BufferDataStream::pos() const {
  return curPos;
}

void libderp::BufferDataStream::seek(size_t pos) {
  reserve(pos);
  curPos = pos;
}

void libderp::BufferDataStream::reserve(size_t newSize) {
  if (size() < newSize) {
    buff.reserve(newSize);
  }
}

void libderp::BufferDataStream::truncate() {
  buff.resize(pos());
}

void libderp::BufferDataStream::readBytes(std::size_t count, void *dest) {
  size_t toCopy = count;
  if (pos() + count > size()) {
    toCopy = size() - pos();
  }
  std::memcpy(dest, buff.data(), toCopy);
}

void libderp::BufferDataStream::writeBytes(std::size_t count, const void *src) {
  reserve(pos() + count);
  std::memcpy(buff.data(), src, count);
}
