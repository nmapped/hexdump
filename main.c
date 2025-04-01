#include <stdio.h>
#include <ctype.h>

void print_hex_ln(unsigned char* buffer, size_t bytes_read, size_t* offset) {
    printf("%08zX  ", *offset);  // print offset

    // print hex values
    for (size_t i = 0; i < bytes_read; i++) {
        printf("%02X ", buffer[i]);
    }

    // print ascii representation
    printf("\t");
    for (size_t i = 0; i < bytes_read; i++) {
        printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
    }

    printf("\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("error: can't open file %s\n", argv[1]);
        return 1;
    }

    unsigned char buffer[16];
    size_t bytes_read;
    size_t offset = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        print_hex_ln(buffer, bytes_read, &offset);
        offset += bytes_read;
    }

    fclose(fp);
    return 0;
}
