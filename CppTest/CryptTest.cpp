#include "CryptTest.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <bcrypt.h>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif // !NT_SUCCESS

static void DumpHex(unsigned char *buf, size_t bufLen)
{
    for (int i = 0; i < bufLen; i++) {
        std::fprintf(stdout, "%02X ", buf[i]);
        if ((i + 1) % 8 == 0) {
            std::fprintf(stdout, "\n");
        }
    }
    std::fprintf(stdout, "\n");
}

////////////////////////////////////////////////////////////

void CryptTest00()
{
    BCRYPT_ALG_HANDLE handle = INVALID_HANDLE_VALUE;
    NTSTATUS status = BCryptOpenAlgorithmProvider(&handle, BCRYPT_RNG_ALGORITHM, nullptr, 0);
    if (!NT_SUCCESS(status)) {
        std::fprintf(stderr, "bcrypt: open algorithm provider failed\n");
        return;
    }
    std::fprintf(stdout, "bcrypt: open algorithm provider succeeded\n");
    do {
        unsigned char buf[20];
        status = BCryptGenRandom(handle, buf, sizeof(buf), 0);
        if (!NT_SUCCESS(status)) {
            std::fprintf(stderr, "bcrypt: generate random failed\n");
            break;
        }
        DumpHex(buf, sizeof(buf));
    } while (false);
    status = BCryptCloseAlgorithmProvider(handle, 0);
    if (!NT_SUCCESS(status)) {
        std::fprintf(stderr, "bcrypt: close algorithm provider failed\n");
        return;
    }
    std::fprintf(stdout, "bcrypt: close algorithm provider succeeded\n");
}

////////////////////////////////////////////////////////////

void CryptTest01()
{
    unsigned char buf[10];
    NTSTATUS status = BCryptGenRandom(nullptr, buf, sizeof(buf), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (!NT_SUCCESS(status)) {
        std::fprintf(stderr, "generate random failed\n");
        return;
    }
    DumpHex(buf, sizeof(buf));
}

////////////////////////////////////////////////////////////
