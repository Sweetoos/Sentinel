#include <openssl/err.h>
#include <openssl/ssl.h>
#include <iostream>

int main()
{
    std::cout << "OpenSSL version: " << OpenSSL_version(OPENSSL_VERSION);
    EVP_MD_CTX *ctx = nullptr;
}
