#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>

int main(int argc, char *argv[]){
    int                 sd;
    struct hostent      *host;
    struct sockaddr_in  addr;
    const SSL_METHOD    *method;
    SSL_CTX             *ctx, *ctx_new;
    SSL                 *ssl;
    char                hostname[] = "www.fit.cvut.cz";
    int                 port = 443;

    const char          *cipher_name;
    char                *allowed_ciphers;
    const SSL_CIPHER    *ssl_cipher;

    int                 i;

    OpenSSL_add_all_algorithms();

    if(SSL_library_init() < 0){
        printf("Could not initialize the OpenSSL library !\n");
        return 1;
    }

    method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    host = gethostbyname(hostname);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(in_addr_t *)(host->h_addr);

    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
        printf("Cannot connect to host %s [%s] on port %d.\n", hostname, inet_ntoa(addr.sin_addr), port);
        return 1;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sd);
    
    // Retrieval of a cipher
    SSL_connect(ssl);
    ssl_cipher = SSL_get_current_cipher(ssl);
    cipher_name = SSL_CIPHER_get_name(ssl_cipher);
    printf("Current cipher is: %s\n", cipher_name);

    /* 
     * DHE - authenticated ephemeral Diffie-Hellman key agreement
     * RSA - is the RSA algorithm
     * AES256 - the AES cipher with a key of length 256 bits
     * SHA - hashing algorithm
     */

    // Blocking it
    allowed_ciphers = (char *) calloc((char)0, 100);
    sprintf(allowed_ciphers, "ALL:!%s", cipher_name);

    printf("Setting ciphers list to \"ALL:!%s\"\n", cipher_name);

    SSL_set_cipher_list(ssl, allowed_ciphers);    

    // Printing available ciphers out
    i = 0;
    cipher_name = SSL_get_cipher_list(ssl, i++);
    printf("\nAvailable ciphers:\n");
    
    while (cipher_name != NULL) {
        printf("%s\n", cipher_name);
        cipher_name = SSL_get_cipher_list(ssl, i++);
    }
     
    // Server certificate verification
    ctx_new = SSL_CTX_new(method);
    SSL_CTX_set_default_verify_paths(ctx_new);

    SSL_shutdown(ssl);
    SSL_free(ssl);

    ssl = SSL_new(ctx_new);
    SSL_set_fd(ssl, sd);
    SSL_connect(ssl);

    printf("\nVerifying server certificate...\n");

    if (SSL_get_verify_result(ssl) == X509_V_OK) {
        printf("[SUCCESS] The certificate looks good.\n");
    } else {
        printf("[FAIL] The certificate does not look good!!!\n");
    }

    /* Freeing resources up */
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sd);
    SSL_CTX_free(ctx);
    SSL_CTX_free(ctx_new);
    free(allowed_ciphers);
}