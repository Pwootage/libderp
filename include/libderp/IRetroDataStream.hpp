#ifndef LIBDERP_IRETRODATASTREAM_HPP
#define LIBDERP_IRETRODATASTREAM_HPP

#include <cstdint>
#include <cstdio>
#include <vector>
#include <functional>

namespace libderp {

class IRetroDataStream {
public:
    // Implemented in subclass; the base of other methods
    virtual size_t size() const = 0;
    virtual size_t pos() const = 0;
    virtual void seek(size_t pos) = 0;
    virtual void reserve(size_t size) = 0;
    virtual void truncate() = 0;

    virtual void readBytes(std::size_t count, void *dest) = 0;
    virtual void writeBytes(std::size_t count, const void *src) = 0;

    //Read
    int8_t read8();
    int16_t read16();
    int32_t read32();
    int64_t read64();
    float readFloat();
    double readDouble();

    template<typename T>
    std::vector<T> readArray(std::size_t count);


    //Write
    void write8(int8_t v);
    void write16(int16_t v);
    void write32(int32_t v);
    void write64(int64_t v);
    void writeFloat(float v);
    void writeDouble(double v);

    template<typename T>
    void writeArray(const std::vector<T> &items);
};

template<typename T>
std::vector<T> IRetroDataStream::readArray(std::size_t count) {
  std::vector<T> res;
  res.reserve(count);
  for (size_t i = 0; i < count; i++) {
    res[i]->readFrom(this);
  }
  return res;
}

template<typename T>
void IRetroDataStream::writeArray(const std::vector<T> &items) {
  for (size_t i = 0; i < items.size(); i++) {
    items[i]->writeTo(this);
  }
}

}

#endif //LIBDERP_PRIMEDATAFILE_HPP
