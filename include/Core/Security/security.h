#ifndef SECURITY_H
#define SECURITY_H

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
int aes_encrypt(const unsigned char *plaintext, int plaintext_len,
    const unsigned char *key, const unsigned char *iv,
    unsigned char *ciphertext);

int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len,
    const unsigned char *key, const unsigned char *iv,
    unsigned char *plaintext);

void print_hex(const char *label, const unsigned char *data, int len);

#endif
