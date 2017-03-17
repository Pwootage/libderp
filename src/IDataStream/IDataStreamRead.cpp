#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x3.hpp>
#include <logvisor/logvisor.hpp>
#include "libderp/IDataStream.hpp"
#include "libderp/endian.hpp"
#include "libderp/derpexcept.hpp"

#define LIBDERP_MAX_STR_LEN (512)

namespace libderp {
using namespace std;

void IDataStream::readPaddingTo(size_t mod) {
  size_t end = pos();
  size_t padding = mod - (end % mod);
  if (padding != mod) {
    for (size_t i = 0; i < padding; i++) read8();
  }
}

template<typename T>
inline T readBigEndian(IDataStream *stream) {
  T res;
  stream->readBytes(sizeof(T), &res);
  return endian::big(res);
}

int8_t IDataStream::read8() { return readBigEndian<int8_t>(this); }
int16_t IDataStream::read16() { return readBigEndian<int16_t>(this); }
int32_t IDataStream::read32() { return readBigEndian<int32_t>(this); }
int64_t IDataStream::read64() { return readBigEndian<int64_t>(this); }
uint8_t IDataStream::read8u() { return readBigEndian<uint8_t>(this); }
uint16_t IDataStream::read16u() { return readBigEndian<uint16_t>(this); }
uint32_t IDataStream::read32u() { return readBigEndian<uint32_t>(this); }
uint64_t IDataStream::read64u() { return readBigEndian<uint64_t>(this); }
float IDataStream::readFloat() { return readBigEndian<float>(this); }
double IDataStream::readDouble() { return readBigEndian<double>(this); }

string IDataStream::readString() {
  string res;
  char c = read8();
  int i = 0;
  while (c != 0 && i < LIBDERP_MAX_STR_LEN) {
    res += c;
    i++;
    c = read8();
  }
  if (i >= LIBDERP_MAX_STR_LEN) {
    error("String too long (>= %d bytes)", LIBDERP_MAX_STR_LEN);
    return "";
  }
  return res;
}

glm::vec3 IDataStream::readVec3() {
  return {readFloat(), readFloat(), readFloat()};
}

glm::vec4 IDataStream::readVec4() {
  return {readFloat(), readFloat(), readFloat(), readFloat()};
}

glm::mat4x3 IDataStream::readMat4x3() {
  glm::mat4x3 res;

  res[0][0] = readFloat();
  res[1][0] = readFloat();
  res[2][0] = readFloat();
  res[3][0] = readFloat();
  res[0][1] = readFloat();
  res[1][1] = readFloat();
  res[2][1] = readFloat();
  res[3][1] = readFloat();
  res[0][2] = readFloat();
  res[1][2] = readFloat();
  res[2][2] = readFloat();
  res[3][2] = readFloat();

  return res;
}

}
