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


size_t FileDataStream::size() const {
  size_t tmp = pos();
  fseek(fd, 0, SEEK_END);
  size_t size = pos();
  fseek(fd, tmp, SEEK_SET);
  return size;
}

size_t FileDataStream::pos() const {
  long pos = ftell(fd);
  if (pos < 0) {
    LIBDERP_EXCEPT("Failed to read file pos")
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
    error();
    logger.report(logvisor::Error, "fsync() failed");
  }
  if (ftruncate(fileno(fd), pos()) != 0) {
    error();
    logger.report(logvisor::Error, "ftruncate() failed");
  }
  if (freopen(name.c_str(), "rb+", fd) != fd) {
    error();
    logger.report(logvisor::Error, "freopen() failed");
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


