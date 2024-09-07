#include <stdio.h>
#include <stdlib.h>

#include "bmp_reader.h"
#include "bmp_writer.h"
#include "bmp_transform.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Использование: %s <входной BMP файл> <выходной BMP файл>\n", argv[0]);
        return 1;
    }

    BMPFile* bmp = loadBMPfile(argv[1]);

    if (bmp != NULL) {
        printf("Изображение успешно загружено.\n");

        transformRotateCW90(bmp);

        saveBMPfile(bmp, argv[2]);
        printf("Изображение успешно сохранено.\n");

        freeBMPfile(bmp);
    } 
    
    else {
        printf("Не удалось загрузить BMP файл.\n");
    }

    return 0;
}