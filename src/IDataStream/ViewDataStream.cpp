#include <logvisor/logvisor.hpp>
#include "libderp/ViewDataStream.hpp"

namespace libderp {

ViewDataStream::ViewDataStream(IDataStream *wrap, size_t lengthLimit):
    wrapped(wrap), offset(wrapped->pos()), length(lengthLimit) {
}

ViewDataStream::~ViewDataStream() {
  // We don't own anything, so no cleanup
}

size_t ViewDataStream::size() {
  size_t wrappedSize = wrapped->size();
  if (wrappedSize < offset) {
    return 0; // Probably fine, it'll expand if it needs to
  }
  size_t offsetAdjustedSize = wrappedSize - offset;
  if (offsetAdjustedSize < length) {
    return offsetAdjustedSize;
  }
  return length;
}

size_t ViewDataStream::pos() {
  if (wrapped->pos() < offset) {
    error("ViewDataStream::Wrapped stream position was < offset, returning 0.");
    return 0;
  }
  return wrapped->pos() - offset;
}

void ViewDataStream::seek(size_t pos) {
  if (pos > length) {
    error("ViewDataStream::Wrapped stream attempted to seek past end of limit!");
    wrapped->seek(offset + length);
  } else {
    wrapped->seek(offset + pos);
  }
}

void ViewDataStream::reserve(size_t size) {
  if (size > length) {
    error("ViewDataStream::Wrapped stream attempted to reserve past end of limit!");
    wrapped->reserve(offset + length);
  } else {
    wrapped->reserve(offset + size);
  }
}

void ViewDataStream::truncate() {
  wrapped->truncate();
}

void ViewDataStream::readBytes(std::size_t count, void *dest) {
  if (pos() + count > length) {
    error("ViewDataStream::Wrapped stream attempted to read past end of limit!");
    seek(length);
    memset(dest, 0, count);
  } else {
    wrapped->readBytes(count, dest);
  }
}

void ViewDataStream::writeBytes(std::size_t count, const void *src) {
  if (pos() + count > length) {
    error("ViewDataStream::Wrapped stream attempted to write past end of limit!");
    seek(length);
  } else {
    wrapped->writeBytes(count, src);
  }
}

}

