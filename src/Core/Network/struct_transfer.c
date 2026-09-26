#include "network.h"

//! NEW FILE FOR EACH STRUCT

//* Send Header

int send_header(int* fd, unsigned int packet_count, unsigned int packet_type)
{
    if(!fd)                 return -1;

    Header header = create_header(packet_type, packet_count, (sizeof(Packet) + AES_BLOCK_SIZE) * packet_count);

    //* Serialization du Header
    unsigned char header_s[sizeof(Header)] = {0X0};
    serialize_header(&header, header_s, sizeof(Header));

    return send_data(fd, header_s, sizeof(Header));
}

int receive_header(Header* header, int* fd)
{
    unsigned char header_s[sizeof(Header)] = {0x0};

    size_t recept_len = sizeof(Header);

    //* Reception du Header
    int received_bytes = async_receive_data(fd, header_s, &recept_len);

    //* Deserialisation du Header
    deserialize_header(header, header_s, recept_len);

    return received_bytes;
}

//* Send Packet(s)

int send_packet(int* fd, Packet* packet, const unsigned char* key, const unsigned char* iv)
{
    //* Verification depends on send_packets

    size_t max_ciphered_len = sizeof(Packet) + AES_BLOCK_SIZE;

    unsigned char ciphered_packet[sizeof(Packet) + AES_BLOCK_SIZE] = {0x0};
    prepare_packet(packet, ciphered_packet, key, iv);

    int packet_bytes = send_data(fd, ciphered_packet, max_ciphered_len);

    return packet_bytes;
}

int send_packets(int* fd, Packet* packet, unsigned int packet_count, const unsigned char* key, const unsigned char* iv)
{
    if(packet_count == 0)
    {
        return 0;
    }

    if(!fd)             return -1;
    if(!packet)         return -1;
    if(!key)            return -1;
    if(!iv)             return -1;

    int packets_bytes = 0;

    for(unsigned int i = 0; i < packet_count; i++)
    {
        packets_bytes += send_packet(fd, &packet[i], key, iv);
    }

    return packets_bytes;
}

int receive_packets(int* fd, unsigned char reception[255][sizeof(Packet) + AES_BLOCK_SIZE], unsigned int packet_count)
{
    if(packet_count == 0)
    {
        return 0;
    }

    int received_packets = 0;

    size_t packet_len = sizeof(Packet) + AES_BLOCK_SIZE;
    for(unsigned int i = 0; i < packet_count; i++)
    {
        size_t result = async_receive_data(fd, reception[i], &packet_len);
        received_packets += result == packet_len ? 1 : 0; 
        //print_hex("recv: ", reception[i], packet_len);
    }
    return received_packets;
}


//* Send Metadata

int send_metadata(int* fd, uint8_t type, struct tm* time)
{
    if(!fd)         return -1;
    
    Metadata metadata = {0x0};

    if(time)
    {
        metadata.time = *time;
        metadata.type = type;
    }else
    {
        metadata = create_metadata(type);
    }

    //* Serialization des Metadata
    unsigned char metadata_s[sizeof(Metadata)] = {0x0};
    serialize_metadata(&metadata, metadata_s, sizeof(Metadata));

    return send_data(fd, metadata_s, sizeof(Metadata));
}

int receive_metadata(Metadata* metadata, int* fd)
{
    size_t metadata_len = sizeof(Metadata);

    unsigned char metadata_s[sizeof(Metadata)] = {0x0};

    //* Reception du Header
    int result = async_receive_data(fd, metadata_s, &metadata_len);

    //* Deserialisation du Header
    deserialize_metadata(metadata_s, metadata, metadata_len);

    return result;
}
