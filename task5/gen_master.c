#include<err.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "openssl/ssl.h"
#include "openssl/evp.h"

int main(int argc, char **argv)
{
    EVP_MD_CTX *mdctx;
    unsigned char *digest = calloc(0x20, 1);
    unsigned int digest_len;
    int i, j;

    if (argc != 2) {
        fprintf(stderr, "Usage: gen_master filename\n");
        return 1;
    }

    srand(time(0));
    for(i = 0; i < 0x20; i += 4)
        *(int*)(digest+i) = rand();

    if ((mdctx = EVP_MD_CTX_create()) == NULL)
        err(1, "Error: could not create context");

    for(j = 0; j < 0x400; j++)
    {
        if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
            err(1, "Error: could not create context");

        if (EVP_DigestUpdate(mdctx, digest, 0x20) != 1)
            err(1, "Error: digest update failed");

        if (EVP_DigestFinal_ex(mdctx, digest, &digest_len) != 1)
            err(1, "Error: digest final stopped");

        if (digest_len != 0x20)
            err(1, "Error: invalid digest size");
    }

    EVP_MD_CTX_destroy(mdctx);

    FILE *fd = fopen(argv[1], "wb");
    fwrite(digest, 0x20, 1, fd);
    fclose(fd);

    return 0;
}

