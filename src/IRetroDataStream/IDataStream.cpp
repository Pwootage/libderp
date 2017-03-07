#include <string>
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


template<typename T>
inline void writeBigEndian(IDataStream *stream, T src) {
  T v = endian::big(src);
  stream->writeBytes(sizeof(T), &v);
}

void IDataStream::write8(int8_t v) { return writeBigEndian(this, v); }
void IDataStream::write16(int16_t v) { return writeBigEndian(this, v); }
void IDataStream::write32(int32_t v) { return writeBigEndian(this, v); }
void IDataStream::write64(int64_t v) { return writeBigEndian(this, v); }
void IDataStream::writeFloat(float v) { return writeBigEndian(this, v); }
void IDataStream::writeDouble(double v) { return writeBigEndian(this, v); }

void IDataStream::writeString(std::string str) {
  writeBytes(str.length(), str.c_str());
  write8(0);
}

template<typename T, void (IDataStream::*func)(T)>
inline void writePrimitive(IDataStream *stream, vector<T> vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    (stream->*func)(vec[i]);
  }
}

template<>
void IDataStream::writeArray(const vector<int8_t> &vec) {
  return writePrimitive<int8_t, &IDataStream::write8> (this, vec);
}

template<>
void IDataStream::writeArray(const vector<int16_t> &vec) {
  return writePrimitive<int16_t, &IDataStream::write16> (this, vec);
}

template<>
void IDataStream::writeArray(const vector<int32_t> &vec) {
  return writePrimitive<int32_t, &IDataStream::write32> (this, vec);
}

template<>
void IDataStream::writeArray(const vector<int64_t> &vec) {
  return writePrimitive<int64_t, &IDataStream::write64> (this, vec);
}

template<>
void IDataStream::writeArray(const vector<float> &vec) {
  return writePrimitive<float, &IDataStream::writeFloat> (this, vec);
}

template<>
void IDataStream::writeArray(const vector<double> &vec) {
  return writePrimitive<double, &IDataStream::writeDouble> (this, vec);
}


DataStreamState IDataStream::state() {
  return _state;
}

size_t IDataStream::errorCount() {
  return _errorCount;
}

void IDataStream::resetState() {
  _state = DataStreamState::ok;
  _errorCount = 0;
}

void IDataStream::error() {
  _state = DataStreamState::error;
  _errorCount++;
}

}
