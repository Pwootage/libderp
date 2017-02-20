#include "libderp/IRetroDataStream.hpp"
#include "libderp/endian.hpp"

namespace libderp {

using namespace std;

template<typename T>
inline T readBigEndian(IRetroDataStream *stream) {
  T res;
  stream->readBytes(sizeof(T), &res);
  return endian::big(res);
}

int8_t IRetroDataStream::read8() { return readBigEndian<int8_t>(this); }
int16_t IRetroDataStream::read16() { return readBigEndian<int16_t>(this); }
int32_t IRetroDataStream::read32() { return readBigEndian<int32_t>(this); }
int64_t IRetroDataStream::read64() { return readBigEndian<int64_t>(this); }
float IRetroDataStream::readFloat() { return readBigEndian<float>(this); }
double IRetroDataStream::readDouble() { return readBigEndian<double>(this); }

template<typename T, T (IRetroDataStream::*func)()>
inline vector<T> readPrimitive(IRetroDataStream *stream, size_t count) {
  vector<T> res;
  res.reserve(count);
  for (size_t i = 0; i < count; i++) {
    res[i] = (stream->*func)();
  }
  return res;
}

template<>
vector<int8_t> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<int8_t, &IRetroDataStream::read8> (this, count);
}

template<>
vector<int16_t> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<int16_t, &IRetroDataStream::read16> (this, count);
}

template<>
vector<int32_t> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<int32_t, &IRetroDataStream::read32> (this, count);
}

template<>
vector<int64_t> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<int64_t, &IRetroDataStream::read64> (this, count);
}

template<>
vector<float> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<float, &IRetroDataStream::readFloat> (this, count);
}

template<>
vector<double> IRetroDataStream::readArray(size_t count) {
  return readPrimitive<double, &IRetroDataStream::readDouble> (this, count);
}


template<typename T>
inline void writeBigEndian(IRetroDataStream *stream, T src) {
  T v = endian::big(src);
  stream->writeBytes(sizeof(T), &v);
}

void IRetroDataStream::write8(int8_t v) { return writeBigEndian(this, v); }
void IRetroDataStream::write16(int16_t v) { return writeBigEndian(this, v); }
void IRetroDataStream::write32(int32_t v) { return writeBigEndian(this, v); }
void IRetroDataStream::write64(int64_t v) { return writeBigEndian(this, v); }
void IRetroDataStream::writeFloat(float v) { return writeBigEndian(this, v); }
void IRetroDataStream::writeDouble(double v) { return writeBigEndian(this, v); }

template<typename T, void (IRetroDataStream::*func)(T)>
inline void writePrimitive(IRetroDataStream *stream, vector<T> vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    (stream->*func)(vec[i]);
  }
}

template<>
void IRetroDataStream::writeArray(const vector<int8_t> &vec) {
  return writePrimitive<int8_t, &IRetroDataStream::write8> (this, vec);
}

template<>
void IRetroDataStream::writeArray(const vector<int16_t> &vec) {
  return writePrimitive<int16_t, &IRetroDataStream::write16> (this, vec);
}

template<>
void IRetroDataStream::writeArray(const vector<int32_t> &vec) {
  return writePrimitive<int32_t, &IRetroDataStream::write32> (this, vec);
}

template<>
void IRetroDataStream::writeArray(const vector<int64_t> &vec) {
  return writePrimitive<int64_t, &IRetroDataStream::write64> (this, vec);
}

template<>
void IRetroDataStream::writeArray(const vector<float> &vec) {
  return writePrimitive<float, &IRetroDataStream::writeFloat> (this, vec);
}

template<>
void IRetroDataStream::writeArray(const vector<double> &vec) {
  return writePrimitive<double, &IRetroDataStream::writeDouble> (this, vec);
}

}
