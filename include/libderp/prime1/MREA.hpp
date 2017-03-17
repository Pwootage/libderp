#ifndef LIBDERP_PRIME1MREA_HPP_HPP
#define LIBDERP_PRIME1MREA_HPP_HPP

#include <libderp/IBinarySerializable.hpp>
#include <libderp/IDataStream.hpp>
#include <cstdint>
#include <glm/mat4x3.hpp>
#include <glm/vec3.hpp>

namespace libderp {
namespace prime1 {

class MREA : public IBinarySerializable {
public:
    static constexpr uint32_t MAGIC = 0xDEADBEEF;
    static constexpr uint32_t VERSION = 0xF;

    glm::mat4x3 transform;
    //TODO: parse these structures so we don't store them

    uint32_t worldModelCount;
    uint32_t dataSectionCount;

    uint32_t worldGeomSectionID;
    uint32_t scriptLayersSectionID;
    uint32_t collisionSectionID;
    uint32_t unknownSectionID;
    uint32_t lightsSectionID;
    uint32_t visiSectionID;
    uint32_t pathSectionID;
    uint32_t areaOctreeID;

    // Read/write methods
    void readFrom(IDataStream &f) override;
    void writeTo(IDataStream &f) override;

};

}
}

#endif //LIBDERP_PRIME1MREA_HPP_HPP
