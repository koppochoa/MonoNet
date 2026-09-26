CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -Iinclude/Core -Iinclude/Core/Client -Iinclude/Core/Server \
-Iinclude/Utils -Iinclude/Core/Network -Iinclude/Security -Iinclude/Types -Iinclude/tests -I/usr/include/openssl

OPENSSL = $(shell brew --prefix openssl@3)



CFLAGS= -Wall -Wextra -O2 -Iinclude -Iinclude/Core -Iinclude/Core/Types \
	       -Iinclude/Core/Utils -I$(OPENSSL)/include \
	       -Iinclude/Core/Network -Iinclude/Core/Security

CFLAGS_CLIENT= $(CFLAGS) -Iinclude/client
CFLAGS_SERVER= $(CFLAGS) -Iinclude/server 

LDFLAGS = -L$(OPENSSL)/lib -lssl -lcrypto -g

SRC_CLIENT = $(shell find src/Core src/client -name '*.c')
SRC_SERVER = $(shell find src/Core src/server -name '*.c')

OBJ_CLIENT = $(patsubst src/%.c, client_build/%.o, $(SRC_CLIENT))
OBJ_SERVER = $(patsubst src/%.c, server_build/%.o, $(SRC_SERVER))

CLIENT = mono_client
SERVER = mono_server

client: $(CLIENT)
server: $(SERVER)

all: client server

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CLFLAGS_CLIENT) -g -o $@ $^ $(LDFLAGS)

client_build/%.o: src/%.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS_CLIENT) -g -c $< -o $@

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS_SERVER) -g -o $@ $^ $(LDFLAGS)

server_build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS_SERVER) -g -c $< -o $@

clean:
	rm -rf client_build server_build $(CLIENT) $(SERVER)

.PHONY: all clean build client server
