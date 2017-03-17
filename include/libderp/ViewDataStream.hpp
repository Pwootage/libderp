#ifndef LIBDERP_VIEWRETRODATASTREAM_HPP
#define LIBDERP_VIEWRETRODATASTREAM_HPP

#include <limits>
#include "libderp/IDataStream.hpp"

namespace libderp {

class ViewDataStream : public IDataStream {
public:
    ViewDataStream(IDataStream *wrap, size_t lengthLimit = std::numeric_limits<size_t>::max());
    ~ViewDataStream();

    ViewDataStream(const ViewDataStream &) = delete;
    ViewDataStream(ViewDataStream &&) = delete;
    ViewDataStream &operator=(const ViewDataStream &) = delete;
    ViewDataStream &operator=(ViewDataStream &&) = delete;
    size_t size() override;
    size_t pos() override;
    void seek(size_t pos) override;
    void reserve(size_t size) override;
    void truncate() override;
    void readBytes(std::size_t count, void *dest) override;
    void writeBytes(std::size_t count, const void *src) override;

private:
    IDataStream *wrapped;
    size_t offset;
    size_t length;
};

}

#endif //LIBDERP_VIEWRETRODATASTREAM_HPP
