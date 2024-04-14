#include <stdio.h>

union doubleBytes {
    double number;
    unsigned char bytes[sizeof(double)];
    struct {
        unsigned int byte0 : 8;
        unsigned int byte1 : 8;
        unsigned int byte2 : 8;
        unsigned int byte3 : 8;
        unsigned int byte4 : 8;
        unsigned int byte5 : 8;
        unsigned int byte6 : 8;
        unsigned int byte7 : 8;
    } bytesAsBits;
};

void printBytes(const unsigned char *bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d байт: %d\n", i + 1, bytes[i]);
    }
}

void solveTask1() {
    union doubleBytes bin;
    printf("Введите число: ");
    scanf("%lf", &bin.number);

    printf("Байты числа:\n");
    printBytes(bin.bytes, sizeof(double));

    printf("Байты в виде полей бит:\n");
    printf("byte0: %d\n", bin.bytesAsBits.byte0);
    printf("byte1: %d\n", bin.bytesAsBits.byte1);
    printf("byte2: %d\n", bin.bytesAsBits.byte2);
    printf("byte3: %d\n", bin.bytesAsBits.byte3);
    printf("byte4: %d\n", bin.bytesAsBits.byte4);
    printf("byte5: %d\n", bin.bytesAsBits.byte5);
    printf("byte6: %d\n", bin.bytesAsBits.byte6);
    printf("byte7: %d\n", bin.bytesAsBits.byte7);
}