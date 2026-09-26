#include "metadata.h"

Metadata create_metadata(uint8_t type)
{
    time_t now = time(NULL); 
    Metadata metadata = {.type = type, .time = *localtime(&now)};
    return metadata;
}

void reset_metadata(Metadata* metadata)
{
    memset(&metadata->time, 0, sizeof(struct tm));
    metadata->type = 0;
}

void show_metadata(Metadata* metadata)
{
    ColorPrint(COLOR_BLUE, "[METADATA]      ");
    printf("    TIME : [%d:%d:%d]", metadata->time.tm_hour, metadata->time.tm_min, metadata->time.tm_sec);
    printf("    TYPE : %d", metadata->type);
    printf("\n");
}

int serialize_metadata(const Metadata* metadata, unsigned char* buffer, size_t buffer_len)
{
    if(!metadata)                            return -1;
    if(!buffer)                         return -1;
    if(buffer_len < sizeof(Metadata))   return -1;

    size_t offset = 0;
    
    //* Serialization de type
    buffer[offset] = metadata->type;
    offset += sizeof(uint8_t);

    //* Sérialisation de "time" (struct tm)
    uint16_t year   = htons(metadata->time.tm_year + 1900); // Année depuis 1900, convertie en big-endian
    uint8_t month   = metadata->time.tm_mon + 1;            // Mois [1-12]
    uint8_t day     = metadata->time.tm_mday;                 // Jour du mois [1-31]
    uint8_t hour    = metadata->time.tm_hour;                // Heure [0-23]
    uint8_t minute  = metadata->time.tm_min;               // Minutes [0-59]
    uint8_t second  = metadata->time.tm_sec;               // Secondes [0-59]

    //* Sérialisation des champs de la structure tm
    memcpy(buffer + offset, &year, sizeof(year)); offset += sizeof(year);
    
    buffer[offset] = month;     offset += sizeof(month);
    buffer[offset] = day;       offset += sizeof(day);
    buffer[offset] = hour;      offset += sizeof(hour);
    buffer[offset] = minute;    offset += sizeof(minute);
    buffer[offset] = second;    offset += sizeof(second);

    return 0;
}   

int deserialize_metadata(const unsigned char* buffer, Metadata* metadata, size_t buffer_len)
{
    if(!buffer)                     return -1;
    if(!metadata)                   return -1;
    if(buffer_len != sizeof(Metadata))  return -1;

    size_t offset = 0;

    metadata->type = buffer[offset];
    offset += sizeof(uint8_t);

    uint16_t year_network;
    memcpy(&year_network, buffer + offset, sizeof(uint16_t));
    metadata->time.tm_year = ntohs(year_network) - 1900; // REMETTRE -1900
    offset += sizeof(uint16_t);

    metadata->time.tm_mon = buffer[offset] -1;  offset += sizeof(uint8_t);
    metadata->time.tm_mday = buffer[offset];    offset += sizeof(uint8_t);
    metadata->time.tm_hour = buffer[offset];    offset += sizeof(uint8_t);
    metadata->time.tm_min = buffer[offset];     offset += sizeof(uint8_t);
    metadata->time.tm_sec = buffer[offset];     offset += sizeof(uint8_t);

    return 0;
}
