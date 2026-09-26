#ifndef DATA_EXCHANGE_H
#define DATA_EXCHANGE_H


int send_protocol_data(int* fd, unsigned int packet_count, int packet_type, uint8_t metadata_type, struct tm* time);
int receive_protocol_data(int* fd, Header* header, Metadata* metadata);

int receive_protocol_data_new(int fd, ClientContext *ctx);

void debug_protocol(Header* header, Metadata* metadata);


#endif