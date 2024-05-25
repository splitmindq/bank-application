#ifndef BANK_SHA256_H
#define BANK_SHA256_H
#include <stddef.h>
#include <stdint.h>

#define SHA256_HEX_SIZE (64 + 1)
#define SHA256_BYTES_SIZE 32

void sha256_hex(const void *src, size_t n_bytes, char *dst_hex65);

void sha256_bytes(const void *src, size_t n_bytes, void *dst_bytes32);

typedef struct sha256 {
    uint32_t state[8];
    uint8_t buffer[64];
    uint64_t n_bits;
    uint8_t buffer_counter;
} sha256;

void sha256_init(struct sha256 *sha);
void sha256_append(struct sha256 *sha, const void *data, size_t n_bytes);
void sha256_finalize_hex(struct sha256 *sha, char *dst_hex65);
void sha256_finalize_bytes(struct sha256 *sha, void *dst_bytes32);

#endif //BANK_SHA256_H
