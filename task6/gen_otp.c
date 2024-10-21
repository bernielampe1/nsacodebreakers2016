#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static char *sig = "\x39\x58\x5a\xfd\x7f\x50\xe4\xa7\xcf\x65\x4b\x3d\xbd\x0c\x4b\x65\xcd\x59\x35\x59\x7a\x17\x5b\x53\x4e\xd0\x12\xef\x98\x08\xc1\xe5";

int main() {
    time_t t = time(0);
    unsigned tmp = time(0) / 0x1e - 1;

    mdctx = EVP_MD_CTX_create();
    key = EVP_PKEY_new_mac_key(0x357, 0, sig, strlen(sig));
    EVP_DigestSignInit(mdctx, 0, EVP_sha1(), 0, key);
    EVP_DigestUpdate(mdctx);
    EVP_digestSignFinal(mdctx, &sig_charptr, &sig_len);
    r = EVP_MD_CTX_destroy(mdctx);

    if (r != 1 || sig_len != 0x14) return -1;

    return 0;
}

