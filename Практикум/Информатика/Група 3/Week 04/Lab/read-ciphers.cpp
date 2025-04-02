#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>

struct HandshakeProtocol {
  uint8_t type;
  uint8_t length[3];
  uint16_t version;
  uint8_t session_id_length;
  uint16_t cipher_suites_length;
};

struct TLSHeader {
  uint8_t content_type;
  uint16_t version;
  uint16_t length;
  HandshakeProtocol handshake;
};

int main() {
  std::ifstream f{"tls-client-hello.bin", std::ios::binary | std::ios::in};

  TLSHeader h;
  f.read(reinterpret_cast<char *>(&h.content_type), sizeof(h.content_type));
  std::cout << "Content Type: " << h.content_type << std::endl;
  f.read(reinterpret_cast<char *>(&h.version), sizeof(h.version));
  std::cout << "Version: " << h.version << std::endl;
  f.read(reinterpret_cast<char *>(&h.length), sizeof(h.length));
  std::cout << "Length: " << h.length << std::endl;
  f.read(reinterpret_cast<char *>(&h.handshake.type), sizeof(h.handshake.type));
  std::cout << "Handshake Type: " << h.handshake.type << std::endl;
  f.read(reinterpret_cast<char *>(&h.handshake.length),
         sizeof(h.handshake.length));
  std::cout << "Handshake Length: " << *(uint32_t *)&h.handshake.length
            << std::endl;
  f.read(reinterpret_cast<char *>(&h.handshake.version),
         sizeof(h.handshake.version));
  f.seekg(32, std::ios_base::cur);
  f.read(reinterpret_cast<char *>(&h.handshake.session_id_length),
         sizeof(h.handshake.session_id_length));
  f.read(reinterpret_cast<char *>(&h.handshake.cipher_suites_length),
         sizeof(h.handshake.cipher_suites_length));

  auto num_ciphers{static_cast<uint16_t>(h.handshake.cipher_suites_length / 2)};
  std::cout << "Number of ciphers: " << num_ciphers << std::endl;
  for (uint16_t i{0}; i < num_ciphers; i++) {
    uint16_t cipher_suite;
    f.read(reinterpret_cast<char *>(&cipher_suite), sizeof(cipher_suite));
    std::cout << "Cipher suite" << i << ": " << std::hex << cipher_suite
              << std::endl;
  }
}