#ifndef LIBDERP_FILERETRODATASTREAM_HPP
#define LIBDERP_FILERETRODATASTREAM_HPP

#include <cstdio>
#include <string>
#include "libderp/IDataStream.hpp"

namespace libderp {

class FileDataStream : public IDataStream {
private:
    FILE *fd;
    std::string name;

public:
    FileDataStream(std::string path);
    ~FileDataStream();

    FileDataStream(const FileDataStream &) = delete;
    FileDataStream(FileDataStream &&) = delete;
    FileDataStream &operator=(const FileDataStream &) = delete;
    FileDataStream &operator=(FileDataStream &&) = delete;

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
