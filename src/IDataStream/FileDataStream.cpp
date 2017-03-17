#include <stdexcept>
#include "libderp/FileDataStream.hpp"
#include "libderp/derpexcept.hpp"
#include "logvisor/logvisor.hpp"

#ifdef _WIN32
#error TODO: import right stuff for ftruncate
#else
#include <unistd.h>
#endif

namespace libderp {
static logvisor::Module logger("FileDataStream");

FileDataStream::FileDataStream(std::string path) {
  name = path;
  fd = fopen(name.c_str(), "rb+");
  if (fd == nullptr) {
    LIBDERP_EXCEPT("Failed to open file")
  }
}

FileDataStream::~FileDataStream() {
  if (fd != nullptr) {
    fclose(fd);
    fd = nullptr;
  }
}


size_t FileDataStream::size() {
  size_t tmp = pos();
  if (fseek(fd, 0, SEEK_END) < 0) {
    error("FileDataStream::Failed to seek to end of file to determine size");
    return 0;
  }
  size_t size = pos();
  if (fseek(fd, tmp, SEEK_SET)) {
    error("FileDataStream::Failed to seek to pos after determining size");
    return 0;
  }
  return size;
}

size_t FileDataStream::pos() {
  long pos = ftell(fd);
  if (pos < 0) {
    error("FileDataStream::Failed to read file pos/ftell() failed");
    return 0;
  } else {
    return static_cast<size_t>(pos);
  }
}

void FileDataStream::seek(size_t pos) {
  fseek(fd, pos, SEEK_SET);
}

void FileDataStream::reserve(size_t size) {
  //No need to reserve in file, it grows automatically
}

void FileDataStream::truncate() {
#ifdef _WIN32
#error TODO: windows ftruncate
#else
  if (fsync(fileno(fd)) != 0) {
    error("FileDataStream::fsync() failed");
    return;
  }
  if (ftruncate(fileno(fd), pos()) != 0) {
    error("FileDataStream::ftruncate() failed");
    return;
  }
  if (freopen(name.c_str(), "rb+", fd) != fd) {
    error("FileDataStream::freopen() failed");
    return;
  };
#endif
}

void FileDataStream::readBytes(std::size_t count, void *dest) {
  fread(dest, 1, count, fd);
}

void FileDataStream::writeBytes(std::size_t count, const void *src) {
  fwrite(src, 1, count, fd);
}

}


