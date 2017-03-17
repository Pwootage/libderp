#include "libderp/prime1/MREA.hpp"

namespace libderp {
namespace prime1 {

void MREA::readFrom(IDataStream &f) {
  uint32_t magic = f.read32u();
  if (magic != MAGIC) {
    f.error("MREA::Invalid magic (%x, expected %x)", magic, MAGIC);
    return;
  }
  uint32_t version = f.read32u();
  if (version != VERSION) {
    f.error("MREA::Invalid version (%u, expected %u)", version, VERSION);
    return;
  }
}

void MREA::writeTo(IDataStream &f) {
  f.write32u(MAGIC);
  f.write32u(VERSION);
}


}
}



