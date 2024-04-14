#include <stdio.h>
#include <windows.h>
#include "tasks.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    char input;
    int taskNumber;
    printf("Введите номер задачи: ");
    scanf("%d", &taskNumber);
    do {
        switch (taskNumber) {
            case 1:
                solveTask1(); break;
            case 2:
                solveTask2(); break;
            default:
                printf("Неверный номер задачи\n"); break;
        }
        printf("Нажмите 'q' для выхода или любую другую клавишу для продолжения: ");
        scanf(" %c", &input);
    } while (input != 'q');
    return 0;
}