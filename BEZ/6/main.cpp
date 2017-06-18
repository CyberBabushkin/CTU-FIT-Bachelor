#include <stdlib.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>

const int KEY_LENGTH = 7;
const int BLOCK_LENGTH = 8;

/**
  * @author babusand
  */
int des(char * in, char * out, unsigned char * key, unsigned char * iv, const EVP_CIPHER* (*fn)(void), bool encrypt) {
  const int headerLen = 36;

  unsigned char header[headerLen];
  unsigned char desBlock[BLOCK_LENGTH];
  unsigned char openBlock[BLOCK_LENGTH];

  memset(desBlock, 0, BLOCK_LENGTH);
  memset(header, 0, headerLen);

  FILE * op = fopen(in, "rb");
  FILE * cp = fopen(out, "wb");

  fread((void *)header, 1, headerLen, op);
  fwrite((void *)header, 1, headerLen, cp);

  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  const char cipherName[] = "des";
  const EVP_CIPHER * cipher;

  OpenSSL_add_all_ciphers();
  cipher = EVP_get_cipherbyname(cipherName);
  if(!cipher) {
      printf("Sifra %s neexistuje.\n", cipherName);
      exit(1);
  }

  int tmpLength = 0;
  size_t read = 0;

  EVP_CipherInit_ex(&ctx, fn(), NULL, key, iv, encrypt);

  while ((read = fread(openBlock, 1, BLOCK_LENGTH, op)) > 0) {
      if (! EVP_CipherUpdate(&ctx, desBlock, &tmpLength, openBlock, read)) {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 1;
      }
      fwrite(desBlock, 1, tmpLength, cp);
  }

  if (! EVP_CipherFinal_ex(&ctx, desBlock, &tmpLength)) {
    EVP_CIPHER_CTX_cleanup(&ctx);
    return 1;
  }

  fwrite(desBlock, 1, tmpLength, cp);

  EVP_CIPHER_CTX_cleanup(&ctx);
  fclose(op);
  fclose(cp);

  return 0;
}

int ecb(char * in, char * out, unsigned char * key, bool encrypt) {
    return des(in, out, key, NULL, &EVP_des_ecb, encrypt);
}

int cbc(char * in, char * out, unsigned char * key, unsigned char * iv, bool encrypt) {
    return des(in, out, key, iv, &EVP_des_cbc, encrypt);
}

int main(void) {

    unsigned char key[KEY_LENGTH] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
    unsigned char iv[BLOCK_LENGTH] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

    char in[] = "./Mad_scientist.bmp";
    char out_ecb[] = "./Mad_scientist_ecb.bmp";
    char out_ecb_dec[] = "./Mad_scientist_ecb_dec.bmp";
    char out_cbc[] = "./Mad_scientist_cbc.bmp";
    char out_cbc_dec[] = "./Mad_scientist_cbc_dec.bmp";

    int a = ecb(in, out_ecb, key, true);
    int b = ecb(out_ecb, out_ecb_dec, key, false);
    int c = cbc(in, out_cbc, key, iv, true);
    int d = cbc(out_cbc, out_cbc_dec, key, iv, false);

    return a & b & c & d;
}