#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix_operations.h"

// Глобальные переменные
int n, m, l;    // Размерности матриц

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
    //int inp_m[10];
    do {
        system("clear");    // Очистка экрана
        printf("Matrix multiplication: NxM x MxL\n \n");
        printf("    / x ... x \\     / x ... x \\  \n");
        printf("   |  . ... .  |   |  . ... .  |   \n");
        printf("N  |  . ... .  | X |  . ... .  |  M\n");
        printf("   |  . ... .  |   |  . ... .  |   \n");
        printf("    \\ x ... x /     \\ x ... x /  \n\n");
        printf("         M               L\n\n");
        printf("Enter sizes: M, N, L\n");

        // Ввод размерностей матриц
        printf("M = ");
        scanf("%d", &m);
        //m = atoi(inp_m);

        printf("N = ");
        scanf("%d", &n);
        //n = atoi(inp_m);

        printf("L = ");
        scanf("%d", &l);
        //l = atoi(inp_m);

        //printf("M = %d, N = %d, L = %d", m, n, l);
    } while (m <= 0 || n <= 0 || l <= 0);

    //Матрицы
    //float matrix1[n][m], matrix2[m][l], matrix_result[n][l];

    // Выделение памяти под двумерные массивы
	float** matrix1 = (float**) malloc(n * sizeof(float*));
	float** matrix2 = (float**) malloc(m * sizeof(float*));
	float** matrix_result = (float**) malloc(n * sizeof(float*));

    // Выделение памяти под элементы матриц
	for (uint8_t i = 0; i < m; i++) {
		matrix1[i] = (float*) malloc(m * sizeof(float));
	}
    for (uint8_t i = 0; i < l; i++) {
        matrix2[i] = (float*) malloc(l * sizeof(float));
		matrix_result[i] = (float*) malloc(l * sizeof(float));
    }

    // Ввод матриц
    printf("Input first matrix:\n");
    for (uint8_t i = 0; i < m; i++) {
        for (uint8_t j = 0; j < n; j++) {
            scanf("%f", &matrix1[i][j]);
        }
    }
    printf("Input second matrix:\n");
    for (uint8_t i = 0; i < l; i++) {
        for (uint8_t j = 0; j < m; j++) {
            scanf("%f", &matrix1[i][j]);
        }
    }
}

int main() {
    start_screen();

    return 0;
}