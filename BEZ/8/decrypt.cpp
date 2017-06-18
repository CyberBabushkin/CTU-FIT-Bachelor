#include <stdio.h>
#include <stdlib.h>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

/**
  * @author babusand
  */

int evp_decrypt(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file)
{
    EVP_CIPHER_CTX ctx;
    RSA *rsaPrivateKey = NULL;
    EVP_PKEY *evpPrivateKey = EVP_PKEY_new();

    unsigned char buffer[4096];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    size_t readBytes;
    int outLength;

    unsigned char *ek;
    unsigned int ekLength;

    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (RAND_load_file("/dev/random", 32) != 32)
        return 1;

    if (!PEM_read_RSAPrivateKey(rsa_pkey_file, &rsaPrivateKey, NULL, NULL))
        return 1;

    if (!EVP_PKEY_assign_RSA(evpPrivateKey, rsaPrivateKey))
        return 1;

    EVP_CIPHER_CTX_init(&ctx);
    ek = (unsigned char *) malloc(EVP_PKEY_size(evpPrivateKey));

    if (fread(&ekLength, sizeof ekLength, 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (ekLength > EVP_PKEY_size(evpPrivateKey))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fread(ek, ekLength, 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fread(iv, EVP_CIPHER_iv_length(EVP_aes_128_cbc()), 1, in_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (!EVP_OpenInit(&ctx, EVP_aes_128_cbc(), ek, ekLength, iv, evpPrivateKey))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    while ((readBytes = fread(buffer, 1, sizeof buffer, in_file)) > 0)
    {
        if (!EVP_OpenUpdate(&ctx, buffer_out, &outLength, buffer, readBytes))
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 1;
        }

        if (fwrite(buffer_out, outLength, 1, out_file) != 1)
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 1;
        }
    }

    if (ferror(in_file))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (!EVP_OpenFinal(&ctx, buffer_out, &outLength))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }

    if (fwrite(buffer_out, outLength, 1, out_file) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 1;
    }


    EVP_PKEY_free(evpPrivateKey);
    free(ek);

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *rsa_pkey_file;
    FILE *in_file;
    FILE *out_file;
    int rv;

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <PEM RSA Private Key File> <IN File> <OUT File>\n", argv[0]);
        exit(1);
    }

    rsa_pkey_file = fopen(argv[1], "rb");
    in_file = fopen(argv[2], "rb");
    out_file = fopen(argv[3], "wb");

    if (!rsa_pkey_file || !in_file || !out_file)
    {
        fprintf(stderr, "I/O Error!\n");
        exit(2);
    }

    rv = evp_decrypt(rsa_pkey_file, in_file, out_file);

    fclose(rsa_pkey_file);
    fclose(in_file);
    fclose(out_file);
    
    return rv;
}
