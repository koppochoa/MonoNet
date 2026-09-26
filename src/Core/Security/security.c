
#include "security.h"

void handleErrors() 
{
    ERR_print_errors_fp(stderr);
    abort();
}

// AES-256-CBC Encryption
int aes_encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        perror("EVP_CIPHER_CTX_new");
        return -1;
    }

    // Initialisation du contexte de chiffrement avec AES-256-CBC
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        perror("EVP_EncryptInit_ex");
        return -1;
    }

    // Chiffrement
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        perror("EVP_EncryptUpdate");
        return -1;
    }
    ciphertext_len = len;

    // Finalisation du chiffrement (avec padding)
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        perror("EVP_EncryptFinal_ex");
        return -1;
    }
    ciphertext_len += len;

    // Libération du contexte
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

// AES-256-CBC Decryption
int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *decryptedtext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int decryptedtext_len;

    // Création du contexte de déchiffrement
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        perror("EVP_CIPHER_CTX_new");
        return -1;
    }

    // Initialisation du contexte de déchiffrement avec AES-256-CBC
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        perror("EVP_DecryptInit_ex");
        return -1;
    }

    // Déchiffrement des données
    if (1 != EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        perror("EVP_DecryptUpdate");
        return -1;
    }
    decryptedtext_len = len;

    // Finalisation du déchiffrement (avec padding)
    if (1 != EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        ERR_print_errors_fp(stderr);
        perror("EVP_DecryptFinal_ex");
        return -1;
    }
    decryptedtext_len += len;

    // Libération du contexte
    EVP_CIPHER_CTX_free(ctx);

    // Retourne la longueur du texte déchiffré
    return decryptedtext_len;
}

// Affiche un tableau d'octets en hexadécimal
void print_hex(const char *label, const unsigned char *data, int len) 
{
    printf("%s [", label);
    for (int i = 0; i < len; i++)
    printf("%02x", data[i]);
    printf("]\n");
}
