#ifndef LIBDERP_BUFFERRETRODATASTREAM_HPP
#define LIBDERP_BUFFERRETRODATASTREAM_HPP

#include "libderp/IRetroDataStream.hpp"
#include <vector>

namespace libderp {

class BufferRetroDataStream : public IRetroDataStream {
private:
    std::vector<uint8_t> buff;
    size_t curPos;

public:
    BufferRetroDataStream(size_t startingSize);

    size_t size() const;
    size_t pos() const override;
    void seek(size_t pos) override;
    void reserve(size_t size) override;
    void truncate() override;

    void readBytes(std::size_t count, void *dest) override;
    void writeBytes(std::size_t count, const void *src) override;
};

}

#endif //LIBDERP_BUFFERRETRODATASTREAM_HPP
