#ifndef LIBDERP_ENDIAN_HPP
#define LIBDERP_ENDIAN_HPP

#include <cstdint>

namespace libderp {
namespace endian {

template<typename T>
static inline T bswap16(T val) {
#if __GNUC__
  return __builtin_bswap16(val);
#elif _WIN32
  return _byteswap_ushort(val);
#else
    return (val = (val << 8) | ((val >> 8) & 0xFF));
#endif
}

template<typename T>
static inline T bswap32(T val) {
#if __GNUC__
  return __builtin_bswap32(val);
#elif _WIN32
  return _byteswap_ulong(val);
#else
    val = (val & 0x0000FFFF) << 16 | (val & 0xFFFF0000) >> 16;
    val = (val & 0x00FF00FF) << 8 | (val & 0xFF00FF00) >> 8;
    return val;
#endif
}

template<typename T>
static inline T bswap64(T val) {
#if __GNUC__
  return __builtin_bswap64(val);
#elif _WIN32
  return _byteswap_uint64(val);
#else
    return ((val & 0xFF00000000000000ULL) >> 56) |
           ((val & 0x00FF000000000000ULL) >> 40) |
           ((val & 0x0000FF0000000000ULL) >> 24) |
           ((val & 0x000000FF00000000ULL) >>  8) |
           ((val & 0x00000000FF000000ULL) <<  8) |
           ((val & 0x0000000000FF0000ULL) << 24) |
           ((val & 0x000000000000FF00ULL) << 40) |
           ((val & 0x00000000000000FFULL) << 56);
#endif
}


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

static inline int16_t big(int16_t val) { return bswap16(val); }
static inline uint16_t big(uint16_t val) { return bswap16(val); }
static inline int32_t big(int32_t val) { return bswap32(val); }
static inline uint32_t big(uint32_t val) { return bswap32(val); }
static inline int64_t big(int64_t val) { return bswap64(val); }
static inline uint64_t big(uint64_t val) { return bswap64(val); }
static inline float big(float val) {
  int32_t ival = bswap32(*((int32_t *) (&val)));
  return *((float *) (&ival));
}
static inline double big(double val) {
  int64_t ival = bswap64(*((int64_t *) (&val)));
  return *((double *) (&ival));
}

static inline int16_t little(int16_t val) { return val; }
static inline uint16_t little(uint16_t val) { return val; }
static inline int32_t little(int32_t val) { return val; }
static inline uint32_t little(uint32_t val) { return val; }
static inline int64_t little(int64_t val) { return val; }
static inline uint64_t little(uint64_t val) { return val; }
static inline float little(float val) { return val; }
static inline double little(double val) { return val; }

#else

static inline int16_t little(int16_t val) { return bswap16(val); }
static inline uint16_t little(uint16_t val) { return bswap16(val); }
static inline int32_t little(int32_t val) { return bswap32(val); }
static inline uint32_t little(uint32_t val) { return bswap32(val); }
static inline int64_t little(int64_t val) { return bswap64(val); }
static inline uint64_t little(uint64_t val) { return bswap64(val); }
static inline float little(float val) {
  int32_t ival = bswap32(*((int32_t *) (&val)));
  return *((float *) (&ival));
}
static inline double little(double val) {
  int64_t ival = bswap64(*((int64_t *) (&val)));
  return *((double *) (&ival));
}

static inline int16_t big(int16_t val) { return val; }
static inline uint16_t big(uint16_t val) { return val; }
static inline int32_t big(int32_t val) { return val; }
static inline uint32_t big(uint32_t val) { return val; }
static inline int64_t big(int64_t val) { return val; }
static inline uint64_t big(uint64_t val) { return val; }
static inline float big(float val) { return val; }
static inline double big(double val) { return val; }
#endif

}
}
#endif //LIBDERP_ENDIAN_HPP
