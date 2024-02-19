#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix_operations.h"

// Глобальные переменные
int n, m, l;    // Размерности матриц


// Функция потока
void* thr_mul(void* thr_data) {
    pthr_data *data = (pthr_data*) thr_data;    // Получение структуры данных
    float _mul_res = 0;                         // Элемент матрицы-результата умножения

    // Сумма произведений i-х элементов строки первой матрицы и столбца второй матрицы
    for (uint8_t i = 0; i < data->m_size; i++) {
        _mul_res += data->m1[data->m1_line][i] * data->m2[i][data->m2_column];
    }
    data->mr[data->m1_line][data->m2_column] = _mul_res;    // Присвоение результата матрице

    return NULL;
}

// Главное меню
void start_screen() {
    uint8_t continue_flag = 0; // Флаг продолжения

    while(!continue_flag) {
        continue_flag = 1;  // Взвод флага на пропуск
        system("clear");    // Очистка экрана
        char inp_s = 0;     // Вводимый символ

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

    uint8_t calcN = n * l;  // Количество потоков (вычислений каждого элемента)

    // Выделение памяти под массив идентификаторов потоков
    pthread_t* thr = (pthread_t*) malloc(calcN * sizeof(pthread_t));
    // Выделение памяти под структуры с потоковыми данными
    pthr_data* thr_data = (pthr_data*) malloc(calcN * sizeof(pthr_data));

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

    // Инициализация структур потоков
    for (uint8_t i = 0; i < n; i++) {
        for (uint8_t j = 0; j < l; j++) {
            uint8_t number = i + j; // Номер потока

            // Заполнение структуры потока
            thr_data[number].m1_line = i;
            thr_data[number].m2_column = j;
            thr_data[number].m_size = m;
            thr_data[number].m1 = matrix1;
            thr_data[number].m2 = matrix2;
            thr_data[number].mr = matrix_result;

            // Запуск потока
            pthread_create(&(thr[number]), NULL, thr_mul, &thr_data[number]);
        }
    }

    // Ожидание выполнения всех потоков
    for (uint8_t i = 0; i < calcN; i++) {
        pthread_join(thr[i], NULL);
    }

    // Вывод матрицы-результата
    printf("\n\nResult:\n\n");
    for (uint8_t i = 0; i < n; i++) {
        for (uint8_t j = 0; j < l; j++) {
            printf("%6.2f", matrix_result[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    start_screen();

    return 0;
}