#include "serializer.h"
// Header
// unsigned char* Serialize_Header(const Header* header) 
// {
//     unsigned char* buffer = malloc(sizeof(Header));
//     if (!buffer) return NULL;

//     buffer[0] = (unsigned char)(header->packet_type & 0xFF);

//     buffer[1] = (header->packet_size >> 24) & 0xFF;
//     buffer[2] = (header->packet_size >> 16) & 0xFF;
//     buffer[3] = (header->packet_size >> 8) & 0xFF;
//     buffer[4] = (header->packet_size) & 0xFF;

//     return buffer;
// }



// Message

// unsigned char* Serialize_Message(const Message* msg) 
// {
//     unsigned char* buffer = malloc(sizeof(Message));
//     if (!buffer) return NULL;
//     else
//     {
//         memset(buffer, 0, sizeof(Message));
//     }

//     size_t offset = 0;

//     // Sérialisation de "type"
//     buffer[offset] = msg->type;
//     offset += sizeof(msg->type);

//     // Sérialisation de "message"
//     memcpy(buffer + offset, msg->message, packet_size);
//     offset += packet_size;

//     // Sérialisation de "time" (struct tm)
//     uint16_t year = htons(msg->time.tm_year + 1900); // Année depuis 1900, convertie en big-endian
//     uint8_t month = msg->time.tm_mon + 1;            // Mois [1-12]
//     uint8_t day = msg->time.tm_mday;                 // Jour du mois [1-31]
//     uint8_t hour = msg->time.tm_hour;                // Heure [0-23]
//     uint8_t minute = msg->time.tm_min;               // Minutes [0-59]
//     uint8_t second = msg->time.tm_sec;               // Secondes [0-59]

//     // Sérialisation des champs de la structure tm
//     memcpy(buffer + offset, &year, sizeof(year)); offset += sizeof(year);
//     buffer[offset] = month; offset += sizeof(month);
//     buffer[offset] = day; offset += sizeof(day);
//     buffer[offset] = hour; offset += sizeof(hour);
//     buffer[offset] = minute; offset += sizeof(minute);
//     buffer[offset] = second; offset += sizeof(second);

//     return buffer; // À free() par l'appelant

// }

    // if(!msg)                            return -1;
    // if(!buffer)                         return -1;
    // if(buffer_len != sizeof(Message))   return -1;

    // memset(buffer, 0, sizeof(Message));

    // size_t offset = 0;

    // // Sérialisation de "type"
    // buffer[offset] = msg->type;
    // offset += sizeof(msg->type);

    // // Sérialisation de "message"
    // memcpy(buffer + offset, msg->message, packet_size);
    // offset += packet_size;

    // // Sérialisation de "time" (struct tm)
    // uint16_t year = htons(msg->time.tm_year + 1900); // Année depuis 1900, convertie en big-endian
    // uint8_t month = msg->time.tm_mon + 1;            // Mois [1-12]
    // uint8_t day = msg->time.tm_mday;                 // Jour du mois [1-31]
    // uint8_t hour = msg->time.tm_hour;                // Heure [0-23]
    // uint8_t minute = msg->time.tm_min;               // Minutes [0-59]
    // uint8_t second = msg->time.tm_sec;               // Secondes [0-59]

    // // Sérialisation des champs de la structure tm
    // memcpy(buffer + offset, &year, sizeof(year)); offset += sizeof(year);
    // buffer[offset] = month; offset += sizeof(month);
    // buffer[offset] = day; offset += sizeof(day);
    // buffer[offset] = hour; offset += sizeof(hour);
    // buffer[offset] = minute; offset += sizeof(minute);
    // buffer[offset] = second; offset += sizeof(second);

// Message* Deserialize_Message(const unsigned char* serialized_msg) 
// {
//     if (!serialized_msg) return NULL;

//     Message* msg = malloc(sizeof(Message));
//     if (!msg) return NULL;

//     unsigned int offset = 0;

//     // Désérialiser 'type'
//     msg->type = serialized_msg[offset];
//     offset += sizeof(msg->type);

//     // Désérialiser 'message'
//     memcpy(msg->message, serialized_msg + offset, packet_size);
//     offset += packet_size;

//     // Désérialiser 'time' (struct tm)
//     // Année
//     uint16_t year;
//     memcpy(&year, serialized_msg + offset, sizeof(year));
//     msg->time.tm_year = ntohs(year) - 1900; // Convertir à partir de 1900
//     offset += sizeof(year);

//     // Mois
//     msg->time.tm_mon = serialized_msg[offset] - 1; // Mois [0-11]
//     offset += sizeof(uint8_t);

//     // Jour
//     msg->time.tm_mday = serialized_msg[offset];
//     offset += sizeof(uint8_t);

//     // Heure
//     msg->time.tm_hour = serialized_msg[offset];
//     offset += sizeof(uint8_t);

//     // Minute
//     msg->time.tm_min = serialized_msg[offset];
//     offset += sizeof(uint8_t);

//     // Seconde
//     msg->time.tm_sec = serialized_msg[offset];
//     offset += sizeof(uint8_t);

//     return msg; // À free() après utilisation

