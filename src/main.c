#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_reader.h"
#include "bmp_transform.h"
#include "bmp_writer.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Ошибка: укажите путь к BMP файлу, тип преобразования и путь для сохранения результата.\n");
        return 1;
    }

    BMPFile* bmp = loadBMPfile(argv[1]);

    if (!bmp) {
        printf("Не удалось загрузить BMP файл.\n");
        return 1;
    }

    // Обрабатываем преобразование
    if (strcmp(argv[2], "none") == 0) {
        transformNone(bmp);
    } else if (strcmp(argv[2], "cw90") == 0) {
        transformRotateCW90(bmp);
    } else if (strcmp(argv[2], "ccw90") == 0) {
        transformRotateCCW90(bmp);
    } else if (strcmp(argv[2], "fliph") == 0) {
        transformFlipHorizontal(bmp);
    } else if (strcmp(argv[2], "flipv") == 0) {
        transformFlipVertical(bmp);
    } else {
        printf("Ошибка: неизвестный тип преобразования.\n");
        freeBMPfile(bmp);
        return 1;
    }

    // Сохраняем результат
    saveBMPfile(bmp, argv[3]);
    freeBMPfile(bmp);

    printf("Файл успешно сохранён.\n");

    return 0;
}
