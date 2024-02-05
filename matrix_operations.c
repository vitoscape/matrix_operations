#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix_operations.h"

// Глобальные переменные
uint8_t n, m, l;    // Размерности матриц


// Главное меню
void start_screen() {
    uint8_t continue_flag = 0; // Флаг продолжения

    while(!continue_flag) {
        continue_flag = 1;  // Взвод флага на пропуск
        system("clear");    // Очистка экрана
        char inp_s = 0;  // Вводимый символ

        printf("Matrix operations.\nChoose operation and press Enter key.\n\n");
        printf("%d. Multiplication\n", MUL_POINT);
        printf("%d. Exit\n\n>>", EXT_POINT);

        scanf("%c", &inp_s); // Ввод

        // Выбор пункта меню
        if (ctoi(inp_s) == MUL_POINT) {
            multiplication();   // Выхов функции умножения
        } else if (ctoi(inp_s) == EXT_POINT) {
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
    char inp_m[10];
    system("clear");    // Очистка экрана
    printf("Matrix multiplication: MxN x NxL\n\n");
    printf("    / x ... x \\     / x ... x \\\n");
    printf("   |  . ... .  |   |  . ... .  |\n");
    printf("N  |  . ... .  | X |  . ... .  |  N\n");
    printf("   |  . ... .  |   |  . ... .  |\n");
    printf("    \\ x ... x /     \\ x ... x /\n\n");
    printf("         M               L\n\n");
    printf("Enter sizes: M, N, L\nM = ");

    
    // Вводи размерностей матриц
    scanf("%s", inp_m);
    m = atoi(inp_m);

    printf("N = ");
    scanf("%s", inp_m);
    n = atoi(inp_m);

    printf("L = ");
    scanf("%s", inp_m);
    l = atoi(inp_m);

    printf("M = %d, N = %d, L = %d", m, n, l);
}

int main() {
    start_screen();

    return 0;
}