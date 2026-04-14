#include <stdint.h>
#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t version_raw;
    uint16_t length_be;
    uint8_t flags_raw;
} proto_header_raw_t;
#pragma pack(pop)

int main() {
    const uint8_t stream[5] = {0x00, 0x03, 0x00, 0x20, 0x00};
    proto_header_raw_t raw;
    memcpy(&raw, stream, sizeof(raw));
    
    printf("version_raw: 0x%02X\n", raw.version_raw);
    printf("length_be: 0x%04X\n", raw.length_be);
    printf("flags_raw: 0x%02X\n", raw.flags_raw);
    
    // 手动转换大端序
    uint16_t length = ((raw.length_be >> 8) & 0xFF) | ((raw.length_be & 0xFF) << 8);
    printf("length (converted): %u\n", length);
    
    return 0;
}
