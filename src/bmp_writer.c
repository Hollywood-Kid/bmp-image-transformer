#include "bmp_writer.h"
#include <stdio.h>
#include <stdlib.h>

void saveBMPfile(BMPFile* bmp_file, const char* fname) {
    FILE* fp = fopen(fname, "wb");

    if (!fp) {
        printf("Ошибка: не удалось сохранить файл.\n");
        exit(1);
    }

    // Запись заголовков BMP и DIB
    fwrite(&bmp_file->fileHeader, sizeof(BMPFileHeader), 1, fp);
    fwrite(&bmp_file->dibHeader, sizeof(DIBHeader), 1, fp);

    int width = bmp_file->dibHeader.biWidth;
    int height = bmp_file->dibHeader.biHeight;
    int bytes_per_pixel = bmp_file->dibHeader.biBitCount / 8;
    int row_size = width * bytes_per_pixel;

    // Рассчитываем паддинг
    int row_padding = (4 - (row_size % 4)) % 4;

    unsigned char* row_buffer = (unsigned char*)malloc(row_size + row_padding);

    // Запись пикселей с учётом паддинга
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            row_buffer[x * bytes_per_pixel] = bmp_file->data[y * width + x].b;
            row_buffer[x * bytes_per_pixel + 1] = bmp_file->data[y * width + x].g;
            row_buffer[x * bytes_per_pixel + 2] = bmp_file->data[y * width + x].r;
        }

        // Добавляем паддинг нулями
        for (int p = 0; p < row_padding; p++) {
            row_buffer[row_size + p] = 0;
        }

        fwrite(row_buffer, 1, row_size + row_padding, fp);
    }

    free(row_buffer);
    fclose(fp);
}