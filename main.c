#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("provide a file to read: %s <file>", argv[0]);
		return 1;
	}

	FILE* fp = fopen(argv[1], "rb");	
	if (fp == NULL) {
		printf("error opening file\n");
		return 1;
	}

	unsigned char buffer[16];
	size_t bytes_read;
	size_t offset = 0;

	/* fread(buffer, element size, no of elements, stream)
	 -> moves file pointer forward automatically
	 */
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		printf("%08zX\t", offset);
		for (size_t i = 0; i < bytes_read; i++) {
			printf("%02X ", buffer[i]);
		}
		printf("\n");
		offset += bytes_read;
	}

	fclose(fp);
	return 0;
}
