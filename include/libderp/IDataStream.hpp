#ifndef LIBDERP_IRETRODATASTREAM_HPP
#define LIBDERP_IRETRODATASTREAM_HPP

#include <cstdint>
#include <cstdio>
#include <vector>
#include <functional>

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

    template<typename T>
    T read();

    template<typename T>
    std::vector<T> readArray(std::size_t count);

    //Write
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
    void writeString(std::string str);

    template<typename T>
    void write(const T &obj);

    template<typename T>
    void writeArray(const std::vector<T> &items);

    //Error state
    DataStreamState state();
    size_t errorCount();
    void resetState();

    void error(const char *format, ...) __printflike(2, 3);

private:
    DataStreamState _state = DataStreamState::ok;
    size_t _errorCount = 0;
};

template <typename T>
T IDataStream::read() {
    T res;
    res.readFrom(*this);
    return res;
}

template<typename T>
std::vector<T> IDataStream::readArray(std::size_t count) {
  std::vector<T> res;
  res.reserve(count);
  for (size_t i = 0; i < count; i++) {
    res[i]->readFrom(this);
  }
  return res;
}

template <typename T>
void IDataStream::write(const T &obj) {
  obj.writeTo(*this);
}

template<typename T>
void IDataStream::writeArray(const std::vector<T> &items) {
  for (size_t i = 0; i < items.size(); i++) {
    items[i]->writeTo(this);
  }
}

}

#endif //LIBDERP_PRIMEDATAFILE_HPP
