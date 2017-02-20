#include <cstring>
#include "libderp/BufferRetroDataStream.hpp"

libderp::BufferRetroDataStream::BufferRetroDataStream(size_t startingSize) {
  reserve(startingSize);
}

size_t libderp::BufferRetroDataStream::size() const {
  return buff.size();
}

size_t libderp::BufferRetroDataStream::pos() const {
  return curPos;
}

void libderp::BufferRetroDataStream::seek(size_t pos) {
  reserve(pos);
  curPos = pos;
}

void libderp::BufferRetroDataStream::reserve(size_t newSize) {
  if (size() < newSize) {
    buff.reserve(newSize);
  }
}

void libderp::BufferRetroDataStream::truncate() {
  buff.resize(pos());
}

void libderp::BufferRetroDataStream::readBytes(std::size_t count, void *dest) {
  size_t toCopy = count;
  if (pos() + count > size()) {
    toCopy = size() - pos();
  }
  std::memcpy(dest, buff.data(), toCopy);
}

void libderp::BufferRetroDataStream::writeBytes(std::size_t count, const void *src) {
  reserve(pos() + count);
  std::memcpy(buff.data(), src, count);
}
