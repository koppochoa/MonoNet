#include "header.h"

Header create_header(uint8_t packet_type, uint8_t packet_count,
                     size_t packet_size) {
  Header header = {.packet_type = packet_type,
                   .packet_count = packet_count,
                   .packet_size = packet_size};
  return header;
}

void reset_header(Header *header) {
  header->packet_count = 0;
  header->packet_size = 0;
  header->packet_type = 0;
}

void show_header(Header *header) {
  ColorPrint(COLOR_BLUE, "[HEADER DEBUG]  ");

  printf("    TYPE    : %d", header->packet_type);
  printf("    Count   : %d", header->packet_count);
  printf("    SIZE    : %ld", header->packet_size);
  printf("\n");
}

int serialize_header(const Header *header, unsigned char *buffer,
                     size_t buffer_len) {
  if (!header)
    return -1;
  if (!buffer)
    return -1;
  if (buffer_len != sizeof(Header))
    return -1;

  buffer[0] = (unsigned char)(header->packet_type & 0xFF);
  buffer[1] = (unsigned char)(header->packet_count & 0xFF);

  for (size_t j = 0; j < sizeof(size_t); j++) {
    buffer[2 + j] = (header->packet_size >> (8 * j)) & 0xFF;
  }

  return 0;
}

int deserialize_header(Header *header, const unsigned char *buffer,
                       size_t buffer_len) {
  if (!header)
    return -1;
  if (!buffer)
    return -1;
  if (buffer_len != sizeof(Header))
    return -1;

  header->packet_type = buffer[0];
  header->packet_count = buffer[1];

  for (size_t j = 0; j < sizeof(size_t); j++) {
    header->packet_size |= ((size_t)buffer[2 + j]) << (8 * j);
  }

  return 0;
}

int send_header(int *fd, unsigned int packet_count, unsigned int packet_type) {
  if (!fd)
    return -1;

  Header header =
      create_header(packet_type, packet_count,
                    (sizeof(Packet) + AES_BLOCK_SIZE) * packet_count);

  //* Serialization du Header
  unsigned char header_s[sizeof(Header)] = {0X0};
  serialize_header(&header, header_s, sizeof(Header));

  return send_data(fd, header_s, sizeof(Header));
}

int receive_header(Header *header, int *fd) {
  unsigned char header_s[sizeof(Header)] = {0x0};

  size_t recept_len = sizeof(Header);

  //* Reception du Header
  int received_bytes = async_receive_data(fd, header_s, &recept_len);

  //* Deserialisation du Header
  deserialize_header(header, header_s, recept_len);

  return received_bytes;
}
