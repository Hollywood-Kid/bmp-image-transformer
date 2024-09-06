#ifndef BMP_READER_H
#define BMP_READER_H

#include <stdint.h>

typedef struct __attribute__((packed)) BMPHeader
{
  uint16_t bfType;        // Тип файла "BM"
  uint32_t bfileSize;     // Размер файла в байтах
  uint32_t bfReserved;    // Зарезервировано, всегда 0
  uint32_t bOffBits;      // Смещение от начала файла до данных изображения
} BMPFileHeader;

typedef struct __attribute__((packed)) DIBHeader
{
  uint32_t biSize;        // Размер структуры DIB Header
  uint32_t biWidth;       // Ширина изображения
  uint32_t biHeight;      // Высота изображения
  uint16_t biPlanes;      // Число цветовых плоскостей (всегда 1)
  uint16_t biBitCount;    // Глубина цвета (например, 24 или 32 бита)
  uint32_t biCompression; // Тип сжатия (0 для несжатого)
  uint32_t biSizeImage;   // Размер изображения в байтах (может быть 0 для несжатого)
} DIBHeader;

typedef struct {
  uint8_t b, g, r;
} Pixel;

typedef struct {
  BMPFileHeader fileHeader;
  DIBHeader dibHeader;
  Pixel* data;
} BMPFile;

BMPFile* loadBMPfile(char* fname);
void freeBMPfile(BMPFile* bmp_file);

#endif