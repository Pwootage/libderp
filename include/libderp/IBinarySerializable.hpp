#ifndef LIBDERP_IBINARYSERIALIZABLE_HPP
#define LIBDERP_IBINARYSERIALIZABLE_HPP

namespace libderp {

class IRetroDataStream;

class IBinarySerializable {
    virtual void readFrom(IRetroDataStream stream) = 0;
    virtual void writeTo(IRetroDataStream stream) = 0;
};

}

#endif //LIBDERP_IBINARYSERIALIZABLE_HPP
