#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
 
int main(int argc, char *argv[]){
 
  char text[] = "AAA";
  char hashFunction[] = "sha256";  // zvolena hashovaci funkce ("sha1", "md5" ...)
  char hashString[64];
 
  EVP_MD_CTX ctx;  // struktura kontextu
  const EVP_MD *type; // typ pouzite hashovaci funkce
  unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
  int length;  // vysledna delka hashe
 
  /* Inicializace OpenSSL hash funkci */
  OpenSSL_add_all_digests();
  /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
  type = EVP_get_digestbyname(hashFunction);
 
  /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
  if(!type) {
    printf("Hash %s neexistuje.\n", hashFunction);
    exit(1);
  }
  
  for (unsigned char c = 1; c < 255; c++)
  for (unsigned char c1 = 1; c1 < 255; c1++)
  for (unsigned char c2 = 1; c2 < 255; c2++) {
    text[0] = (char) c;
    text[1] = (char) c1;
    text[2] = (char) c2;
    /* Provedeni hashovani */
    EVP_DigestInit(&ctx, type);  // nastaveni kontextu
    EVP_DigestUpdate(&ctx, text, strlen(text));  // zahashuje text a ulozi do kontextu
    EVP_DigestFinal(&ctx, hash, (unsigned int *) &length);  // ziskani hashe z kontextu
 
    /* Vypsani vysledneho hashe */
    // printf("Hash textu \"%s\" je: ", text);
    for(int i = 0; i < length; i++){
      sprintf(hashString + 2*i, "%02x", hash[i]);
    }

    if ((hashString[0] == 'a' && hashString[1] == 'a') &&
          (hashString[2] == 'b' && hashString[3] == 'b'))  {
      printf("For text: %s (0th symbol has code %d, 1st is %d and 2nd is %d) the hash text is: \n\t%s\n", text, (int)c, (int)c1, (int)c2, hashString);
    }
    
    //printf("\n");
 
  }

  
  exit(0);
}