#include <stdint.h>
#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t b1;
    uint8_t b2;
    uint16_t b34;
    uint8_t b5;
} test_t;
#pragma pack(pop)

int main() {
    const uint8_t stream[5] = {0x00, 0x03, 0x00, 0x20, 0x00};
    test_t t;
    memcpy(&t, stream, sizeof(t));
    
    printf("b1: 0x%02X\n", t.b1);
    printf("b2: 0x%02X\n", t.b2);
    printf("b34: 0x%04X\n", t.b34);
    printf("b5: 0x%02X\n", t.b5);
    
    // 尝试不同的版本解析
    printf("\n尝试版本解析:\n");
    printf("b1作为版本字节: maj=%u, min=%u\n", (t.b1 >> 4) & 0x0F, t.b1 & 0x0F);
    printf("b2作为版本字节: maj=%u, min=%u\n", (t.b2 >> 4) & 0x0F, t.b2 & 0x0F);
    
    return 0;
}
