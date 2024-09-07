#ifndef BMP_TRANSFORM_H
#define BMP_TRANSFORM_H

#include "bmp_reader.h"

void transformNone(BMPFile* bmp);
void transformFlipHorizontal(BMPFile* bmp);
void transformFlipVertical(BMPFile* bmp);
void transformRotateCW90(BMPFile* bmp);
void transformRotateCCW90(BMPFile* bmp);

#endif