// }

    // if(!msg)                                    return -1;
    // if(!serialized_msg)                         return -1;
    // if(serialized_msg_len != sizeof(Message))   return -1;

    // unsigned int offset = 0;

    // // Désérialiser 'type'
    // msg->type = serialized_msg[offset];
    // offset += sizeof(msg->type);

    // // Désérialiser 'message'
    // memcpy(msg->message, serialized_msg + offset, packet_size);
    // offset += packet_size;

    // // Désérialiser 'time' (struct tm)
    // // Année
    // uint16_t year;
    // memcpy(&year, serialized_msg + offset, sizeof(year));
    // msg->time.tm_year = ntohs(year) - 1900; // Convertir à partir de 1900
    // offset += sizeof(year);

    // // Mois
    // msg->time.tm_mon = serialized_msg[offset] - 1; // Mois [0-11]
    // offset += sizeof(uint8_t);

    // // Jour
    // msg->time.tm_mday = serialized_msg[offset];
    // offset += sizeof(uint8_t);

    // // Heure
    // msg->time.tm_hour = serialized_msg[offset];
    // offset += sizeof(uint8_t);

    // // Minute
    // msg->time.tm_min = serialized_msg[offset];
    // offset += sizeof(uint8_t);

    // // Seconde
    // msg->time.tm_sec = serialized_msg[offset];
    // offset += sizeof(uint8_t);

// Ciphered_Message

// unsigned char* Serialize_Cipherer_Message(const Ciphered_Message* msg, size_t* out_size) {
//     *out_size = sizeof(uint32_t) + msg->ciphered_len;

//     unsigned char* buffer = malloc(*out_size);
//     if (!buffer) return NULL;

//     // Convertir ciphered_len en big endian (network byte order)
//     uint32_t len_net = htonl(msg->ciphered_len);

//     // Copier la taille
//     memcpy(buffer, &len_net, sizeof(uint32_t));

//     // Copier le contenu
//     memcpy(buffer + sizeof(uint32_t), msg->ciphered, msg->ciphered_len);

//     return buffer;
// }

// Fonction pour convertir size_t en Big-endian
void to_big_endian(size_t value, unsigned char* buffer)
{
    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        buffer[i] = (value >> ((sizeof(size_t) - 1 - i) * 8)) & 0xFF;
    }
}

// // Fonction pour convertir Big-endian en size_t
// size_t from_big_endian(const unsigned char* buffer)
// {
//     size_t value = 0;
//     // for (size_t i = 0; i < sizeof(size_t); ++i)
//     // {
//     //     value |= ((size_t)buffer[i] << ((sizeof(size_t) - 1 - i) * 8));
//     // }
//     return value;
// }

// Fonction de sérialisation
// int serialize_Ciphered_Message(const Ciphered_Message* msg, unsigned char* buffer)
// {
//     // size_t offset = 0;

//     // // Sérialisation de "size" (en Big-endian)
//     // to_big_endian(msg->ciphered_len, buffer + offset);
//     // offset += sizeof(size_t);

//     // // Sérialisation de "ciphered_message"
//     // memcpy(buffer + offset, msg->ciphered, msg->ciphered_len);
    
//     return 0;
// }

// Fonction de désérialisation
// int deserialize_Ciphered_Message(const unsigned char* buffer, Ciphered_Message* msg)
// {
//     // size_t offset = 0;

//     // // Désérialisation de "size" (en Big-endian -> Little-endian)
//     // msg->ciphered_len = from_big_endian(buffer + offset);
//     // offset += sizeof(size_t);

//     // // Vérification de la longueur
//     // if (msg->ciphered_len > CIPHERED_LEN) {
//     //     return -1;  // Erreur : taille trop grande
//     // }

//     // // Désérialisation de "ciphered_message"
//     // memcpy(msg->ciphered, buffer + offset, msg->ciphered_len);
    
//     return 0;  // Succès
// }


// int serialize_CiphererMessage(const Ciphered_Message* msg, unsigned char* buffer, size_t buffer_len) 
// {
//     if (!msg || !buffer || buffer_len < sizeof(size_t) + msg->ciphered_len) {
//         return;  // Vérification de la taille du buffer
//     }

//     memset(buffer, 0, CIPHERED_LEN);

//     size_t offset = 0;

//     // Sérialisation de "size" (en toute sécurité)
//     memcpy(buffer + offset, &msg->ciphered_len, sizeof(size_t));
//     offset += sizeof(size_t);

//     // Sérialisation de "ciphered_message"
//     memcpy(buffer + offset, msg->ciphered, msg->ciphered_len);


//     // // Convertir ciphered_len en big endian (network byte order)
//     // size_t len_net = htonl(msg->ciphered_len);

//     // // Copier la taille
//     // memcpy(buffer, &len_net, sizeof(size_t));

//     // // Copier le contenu chiffré
//     // memcpy(buffer + sizeof(size_t), msg->ciphered, msg->ciphered_len);
// }


// // Ciphered_Message Deserialize_Cipherer_Message(const unsigned char* buffer) {
// //     Ciphered_Message msg;

// //     // Lire et convertir ciphered_len (big endian -> host order)
// //     uint32_t len_net;
// //     memcpy(&len_net, buffer, sizeof(uint32_t));
// //     msg.ciphered_len = ntohl(len_net);

// //     // Allouer et copier le contenu
// //     msg.ciphered = malloc(msg.ciphered_len);
// //     if (!msg.ciphered) {
// //         msg.ciphered_len = 0;
// //         return msg; // retourne struct vide si erreur
// //     }

// //     memcpy(msg.ciphered, buffer + sizeof(uint32_t), msg.ciphered_len);

// //     return msg;
// // }

// int deserialize_CiphererMessage(Ciphered_Message* message, const unsigned char* buffer, size_t serialized_msg_len) 
// {







//     // if(!message) return -1;

//     // // Lire et convertir ciphered_len (big endian -> host order)
//     // size_t len_net;
//     // memcpy(&len_net, buffer, sizeof(size_t));
//     // message->ciphered_len = ntohl(len_net);

//     // if(serialized_msg_len < sizeof(size_t) + message->ciphered_len)    return -1;

//     // message->ciphered = (unsigned char*)buffer + sizeof(size_t);

//     // message->ciphered[message->ciphered_len] = '\0';

//     return 0;
// }
