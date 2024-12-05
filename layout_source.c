#include "header.h"

void drawBoxWithText(char *text, int width) {
    int textLen = strlen(text);
    int padding = (width - textLen) / 2;
    int i;

    // Garis atas
    printf("%c", 201);
    for (i = 0; i < width; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);

    // Baris dengan teks
    printf("%c", 186);
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (i = 0; i < width - textLen - padding; i++) {
        printf(" ");
    }
    printf("%c\n", 186);

    // Garis bawah
    printf("%c", 200);
    for (i = 0; i < width; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}
