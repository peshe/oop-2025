#include <cstdint>
#include <fstream>
#include <iostream>

#include <arpa/inet.h>

#include "version_ihl_portable.h"

union first_byte_of_ipv4_hdr {
  uint8_t value;
  version_ihl bitfield;
};

struct ipv4_hdr {
  first_byte_of_ipv4_hdr first_byte;
  uint8_t type_of_service;
  uint16_t total_length;
  uint16_t packet_id;
  uint16_t fragment_offset;
  uint8_t time_to_live;
  uint8_t next_proto_id;
  uint16_t hdr_checksum;
  uint32_t src_addr;
  uint32_t dst_addr;
};

int main() {
  std::ifstream f{"ipv4-hdr.bin"};
  ipv4_hdr h;
  f.read((char *)&h, sizeof(h));
  std::cout << "Structure size: " << sizeof(h) << std::endl;
  std::cout << "First byte of structure: " << (int)((uint8_t *)&h)[0]
            << std::endl;
  std::cout << "Whole union value: " << (int)h.first_byte.value << std::endl;
  std::cout << "Higher nibble of first byte: "
            << (int)h.first_byte.bitfield.version << std::endl;
  std::cout << "Lower nibble of first byte: " << (int)h.first_byte.bitfield.ihl
            << std::endl;
  std::cout << "Second member of struct: " << (int)h.type_of_service
            << std::endl;
  std::cout << "Third member of struct: " << ntohs(h.total_length) << std::endl;
  std::cout << "Seventh member of struct: " << (int)h.next_proto_id
            << std::endl;
  std::cout << "Last member of struct: " << ntohl(h.dst_addr) << std::endl;

  return 0;
}
