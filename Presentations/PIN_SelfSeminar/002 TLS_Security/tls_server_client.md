**Table of Contents**
- [tls\_server.c](#tls_serverc)
- [tls\_client.c](#tls_clientc)

# tls_server.c
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <signal.h>

/*
 * CHOOSE 1-way / 2-way Handshake
 * uncomment ONE_WAY_HANDSHAKE 	:: 1-way handshake
 * comment ONE_WAY_HANDSHAKE	:: 2-way Handshake
 */
// #define ONE_WAY_HANDSHAKE

#define PORT          4433                // Server Port
#define MAX_BUF       2048                // Message Max Length

#define CA_FILE       "certs/ca/ca.crt"             // CA CERTIFICATE FILE PATH
#define CRT_FILE      "certs/server/server.crt"     // HOST CERTIFICATE FILE PATH
#define KEY_FILE      "certs/server/server.key"      // HOST KEY FILE PATH

/* TLS1.2 CIPHERSUITE */
#define CIPHERSUITE "ECDHE-ECDSA-ARIA128-GCM-SHA256"

//Setting Server configuration
int create_socket(void)
{
  int sockfd;
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("Unable to create socket\n");
    return -1;
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
  {
    printf("setsockopt(SO_REUSEADDR) failed");
    return -1;
  }

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    printf("Unable to bind");
    return -1;
  }

  if (listen(sockfd, 1) < 0)
  {
    printf("Unable to listen");
    return -1;
  }

  return sockfd;
}

//Initialize OpenSSL and load Engine
void init_openssl()
{
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();
}

//Finish OpenSSL
void cleanup_openssl()
{
  EVP_cleanup();
}

// Create Server Context
SSL_CTX *create_context()
{
  SSL_CTX *ctx;

  // if((ctx = SSL_CTX_new(SSLv23_method())) == NULL)
  if((ctx = SSL_CTX_new(SSLv23_server_method())) == NULL)
  {
    printf("Unable to create SSL context");
    return NULL;
  }

  return ctx;
}

//Setting TLS Configuration
void configure_context(SSL_CTX *ctx)
{
  //set TLS version
  SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);
  SSL_CTX_set_max_proto_version(ctx, TLS1_3_VERSION);

  /*
   * Set supported signature algorithm
   * You Have to setting ECDSA_SHA256:EC-KCDSA
   * to use ECDSA based Certificate and EC-KCDSA base Certificate
   */
  SSL_CTX_set1_sigalgs_list(ctx, "ECDSA+SHA256:EC-KCDSA");

  /*
   * Set ECC Curve
   */
  SSL_CTX_set1_curves_list(ctx, "P-256");

  /*
   * Set Handshake Method
   */
#if defined(ONE_WAY_HANDSHAKE)
  SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
#else
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
#endif

  //Set CA Certificate File Path
  if (!SSL_CTX_load_verify_locations(ctx, CA_FILE, NULL))
  {
    printf("Error loading CA certificate\n");
    exit(EXIT_FAILURE);
  }

  //Set Host Certificate
  if (SSL_CTX_use_certificate_file(ctx, CRT_FILE, SSL_FILETYPE_PEM) <= 0)
  {
    printf("Error loading Host certificate\n");
    exit(EXIT_FAILURE);
  }

  //Set Host Key
  if (SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0)
  {
    printf("Error loading key file\n");
    exit(EXIT_FAILURE);
  }

  if (SSL_CTX_set_cipher_list(ctx, CIPHERSUITE) != 1) {
    printf("Unable to set cipher list\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv)
{
  SSL *ssl;
  int client;
  int sock;
  SSL_CTX *ctx;

  char resp[MAX_BUF];
  char req[MAX_BUF];
  pid_t cpid;

  init_openssl();
  ctx = create_context();
  configure_context(ctx);

  sock = create_socket();

  while (1)
  {   
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    printf("Waiting for new connection...\n");

    client = accept(sock, (struct sockaddr *)&addr, &len);
    if (client < 0)
    {
      perror("Unable to accept");
      return -1;
    }
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client);

    if (SSL_accept(ssl) <= 0)
    {
      ERR_print_errors_fp(stderr);
    }
    else
    { /* send message to the server*/
      cpid = fork();
      if (cpid == 0)
      {
        while (1)
        {
          len = SSL_read(ssl, resp, MAX_BUF);
          if (len <= 0)
          {
            kill(getpid(), SIGKILL);
          }
          resp[len] = '\0';
          printf("\n[CLIENT] : %s\nSend to Client: ", resp);
          fflush(stdout);
        }
      }
      else
      {/* read response from server and print to stdout */
        int status;
        while ((waitpid(cpid, &status, WNOHANG) == 0))
        {   
          printf("\nSend to Client: ");
          scanf("%[^\n]", req);
          getchar();
          SSL_write(ssl, req, strlen(req));
        }
      }
      SSL_shutdown(ssl);
      SSL_free(ssl);
      close(client);
    }
    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
  }

  return 0;
}
```

# tls_client.c
```c
#include "stdio.h" // printf(), exit()
#include "string.h"

#include "openssl/bio.h"
#include "openssl/err.h"
#include "openssl/ssl.h"
#include <openssl/engine.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


/* CHOOSE 1-way / 2-way Handshake
 * uncomment ONE_WAY_HANDSHAKE	:: 1-way Handshake
 * comment ONE_WAY_HANDSHAKE	:: 2-way Handshake
 */
// #define ONE_WAY_HANDSHAKE 

#define SERVER_IP      "127.0.0.1"        // SERVER IP
#define PORT          4433                // SERVER PORT
#define MAX_BUF       2048                //Message Max Length

#define CA_FILE       "certs/ca/ca.crt"           //CA CERTIFICATE FILE PATH
#define CRT_FILE      "certs/client/client.crt"   //HOST CERTIFICATE FILE PATH
#define KEY_FILE      "certs/client/client.key"    //HOST KEY FILE PATH

/* TLS1.2 CIPHERSUITE */
#define CIPHERSUITE "ECDHE-ECDSA-ARIA128-GCM-SHA256"

//PROTO_VERSION is TLS Version to use when communicating with the server
#if defined(TLS1_3)
#define PROTO_VERSION TLS1_3_VERSION
#else
#define PROTO_VERSION TLS1_2_VERSION
#endif

//Setting Server configuration
int create_socket(SSL *ssl)
{
  int sockfd;
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "ERROR : invalid address\n");
    return -1;
  }

  if(inet_pton(AF_INET, SERVER_IP, &addr.sin_addr) != 1){
    fprintf(stderr, "ERROR : failed to create the socket\n");
    return 1;
  }
  if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    fprintf(stderr, "ERROR:  failed to connect\n");
    return 1;
  }

  SSL_set_fd(ssl, sockfd);
  SSL_connect(ssl);
}

