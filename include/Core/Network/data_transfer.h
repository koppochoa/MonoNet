#pragma once

#include <stddef.h>

int send_data(int* fd, const unsigned char* data, unsigned int len);
//unsigned char*  async_receive_data(int* fd, int len);
int async_receive_data(int* fd, unsigned char* output, size_t* len);

int async_receive_data_partial(int* fd, unsigned char* output, size_t total_size, size_t already_received,int* errcode);

