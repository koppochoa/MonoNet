#ifndef METADATA_H
#define METADATA_H

#include <time.h>
#include <stdint.h>
#include <string.h>
#include "utils.h"
typedef struct {
  uint8_t type;
  struct tm time;
} Metadata;

Metadata create_metadata(uint8_t type);
void reset_metadata(Metadata *metadata);
void show_metadata(Metadata *metadata);

int serialize_metadata(const Metadata *metadata, unsigned char *buffer,
                       size_t buffer_len);
int deserialize_metadata(const unsigned char *buffer, Metadata *metadata,
                         size_t buffer_len);

#endif