//Initialize OpenSSL
void init_openssl()
{
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();
}

//Finish OpenSSL
void cleanup_openssl()
{
  EVP_cleanup();
}

// Create Client Context
SSL_CTX *create_context()
{
  SSL_CTX *ctx;

  // if((ctx = SSL_CTX_new(SSLv23_method())) == NULL)
  if((ctx = SSL_CTX_new(SSLv23_client_method())) == NULL)
  {
    printf("Unable to create SSL context");
    return NULL;
  }
  return ctx;
}

//Setting TLS Configuration
void configure_context(SSL_CTX *ctx)
{
  //set TLS version
  SSL_CTX_set_min_proto_version(ctx, PROTO_VERSION);
  SSL_CTX_set_max_proto_version(ctx, PROTO_VERSION);

  /*
   * Set supported signature algorithm
   * You Have to setting ECDSA_SHA256:EC-KCDSA
   * to use ECDSA based Certificate and EC-KCDSA base Certificate
   */
  SSL_CTX_set1_sigalgs_list(ctx, "ECDSA+SHA256:EC-KCDSA");

  /*
   * Set ECC Curve
   */
  SSL_CTX_set1_curves_list(ctx, "P-256");

  /*
   * Set Handshake Method
   */
#if defined(ONE_WAY_HANDSHAKE)
  SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
#else
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
#endif

  //Set CA Certificate File Path
  if (!SSL_CTX_load_verify_locations(ctx, CA_FILE, NULL))
  {
    fprintf(stderr, "Error loading trust store into SSL context\n");
    ERR_print_errors_fp(stderr);
    exit(1);
  }

  //Set Host Certificate and Key File Path
#if !defined(ONE_WAY_HANDSHAKE)
  if (SSL_CTX_use_certificate_file(ctx, CRT_FILE, SSL_FILETYPE_PEM) <= 0)
  {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  if(SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <=0)
  {
    fprintf(stderr, "Private key does not match the public certificate\n");
    abort();
  }
#endif
}

int main()
{
  SSL *ssl;
  SSL_CTX *ctx;

  int sock;

  char req[MAX_BUF]; // message to send
  char resp[MAX_BUF]; // message to read
  int len;
  pid_t cpid;


  /* Set up the OpenSSL library */
  init_openssl();

  ctx = create_context();
  configure_context(ctx);
  SSL_CTX_set_cipher_list(ctx, CIPHERSUITE);

  ssl = SSL_new(ctx);



  //set Ciphersuite
#if defined(TLS1_3)
  SSL_set_ciphersuites(ssl, CIPHERSUITE);
#else
  // SSL_set_cipher_list(ssl, CIPHERSUITE);
#endif

  create_socket(ssl);

  cpid = fork();
  if (cpid == 0)
  {
    while (1)
    {
      len = SSL_read(ssl, resp, MAX_BUF);
      if (len <= 0)
      {
        kill(getpid(), SIGKILL);
      }
      resp[len] = '\0';
      printf("\n[SERVER] : %s\nSend to Server: ", resp);
      fflush(stdout);
    }
  }
  else
  {/* read response from server and print to stdout */
    int status;
    while ((waitpid(cpid, &status, WNOHANG) == 0))
    {   
      printf("\nSend to server: ");
      scanf("%[^\n]", req);
      getchar();
      SSL_write(ssl, req, strlen(req));
    }
  }
  /* close TCP/IP connection and free bio and context */
  SSL_CTX_free(ctx);

  cleanup_openssl();

  return 0;
}
```