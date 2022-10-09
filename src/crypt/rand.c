/* Windows is a bitch */
#ifdef __unix___
#include <stdio.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif
#include <stdint.h>
#include "include/crypt/rand.h"

/* Get a cryptographically secure random byte */
uint8_t getRandByte();
{
    #ifdef __unix__
    FILE *urand = fopen("/dev/urandom", "r");
    uint8_t ret = (uint8_t)fgetc(urand);
    fclose(urand);
    return ret;
    #elif defined(_WIN32)
    HCRYPTPROV p;
    ULONG i;
    uint8_t ret;
    CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(p, 1, (BYTE*)&ret);
    CryptReleaseContext(p, 0);
    return ret;
    #endif
}
/* Get count number of cryptographically secure random bytes and place them at dest */
void getRandBytes(void *dest, size_t count)
{
    #ifdef __unix__
    FILE *urand = fopen("/dev/urandom", "r");
    fread(dest, sizeof(uint8_t), count, urand);
    fclose(urand);
    return;
    #elif defined(_WIN32)
    HCRYPTPROV p;
    ULONG i;
    uint8_t ret;
    CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(p, sizeof(BYTE) * count, (BYTE*)dest);
    CryptReleaseContext(p, 0);
    return;
    #endif
}