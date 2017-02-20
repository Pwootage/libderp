#ifndef LIBDERP_FILERETRODATASTREAM_HPP
#define LIBDERP_FILERETRODATASTREAM_HPP

#include <cstdio>
#include "libderp/IRetroDataStream.hpp"

namespace libderp {

class FileRetroDataStream : public IRetroDataStream {
private:
    FILE *fd;
    const char* name;

public:
    FileRetroDataStream(const char *path);
    ~FileRetroDataStream();

    size_t pos() const override;
    void seek(size_t pos) override;
    void reserve(size_t size) override;
    void truncate() override;

    void readBytes(std::size_t count, void *dest) override;
    void writeBytes(std::size_t count, const void *src) override;
    size_t size() const override;

};

}

#endif //LIBDERP_FILERETRODATASTREAM_HPP
