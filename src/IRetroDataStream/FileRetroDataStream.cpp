#include <stdexcept>
#include "libderp/FileRetroDataStream.hpp"
#include "libderp/derpexcept.hpp"

#ifdef _WIN32
#error TODO: import right stuff for ftruncate
#else
#include <unistd.h>
#endif

namespace libderp {

FileRetroDataStream::FileRetroDataStream(const char *path) {
  name = path;
  fd = fopen(path, "rb+");
  if (fd == nullptr) {
    LIBDERP_EXCEPT("Failed to open file")
  }
}


FileRetroDataStream::~FileRetroDataStream() {
  fclose(fd);
}


size_t FileRetroDataStream::size() const {
  size_t tmp = pos();
  fseek(fd, 0, SEEK_END);
  size_t size = pos();
  fseek(fd, tmp, SEEK_SET);
  return size;
}

size_t FileRetroDataStream::pos() const {
  long pos = ftell(fd);
  if (pos < 0) {
    LIBDERP_EXCEPT("Failed to read file pos")
  } else {
    return static_cast<size_t>(pos);
  }
}

void FileRetroDataStream::seek(size_t pos) {
  fseek(fd, pos, SEEK_SET);
}

void FileRetroDataStream::reserve(size_t size) {
  auto tmp = pos();
  fseek(fd, size, SEEK_SET);
  seek(tmp);
}

void FileRetroDataStream::truncate() {
#ifdef _WIN32
#error TODO: windows ftruncate
#else
  fsync(fileno(fd));
  ftruncate(fileno(fd), pos());
  freopen(name, "rb+", fd);
#endif
}

void FileRetroDataStream::readBytes(std::size_t count, void *dest) {
  fread(dest, 1, count, fd);
}

void FileRetroDataStream::writeBytes(std::size_t count, const void *src) {
  fwrite(src, 1, count, fd);
}

}


