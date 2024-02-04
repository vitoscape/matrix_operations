#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>

#include "matrix_operations.h"


// Главное меню
void start_screen() {
    uint8_t continue_flag = 0; // Флаг продолжения

    while(!continue_flag) {
        continue_flag = 1;  // Взвод флага на пропуск
        system("clear");    // Очистка экрана
        char input = 0;  // Вводимый символ

        printf("Matrix operations.\nChoose operation and press Enter key.\n\n");
        printf("%d. Multiplication\n", MUL_POINT);
        printf("%d. Exit\n\n>>", EXT_POINT);

        scanf("%c", &input); // Ввод

        // Выбор пункта меню
        if (ctoi(input) == MUL_POINT) {
            multiplication();   // Выхов функции умножения
        } else if (ctoi(input) == EXT_POINT) {
            system("clear");    // Очистка экрана
            printf("Thank you for using this program.\n");
            exit(0);            // Выход из программы
        } else {
            continue_flag = 0;  // Сброс флага
            printf("\nEnter number between %d to %d:\n", MUL_POINT, EXT_POINT);
        }
    }
}

// Умножение
void multiplication() {
    system("clear");    // Очистка экрана
    printf("Matrix multiplication: MxN x NxL\n");
    printf("Enter sizes: M, N, L\n\n>>");
}

int main() {
    start_screen();

    return 0;
}