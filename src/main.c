#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

void printBMPHeaders(BMPFile* bmp) {
    // Вывод информации о BMP File Header
    printf("BMP File Header:\n");
    printf("  Тип файла: %c%c (0x%X)\n", (bmp->fileHeader.bfType & 0xFF), (bmp->fileHeader.bfType >> 8), bmp->fileHeader.bfType);
    printf("  Размер файла: %u байт\n", bmp->fileHeader.bfileSize);
    printf("  Зарезервировано: %u\n", bmp->fileHeader.bfReserved);
    printf("  Смещение до данных изображения: %u байт\n", bmp->fileHeader.bOffBits);

    // Вывод информации о DIB Header (Bitmap Info Header)
    printf("\nDIB Header (Bitmap Info Header):\n");
    printf("  Размер DIB Header: %u байт\n", bmp->dibHeader.biSize);
    printf("  Ширина изображения: %d пикселей\n", bmp->dibHeader.biWidth);
    printf("  Высота изображения: %d пикселей\n", bmp->dibHeader.biHeight);
    printf("  Число цветовых плоскостей: %d\n", bmp->dibHeader.biPlanes);
    printf("  Глубина цвета: %d бит\n", bmp->dibHeader.biBitCount);
    printf("  Тип сжатия: %u\n", bmp->dibHeader.biCompression);
    printf("  Размер изображения: %u байт\n", bmp->dibHeader.biSizeImage);
}

void printBMPPixels(BMPFile* bmp) {
    printf("\nПиксели изображения:\n");
    int width = bmp->dibHeader.biWidth;
    int height = bmp->dibHeader.biHeight;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel pixel = bmp->data[y * width + x];
            printf("Пиксель (%d, %d): R=%d G=%d B=%d\n", x, y, pixel.r, pixel.g, pixel.b);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ошибка: укажите путь к BMP файлу в качестве аргумента.\n");
        return 1;
    }

    BMPFile* bmp = loadBMPfile(argv[1]);

    if (bmp != NULL) {
        printf("Файл BMP успешно загружен.\n\n");
        printBMPHeaders(bmp);
        
        printBMPPixels(bmp);  // Выводим информацию о пикселях
        
        freeBMPfile(bmp);
    } else {
        printf("Не удалось загрузить BMP файл.\n");
    }

    return 0;
}