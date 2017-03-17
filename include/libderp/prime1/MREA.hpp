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

    MREA(IDataStream &stream);

    glm::mat4x3 transform;



    // Read/write methods
    void writeTo(IDataStream &f) override;

};

}
}

#endif //LIBDERP_PRIME1MREA_HPP_HPP
