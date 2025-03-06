#include <cstdint>

struct version_ihl {
  uint8_t version : 4;
  uint8_t ihl : 4;
};
