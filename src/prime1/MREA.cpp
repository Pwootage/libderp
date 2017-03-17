#include <vector>
#include <functional>
#include <iostream>
#include "libderp/prime1/MREA.hpp"

using namespace std;

namespace libderp {
namespace prime1 {

MREA::MREA(IDataStream &f) {
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
  transform = f.readMat4x3();

  uint32_t modelCount = f.read32u();
  uint32_t dataSectionCount = f.read32u();

  uint32_t geomSectionID = f.read32u();
  uint32_t scriptLayersSectionID = f.read32u();
  uint32_t collisionSectionID = f.read32u();
  uint32_t unknownSectionID = f.read32u();
  uint32_t lightsSectionID = f.read32u();
  uint32_t visiSectionID = f.read32u();
  uint32_t pathSectionID = f.read32u();
  uint32_t areaOctreeID = f.read32u();

  vector<uint32_t> sectionSizes = f.readArray<uint32_t>(dataSectionCount, &IDataStream::read32u);
  f.readPaddingTo(32);

  vector<vector<uint8_t>> sections(dataSectionCount);
  for (size_t i = 0; i < dataSectionCount; i++) {
    uint32_t size = sectionSizes[i];
    vector<uint8_t> section(size);
    f.readBytes(size, &section[0]);
    f.readPaddingTo(32);
    sections[i] = section;
  }

//  vector<uint8_t> sections = f.read
  //PARSIN TIME

}

void MREA::writeTo(IDataStream &f) {
  f.write32u(MAGIC);
  f.write32u(VERSION);
  f.writeMat4x3(transform);
}


}
}



