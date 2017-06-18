#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
 
int main(void) {
 
  // unsigned char ot[1024] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ0000";  // open text
  unsigned char ot[1024] = "abcdefghijklmnopqrstuvwxyz0123";  // open text
  unsigned char st[1024];  // sifrovany text
  unsigned char key[EVP_MAX_KEY_LENGTH] = "Mysterious key..";  // klic pro sifrovani
  unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor";  // inicializacni vektor
  char cipherString[1024];
  memset(cipherString, 0, 1024);

  const char cipherName[] = "RC4";
  const EVP_CIPHER * cipher;
 
  OpenSSL_add_all_ciphers();
  /* sifry i hashe by se nahraly pomoci OpenSSL_add_all_algorithms() */
  cipher = EVP_get_cipherbyname(cipherName);
  if(!cipher) {
    printf("Sifra %s neexistuje.\n", cipherName);
    exit(1);
  }
 
  int otLength = strlen((const char*) ot);
  int stLength = 0;
  int tmpLength = 0;
 
  EVP_CIPHER_CTX ctx; // struktura pro kontext
 
  printf("OT: %s\n", ot);
 
  /* Sifrovani */
  EVP_EncryptInit(&ctx, cipher, key, iv);  // nastaveni kontextu pro sifrovani
  EVP_EncryptUpdate(&ctx,  st, &tmpLength, ot, otLength);  // sifrovani ot
  stLength += tmpLength;
  EVP_EncryptFinal(&ctx, st + stLength, &tmpLength);  // dokonceni (ziskani zbytku z kontextu)
  stLength += tmpLength;
 
  printf ("Zasifrovano %d znaku.\n", stLength);

  for(int i = 0; i < stLength; i++){
    sprintf(cipherString + 2*i, "%02x", st[i]);
  }
 
  /* Desifrovani */
  EVP_DecryptInit(&ctx, cipher, key, iv);  // nastaveni kontextu pro desifrovani
  EVP_DecryptUpdate(&ctx, ot, &tmpLength,  st, stLength);  // desifrovani st
  otLength += tmpLength;
  EVP_DecryptFinal(&ctx, ot + otLength, &tmpLength);  // dokonceni (ziskani zbytku z kontextu)
  otLength += tmpLength;


 
  /* Vypsani zasifrovaneho a rozsifrovaneho textu. */
  printf("ST: %s\nDT: %s\n", cipherString, ot);
 
  exit(0);
}