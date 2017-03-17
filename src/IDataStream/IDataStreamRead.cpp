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
    LIBDERP_EXCEPT("String too long (>= LIBDERP_MAX_STR_LEN bytes)")
  }
  return res;
}

template<typename T, T (IDataStream::*func)()>
inline vector<T> readPrimitive(IDataStream *stream, size_t count) {
  vector<T> res;
  res.reserve(count);
  for (size_t i = 0; i < count; i++) {
    res[i] = (stream->*func)();
  }
  return res;
}

template<>
vector<int8_t> IDataStream::readArray(size_t count) {
  return readPrimitive<int8_t, &IDataStream::read8> (this, count);
}

template<>
vector<int16_t> IDataStream::readArray(size_t count) {
  return readPrimitive<int16_t, &IDataStream::read16> (this, count);
}

template<>
vector<int32_t> IDataStream::readArray(size_t count) {
  return readPrimitive<int32_t, &IDataStream::read32> (this, count);
}

template<>
vector<int64_t> IDataStream::readArray(size_t count) {
  return readPrimitive<int64_t, &IDataStream::read64> (this, count);
}

template<>
vector<float> IDataStream::readArray(size_t count) {
  return readPrimitive<float, &IDataStream::readFloat> (this, count);
}

template<>
vector<double> IDataStream::readArray(size_t count) {
  return readPrimitive<double, &IDataStream::readDouble> (this, count);
}

}
