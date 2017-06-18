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
    SSL_CTX             *ctx;
    SSL                 *ssl;
    char                req[] = "GET /student/odkazy HTTP/1.1\r\nHost: fit.cvut.cz\r\n\r\n";;
    size_t              req_len = strlen(req);
    char                hostname[] = "www.fit.cvut.cz";
    int                 port = 443;
    int                 bytes;
    char                buf[128];

    char                dest_url[] = "https://www.fit.cvut.cz/";
    X509                *cert = NULL;

    FILE *              page;
    FILE *              certFile;

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
    SSL_connect(ssl);

    /* Get the remote certificate into the X509 structure */
    cert = SSL_get_peer_certificate(ssl);
    if (cert == NULL) {
        printf("Error: Could not get a certificate from: %s.\n", dest_url);
        return 1;
    } else
        printf("Retrieved the server's certificate from: %s.\n", dest_url);

    /* Writing PEM file */
    certFile = fopen("./cert.pem", "w+b");
    PEM_write_X509(certFile, cert);
    fclose(certFile);

    /* Sending a request */
    SSL_write(ssl, req, (int)req_len);

    /* Writing to file */
    memset(buf, '\0', sizeof(buf));

    page = fopen("./page.html", "w+b");
    bytes = SSL_read(ssl, buf, sizeof(buf));
    while(bytes > 0){
        fwrite(buf, 1, (size_t) bytes, page);
        memset(buf, '\0', sizeof(buf));
        bytes = SSL_read(ssl, buf, sizeof(buf));
    }

    /* Freeing resources up */
    fclose(page);
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sd);
    SSL_CTX_free(ctx);
}