#include "allium/Sponge.h"
#include "allium/Lyra2.h"
#include "allium/sph_blake.h"
#include "allium/sph_groestl.h"
#include "allium/sph_skein.h"
#include "allium/sph_keccak.h"
#include "allium/sph_cubehash.h"

#include <string.h>

void BRAllium(void *hash, int len, const void *input)
{
    char hashA[32], hashB[32];

    sph_blake256_context ctx_blake;
    sph_keccak256_context ctx_keccak;
    sph_cubehash512_context ctx_cubehash;
    sph_skein256_context ctx_skein;
    sph_groestl256_context ctx_groestl;

    sph_blake256_init(&ctx_blake);
    sph_blake256(&ctx_blake, input, len);
    sph_blake256_close(&ctx_blake, hashA);

    sph_keccak256_init(&ctx_keccak);
    sph_keccak256(&ctx_keccak, hashA, 32);
    sph_keccak256_close(&ctx_keccak, hashB);

    LYRA2(hashA, 32, hashB, 32, hashB, 32, 1, 8, 8);

    sph_cubehash256_init(&ctx_cubehash);
    sph_cubehash256(&ctx_cubehash, hashA, 32);
    sph_cubehash256_close(&ctx_cubehash, hashB);

    LYRA2(hashA, 32, hashB, 32, hashB, 32, 1, 8, 8);

    sph_skein256_init(&ctx_skein);
    sph_skein256(&ctx_skein, hashA, 32);
    sph_skein256_close(&ctx_skein, hashB);

    sph_groestl256_init(&ctx_groestl);
    sph_groestl256(&ctx_groestl, hashB, 32);
    sph_groestl256_close(&ctx_groestl, hashA);

    memcpy(hash, hashA, 32);
}
