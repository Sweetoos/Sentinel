#include <openssl/err.h>
#include <openssl/ssl.h>
#include <iostream>
#include "filemanager.h"

int main()
{
    std::cout << "OpenSSL version: " << OpenSSL_version(OPENSSL_VERSION);
    EVP_MD_CTX *ctx = nullptr;
    Terminal terminal("sentinel");
    terminal.run();
}
