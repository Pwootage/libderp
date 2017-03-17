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
inline void writeBigEndian(IDataStream *stream, T src) {
  T v = endian::big(src);
  stream->writeBytes(sizeof(T), &v);
}

void IDataStream::write8(int8_t v) { return writeBigEndian(this, v); }
void IDataStream::write16(int16_t v) { return writeBigEndian(this, v); }
void IDataStream::write32(int32_t v) { return writeBigEndian(this, v); }
void IDataStream::write64(int64_t v) { return writeBigEndian(this, v); }
void IDataStream::write8u(uint8_t v) { return writeBigEndian(this, v); }
void IDataStream::write16u(uint16_t v) { return writeBigEndian(this, v); }
void IDataStream::write32u(uint32_t v) { return writeBigEndian(this, v); }
void IDataStream::write64u(uint64_t v) { return writeBigEndian(this, v); }
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

}
