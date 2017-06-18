#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

/**
  * @author babusand
  */

int evp_encrypt(FILE *rsaPublicKeyFile, FILE *inFile, FILE *outFile)
{
    EVP_CIPHER_CTX ctx;
    RSA *rsaPublicKey = NULL;
    EVP_PKEY *evpPrivateKey = EVP_PKEY_new();

    unsigned char buffer[4096];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    size_t readBytes;
    int outLength;

    unsigned char *ek = NULL;
    int ekLength;

    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (RAND_load_file("/dev/random", 32) != 32)
        return 1;

    if (!PEM_read_RSA_PUBKEY(rsaPublicKeyFile, &rsaPublicKey, NULL, NULL))
        return 2;

    if (!EVP_PKEY_assign_RSA(evpPrivateKey, rsaPublicKey))
        return 3;

    EVP_CIPHER_CTX_init(&ctx);
    ek = (unsigned char *) malloc(EVP_PKEY_size(evpPrivateKey));

    if (!EVP_SealInit(&ctx, EVP_aes_128_cbc(), &ek, &ekLength, iv, &evpPrivateKey, 1))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 4;
    }

    if (fwrite(&ekLength, sizeof ekLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 5;
    }

    if (fwrite(ek, ekLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 6;
    }

    if (fwrite(iv, EVP_CIPHER_iv_length(EVP_aes_128_cbc()), 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 7;
    }

    while ((readBytes = fread(buffer, 1, sizeof buffer, inFile)) > 0)
    {
        if (!EVP_SealUpdate(&ctx, buffer_out, &outLength, buffer, readBytes))
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 8;
        }

        if (fwrite(buffer_out, outLength, 1, outFile) != 1)
        {
            EVP_PKEY_free(evpPrivateKey);
            free(ek);
            return 9;
        }
    }

    if (ferror(inFile))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 10;
    }

    if (!EVP_SealFinal(&ctx, buffer_out, &outLength))
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 11;
    }

    if (fwrite(buffer_out, outLength, 1, outFile) != 1)
    {
        EVP_PKEY_free(evpPrivateKey);
        free(ek);
        return 12;
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
        fprintf(stderr, "Usage: %s <PEM RSA Public Key File> <IN File> <OUT File>\n", argv[0]);
        exit(1);
    }

    rsa_pkey_file = fopen(argv[1], "rb");
    in_file = fopen(argv[2], "rb");
    out_file = fopen(argv[3], "wb");

    if (rsa_pkey_file == NULL || in_file == NULL || out_file == NULL)
    {
        fprintf(stderr, "I/O Error!\n");
        return 1;
    }

    rv = evp_encrypt(rsa_pkey_file, in_file, out_file);

    fclose(rsa_pkey_file);
    fclose(in_file);
    fclose(out_file);
    return rv;
}
