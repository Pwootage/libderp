#ifndef LIBDERP_IBINARYSERIALIZABLE_HPP
#define LIBDERP_IBINARYSERIALIZABLE_HPP

namespace libderp {

class IDataStream;

class IBinarySerializable {
public:
    virtual void readFrom(IDataStream &stream) = 0;
    virtual void writeTo(IDataStream &stream) = 0;
};

}

#endif //LIBDERP_IBINARYSERIALIZABLE_HPP
