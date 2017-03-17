#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x3.hpp>
#include <logvisor/logvisor.hpp>
#include "libderp/IDataStream.hpp"
#include "libderp/endian.hpp"
#include "libderp/derpexcept.hpp"

#define LIBDERP_MAX_STR_LEN (512)

namespace libderp {
using namespace std;

static logvisor::Module logger("IDataStream");

DataStreamState IDataStream::state() {
  return _state;
}

size_t IDataStream::errorCount() {
  return _errorCount;
}

void IDataStream::resetState() {
  _state = DataStreamState::ok;
  _errorCount = 0;
}

void IDataStream::error(const char *format, ...) {
  _state = DataStreamState::error;
  _errorCount++;
  va_list ap;
  va_start(ap, format);
  logger.report(logvisor::Level::Error, format, ap);
  va_end(ap);
}

}
