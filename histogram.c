#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define B2L_ENDIAN(num) (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000))

int is_little_endian() {
    uint16_t word = 0x0001;
    uint8_t* ptr = (uint8_t*)&word;
    return (ptr[0]) ? 1 : 0;
}

uint8_t* read_file(const char* file_path, size_t* size) {
    FILE* fp = fopen(file_path, "rb");

    if (!fp) {
        fprintf(stderr, "File couldn't found\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*)malloc(*size);

    if (!buffer) {
        fprintf(stderr, "Buffer is null\n");
        exit(1);
    }

    fread(buffer, *size, 1, fp);
    fclose(fp);
    return buffer;
}

void histogram(const uint8_t* buffer, size_t size) {
    int i, hist[256] = { 0 };
    float ort, var;

    for (i = 0; i < size; i++)
        hist[buffer[i]]++;

    for (i = 0; i < 256; i++)
        printf("%d ==> %d\n", i, hist[i]);

    ort = 0.0f;
    for (i = 0; i < 256; i++)
        ort += i * hist[i];
    ort /= size;
    printf("\n");
    printf("ortalama : %f\n", ort);

    var = 0.0f;
    for (i = 0; i < 256; i++)
        var += (i - ort) * (i - ort) * hist[i];
    var = var / (size - 1);

    printf("varyans : %f", var);
}

int main()
{
    uint8_t* buffer;
    uint32_t offset, width, height;
    size_t size;

    buffer = read_file("lena.bmp", &size);

    if (is_little_endian()) {
        offset  = *((uint32_t*)(&buffer[10]));
        width   = *((uint32_t*)(&buffer[18]));
        height  = *((uint32_t*)(&buffer[22]));
    }
    else {
        offset  = B2L_ENDIAN(*((uint32_t*)(&buffer[10])));
        width   = B2L_ENDIAN(*((uint32_t*)(&buffer[18])));
        height  = B2L_ENDIAN(*((uint32_t*)(&buffer[22])));
    }
    
    histogram(&buffer[offset], width * height);

    return 0;
}