#include "bmp_transform.h"
#include <stdlib.h>

void transformNone(BMPFile* bmp) {
    // Ничего не делаем
}

void transformFlipHorizontal(BMPFile* bmp) {
    int width = bmp->dibHeader.biWidth;
    int height = bmp->dibHeader.biHeight;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            Pixel tmp = bmp->data[y * width + x];
            bmp->data[y * width + x] = bmp->data[y * width + (width - 1 - x)];
            bmp->data[y * width + (width - 1 - x)] = tmp;
        }
    }
}

void transformFlipVertical(BMPFile* bmp) {
    int width = bmp->dibHeader.biWidth;
    int height = bmp->dibHeader.biHeight;

    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            Pixel tmp = bmp->data[y * width + x];
            bmp->data[y * width + x] = bmp->data[(height - 1 - y) * width + x];
            bmp->data[(height - 1 - y) * width + x] = tmp;
        }
    }
}

void transformRotateCW90(BMPFile* bmp) {
    int width = bmp->dibHeader.biWidth;
    int height = bmp->dibHeader.biHeight;

    Pixel* rotated_data = (Pixel*)malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rotated_data[x * height + (height - 1 - y)] = bmp->data[y * width + x];
        }
    }

    free(bmp->data);
    bmp->data = rotated_data;
    bmp->dibHeader.biWidth = height;
    bmp->dibHeader.biHeight = width;
}

void transformRotateCCW90(BMPFile* bmp) {
    int width = bmp->dibHeader.biWidth;
    int height = bmp->dibHeader.biHeight;

    Pixel* rotated_data = (Pixel*)malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rotated_data[(width - 1 - x) * height + y] = bmp->data[y * width + x];
        }
    }

    free(bmp->data);
    bmp->data = rotated_data;
    bmp->dibHeader.biWidth = height;
    bmp->dibHeader.biHeight = width;
}