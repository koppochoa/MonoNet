#include "chat.h"

void PrintTest(char* testname, bool state)
{
    ColorPrint(COLOR_BLUE, testname);
    const char* color = state ? COLOR_GREEN : COLOR_RED;
    char* message = state ? "passed" : "error";
    printf(":   ");
    ColorPrint(color, message);
    printf("\n");
}

//* Header Test
void HeaderTest()
{
    ColorPrint(COLOR_CYAN, "HEADER TESTS : \n");

    Header header = {0x0};
    header.packet_size = 10;
    header.packet_type = 9;
    header.packet_count = 3;

    unsigned char header_s[sizeof(Header)];
    serialize_header(&header, header_s, sizeof(Header));

    Header new_header = {0x0};
    deserialize_header(&new_header, header_s, sizeof(Header));

    bool test = (header.packet_size == new_header.packet_size && header.packet_type == new_header.packet_type && header.packet_count == new_header.packet_count) ? true : false;
    PrintTest("Header Test", test);
}

//* Packet Test
void PacketTest()
{
    ColorPrint(COLOR_CYAN, "PACKET TESTS : \n");

    Packet packet = {0x0};
    strcpy(packet.data, "test00");
    packet.type = 18;

    unsigned char packet_s[sizeof(Packet)];
    serialize_packet(&packet, packet_s, sizeof(Packet));

    Packet new_packet = {0x0};
    deserialize_packet(&new_packet, packet_s, sizeof(Packet));

    bool test_type = (packet.type == new_packet.type) ? true : false;
    PrintTest("Packet Type Test", test_type);

    bool test_data = strncmp(packet.data, new_packet.data, MESSAGE_SIZE) == 0;
    PrintTest("Packet Data Test", test_data);
}

//* Metadata Test
void MetadataTest()
{
    ColorPrint(COLOR_CYAN, "METADATA TESTS : \n");

    Metadata metadata = {0};
    metadata.type = 30;

    time_t now = time(NULL); // Prend l'heure actuelle
    if (now != (time_t)-1) {
        struct tm *now_tm = localtime(&now);
        if (now_tm) {
            metadata.time = *now_tm; // Copie la structure
        }
    }

    unsigned char metadata_s[sizeof(Metadata)];
    serialize_metadata(&metadata, metadata_s, sizeof(Metadata));

    usleep(1000);

    Metadata new_metadata = {0x0};
    deserialize_metadata(metadata_s, &new_metadata, sizeof(Metadata));

    bool test_type = new_metadata.type == metadata.type;
    PrintTest("Metadata type test", test_type);

    bool test_time = new_metadata.time.tm_hour == metadata.time.tm_hour && new_metadata.time.tm_year == metadata.time.tm_year;
    PrintTest("Metadata time test", test_time);
}

//* Packet Encryption Test
void PacketEncryptionTest()
{
    ColorPrint(COLOR_CYAN, "Packet Encryption TESTS : \n");

    // // Clé AES 256 bits (32 octets)
    unsigned char key_256[32] = {
        0x60, 0x3d, 0xeb, 0x10, 
        0x15, 0xca, 0x71, 0xbe, 
        0x2b, 0x73, 0xae, 0xf0, 
        0x85, 0x7d, 0x77, 0x81, 
        0x1f, 0x35, 0x94, 0x1e, 
        0x64, 0x92, 0x1b, 0x8a, 
        0x43, 0x8f, 0x6a, 0x0a, 
        0x68, 0x7b, 0x8d, 0x12
    };
    
    unsigned char iv[16] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
    };
    

    Packet packet = {0x0};
    strcpy(packet.data,"eeeeeeee");
    packet.type = 22;

    unsigned char packet_s[sizeof(Packet)];
    serialize_packet(&packet, packet_s, sizeof(Packet));

    unsigned char packet_s_c[sizeof(Packet) + AES_BLOCK_SIZE];
    aes_encrypt(packet_s, sizeof(Packet), key_256, iv, packet_s_c);

    // //!----------

    size_t newLen = sizeof(Packet) + (AES_BLOCK_SIZE - (sizeof(Packet) % AES_BLOCK_SIZE));

    Packet new_packet = {0x0};
    unsigned char new_packet_s[sizeof(Packet)];
    aes_decrypt(packet_s_c, newLen, key_256, iv, new_packet_s);

    int result = deserialize_packet(&new_packet, new_packet_s, sizeof(Packet));

    bool test_decryption = result != -1;
    PrintTest("Packet Encryption decrypt test", test_decryption);

    bool test_packet= strcmp(packet.data, new_packet.data) == 0 && packet.type == new_packet.type;
    PrintTest("Packet Encryption packet test", test_packet);
}

void RunTests()
{
    HeaderTest();
    PacketTest();
    MetadataTest();
    PacketEncryptionTest();
}