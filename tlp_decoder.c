
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    // Example PCIe Memory Write TLP (3-DW header)
    uint32_t header[3] = {
        0x40000001,
        0x0000000F,
        0x10000000
    };

    uint32_t dw0 = header[0];
    uint32_t dw1 = header[1];
    uint32_t dw2 = header[2];

    // Extract header fields using bit manipulation
    unsigned int fmt = (dw0 >> 29) & 0x7;
    unsigned int type = (dw0 >> 24) & 0x1F;
    unsigned int length = dw0 & 0x3FF;

    unsigned int requester_id = (dw1 >> 16) & 0xFFFF;
    unsigned int tag = (dw1 >> 8) & 0xFF;
    unsigned int last_be = (dw1 >> 4) & 0xF;
    unsigned int first_be = dw1 & 0xF;

    printf("PCIe TLP Header Decoder\n");
    printf("-----------------------\n");
    printf("Format:       0x%X\n", fmt);
    printf("Type:         0x%X\n", type);
    printf("Length:       %u DW (%u bytes)\n", length, length * 4);

    printf("Requester ID: 0x%04X\n", requester_id);
    printf("Tag:          0x%02X\n", tag);
    printf("First BE:     0x%X\n", first_be);
    printf("Last BE:      0x%X\n", last_be);

    printf("Address:      0x%08X\n", dw2);

    if (fmt == 2 && type == 0)
    {
        printf("Packet Type:  Memory Write (3-DW header)\n");
    }
    else
    {
        printf("Packet Type:  Other / Unsupported\n");
    }

    return 0;
}
