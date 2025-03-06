#include <cstdint>

struct version_ihl {
#if BYTE_ORDER == LITTLE_ENDIAN
  uint8_t ihl : 4;
  uint8_t version : 4;
#elif BYTE_ORDER == BIG_ENDIAN
  uint8_t version : 4;
  uint8_t ihl : 4;
#endif
};
