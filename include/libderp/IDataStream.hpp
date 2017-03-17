#ifndef LIBDERP_IRETRODATASTREAM_HPP
#define LIBDERP_IRETRODATASTREAM_HPP

#include <cstdint>
#include <cstdio>
#include <vector>
#include <functional>
#include <glm/fwd.hpp>

namespace libderp {

enum class DataStreamState {
    ok, error
};

class IDataStream {
public:
    IDataStream() = default;
    virtual ~IDataStream() = default;

    // Implemented in subclass; the base of other methods
    virtual size_t size() = 0;
    virtual size_t pos() = 0;
    virtual void seek(size_t pos) = 0;
    virtual void reserve(size_t size) = 0;
    virtual void truncate() = 0;

    virtual void readBytes(std::size_t count, void *dest) = 0;
    virtual void writeBytes(std::size_t count, const void *src) = 0;

    //Read
    void readPaddingTo(size_t mod);
    int8_t read8();
    int16_t read16();
    int32_t read32();
    int64_t read64();
    uint8_t read8u();
    uint16_t read16u();
    uint32_t read32u();
    uint64_t read64u();
    float readFloat();
    double readDouble();
    std::string readString();
    glm::vec3 readVec3();
    glm::vec4 readVec4();
    glm::mat4x3 readMat4x3();

    template<typename T>
    std::vector<T> readArray(size_t count, std::function<T(IDataStream &stream)> generator);

    //Write
    void writePaddingTo(size_t mod, uint8_t v = 0x00);
    void write8(int8_t v);
    void write16(int16_t v);
    void write32(int32_t v);
    void write64(int64_t v);
    void write8u(uint8_t v);
    void write16u(uint16_t v);
    void write32u(uint32_t v);
    void write64u(uint64_t v);
    void writeFloat(float v);
    void writeDouble(double v);
    void writeString(const std::string &str);
    void writeVec3(const glm::vec3 &vec);
    void writeVec4(const glm::vec4 &vec);
    void writeMat4x3(const glm::mat4x3 &mat);

    template<typename T>
    void writeArray(std::vector<T> vec, std::function<void(IDataStream &stream, const T &obj)> writer);

    //Error state
    DataStreamState state();
    size_t errorCount();
    void resetState();

    void error(const char *format, ...) __printflike(2, 3);

private:
    DataStreamState _state = DataStreamState::ok;
    size_t _errorCount = 0;
};

template<typename T>
std::vector<T> IDataStream::readArray(size_t count, std::function<T(IDataStream &stream)> generator) {
  std::vector<T> res(count);
  for (size_t i = 0; i < count; i++) {
    res[i] = generator(*this);
  }
  return res;
}

template<typename T>
void IDataStream::writeArray(std::vector<T> vec, std::function<void(IDataStream &, const T &)> writer) {
  for (size_t i = 0; i < vec.size(); i++) {
    writer(*this, vec[i]);
  }
}


}

#endif //LIBDERP_PRIMEDATAFILE_HPP
