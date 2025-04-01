#include <stdio.h>
#include <ctype.h>

void print_hex_ln(unsigned char* buffer, size_t* bytes_read, size_t* offset) {
	printf("%08zX\t", *offset);
	for (size_t i = 0; i < *bytes_read; i++) {
		printf("%02X ", buffer[i]);
		if (i % 16 == 15 || i == *bytes_read - 1) {
			printf("\t");
			for (size_t j = i - (i % 16); j <= i; j++) {
				printf("%c", isprint(buffer[j]) ? buffer[j] : '.');
			}
			printf("\n");
		}
	}
}

int main(int argc, char** argv) {
	if (argc < 2) printf("usage: %s <filename>\n", argv[0]);

	FILE* fp = fopen(argv[1], "rb");

	if (fp == NULL) printf("there was an error opening the file\n"); 

	unsigned char buffer[16];
	size_t bytes_read;
	size_t offset = 0;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		print_hex_ln(buffer, &bytes_read, &offset);
		offset += bytes_read;
	}

	return 0;
}
