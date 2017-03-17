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


void IDataStream::writePaddingTo(size_t mod, uint8_t v) {
  size_t end = pos();
  size_t padding = mod - (end % mod);
  if (padding != mod) {
    for (size_t i = 0; i < padding; i++) write8(v);
  }
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
void IDataStream::write8u(uint8_t v) { return writeBigEndian(this, v); }
void IDataStream::write16u(uint16_t v) { return writeBigEndian(this, v); }
void IDataStream::write32u(uint32_t v) { return writeBigEndian(this, v); }
void IDataStream::write64u(uint64_t v) { return writeBigEndian(this, v); }
void IDataStream::writeFloat(float v) { return writeBigEndian(this, v); }
void IDataStream::writeDouble(double v) { return writeBigEndian(this, v); }

void IDataStream::writeString(const string &str) {
  writeBytes(str.length(), str.c_str());
  write8(0);
}

void IDataStream::writeVec3(const glm::vec3 &vec) {
  writeFloat(vec.x);
  writeFloat(vec.y);
  writeFloat(vec.z);
}

void IDataStream::writeVec4(const glm::vec4 &vec) {
  writeFloat(vec.x);
  writeFloat(vec.y);
  writeFloat(vec.z);
  writeFloat(vec.w);
}

void IDataStream::writeMat4x3(const glm::mat4x3 &mat) {
  writeFloat(mat[0][0]);
  writeFloat(mat[1][0]);
  writeFloat(mat[2][0]);
  writeFloat(mat[3][0]);
  writeFloat(mat[0][1]);
  writeFloat(mat[1][1]);
  writeFloat(mat[2][1]);
  writeFloat(mat[3][1]);
  writeFloat(mat[0][2]);
  writeFloat(mat[1][2]);
  writeFloat(mat[2][2]);
  writeFloat(mat[3][2]);
}

}
