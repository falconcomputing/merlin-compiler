/*
 *   Byte-oriented AES-256 implementation.
 *   All lookup tables replaced with 'on the fly' calculations.
 */
#include "support.h"

typedef struct {
  uint8_t key[32];
  uint8_t enckey[32];
  uint8_t deckey[32];
} aes256_context;

#ifdef MCC_SIM
#define BATCH (1*1024*1024)
#else
#define BATCH (16*1024*1024)
#endif

#define TILE_SIZE (1024*4)

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  aes256_context ctx;
  uint8_t k[32];
  uint8_t buf[16];
};

