
#include "data_exchange.h"

#include "network.h"


//* Send Protocol Data

//old
int send_protocol_data(int* fd, unsigned int packet_count, int packet_type, uint8_t metadata_type, struct tm* time)
{
    //* Envoi du Header
    int header_bytes = send_header(fd, packet_count, packet_type);
    
    //* Envoi des metadatas
    int metadata_bytes = send_metadata(fd, metadata_type, time);

    //log_client(WARNING, "PROTOCOL : %d", header_bytes + metadata_bytes);
    
    return header_bytes + metadata_bytes;
}

//* Receive Protocol Data
int receive_protocol_data(int* fd, Header* header, Metadata* metadata)
{
    //* Reception du Header
    int header_bytes = receive_header(header, fd);

    //* Reception des Metadata
    int metadata_bytes = receive_metadata(metadata, fd);

    return header_bytes + metadata_bytes;
}

int receive_protocol_data_new(int fd, ClientContext *ctx) 
{
    ssize_t n;

    int errcode;

    if (ctx->step == RECV_HEADER) {
        //n = recv(fd, ((uint8_t*)&ctx->header) + ctx->bytes_received, sizeof(Header) - ctx->bytes_received, 0);
        ctx->can_read = false;
        n = async_receive_data_partial(&fd, ctx->header_container, sizeof(Header), ctx->bytes_received, &errcode);
        if (n < 0) {
            fprintf(stderr, "Error while receiving metadata (errno=%d): %s\n", errcode, strerror(errcode));
            return -1;
        }

        //printf("recv %ld bytes à l'étape %d\n", n, ctx->step);

        if (n <= 0) return -1;
        ctx->bytes_received += n;

        if (ctx->bytes_received == sizeof(Header)) 
        {
            ctx->step = RECV_METADATA;
            ctx->bytes_received = 0;
            deserialize_header(&ctx->header, ctx->header_container, sizeof(Header));

        }

        return 0; // pas encore tout reçu
    }

    if (ctx->step == RECV_METADATA) {
        //n = recv(fd, ((uint8_t*)&ctx->metadata) + ctx->bytes_received, sizeof(Metadata) - ctx->bytes_received, 0);
        //n = receive_metadata(&ctx->metadata, &fd);
        n = async_receive_data_partial(&fd, ctx->metadata_container, sizeof(Metadata), ctx->bytes_received, &errcode);
        if (n < 0) {
            fprintf(stderr, "Error while receiving metadata (errno=%d): %s\n", errcode, strerror(errcode));
            return -1;
        }
        //printf("recv %ld bytes à l'étape %d\n", n, ctx->step);

        
        if (n <= 0) return -1;
        ctx->bytes_received += n;

        if (ctx->bytes_received == sizeof(Metadata)) 
        {
            deserialize_metadata(ctx->metadata_container,&ctx->metadata, sizeof(Metadata));
            ctx->bytes_received = 0;

            if(ctx->header.packet_count == 0)
            {
                ctx->step = RECV_HEADER;
                
                return 1; //* tout est recu
            }
            else
            {
                ctx->step = RECV_PACKET;
            }

        }
        return 0;
    }

    if(ctx->step == RECV_PACKET)
    {
        n = async_receive_data_partial(
            &fd,
            ctx->packets[ctx->packet_index],
            ctx->header.packet_size,
            ctx->bytes_received,
            &errcode
        );
        if (n < 0) {
            fprintf(stderr, "Error while receiving metadata (errno=%d): %s\n", errcode, strerror(errcode));
            return -1;
        }

        //printf("recv %ld bytes à l'étape %d\n", n, ctx->step);

        if (n <= 0) return -1;
        ctx->bytes_received += n;

        if (ctx->bytes_received == ctx->header.packet_size) 
        {
            ctx->bytes_received = 0;
            ctx->packet_index++;
            
            if (ctx->packet_index < ctx->header.packet_count) 
            {
                return 0;
            }

            ctx->step = RECV_HEADER;
            ctx->packet_index = 0;
            ctx->can_read = true;
            return 1;
        }
    }
    return -1; // état inconnu
}

void debug_protocol(Header* header, Metadata* metadata)
{
    char header_data[100];
    snprintf(header_data, 100,      "   TYPE %d     SIZE %ld    COUNT %d", header->packet_type, header->packet_size, header->packet_count);

    char metadata_data[100];
    snprintf(metadata_data, 100,    "   TYPE %d     TIME [%d:%d:%d]", metadata->type, metadata->time.tm_hour, metadata->time.tm_min, metadata->time.tm_sec);

    printf("******************************************************************\n");
    printf("|   ");ColorPrint(COLOR_RED, "HEADER        :");ColorPrint(COLOR_BLUE, header_data);    printf("|\n");
    printf("------------------------------------------------------------------\n");
    printf("|   ");ColorPrint(COLOR_RED, "METADATA      :");ColorPrint(COLOR_BLUE, metadata_data);  printf("|\n");
    printf("******************************************************************\n");

}






