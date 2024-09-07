#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

BMPFile* loadBMPfile(char* fname) {
    FILE* fp = fopen(fname, "rb");

    if (!fp) {
        printf("Ошибка: не удалось открыть файл.\n");
        exit(1);
    }

    BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));

    // Чтение заголовков BMP файла
    fread(&bmp_file->fileHeader, sizeof(BMPFileHeader), 1, fp);
    fread(&bmp_file->dibHeader, sizeof(DIBHeader), 1, fp);

    int width = bmp_file->dibHeader.biWidth;
    int height = bmp_file->dibHeader.biHeight;
    int bytes_per_pixel = bmp_file->dibHeader.biBitCount / 8;
    int row_size = width * bytes_per_pixel;

    // Рассчитываем количество байтов паддинга
    int row_padding = (4 - (row_size % 4)) % 4;

    // Выделяем память для пиксельных данных
    bmp_file->data = (Pixel*)malloc(width * height * sizeof(Pixel));

    // Читаем пиксели построчно с учетом паддинга
    unsigned char* row_buffer = (unsigned char*)malloc(row_size + row_padding);
    for (int y = height - 1; y >= 0; y--) {
        fread(row_buffer, 1, row_size + row_padding, fp);
        for (int x = 0; x < width; x++) {
            bmp_file->data[y * width + x].b = row_buffer[x * bytes_per_pixel];
            bmp_file->data[y * width + x].g = row_buffer[x * bytes_per_pixel + 1];
            bmp_file->data[y * width + x].r = row_buffer[x * bytes_per_pixel + 2];
        }
    }

    free(row_buffer);
    fclose(fp);

    return bmp_file;
}

void freeBMPfile(BMPFile* bmp_file) {
    if (bmp_file) {
        if (bmp_file->data) {
            free(bmp_file->data);
        }
        free(bmp_file);
    }
}
