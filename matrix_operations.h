#ifndef __MATRIX_OPERATIONS_H
#define __MATRIX_OPERATIONS_H


#define MUL_POINT 1 // Номер пункта Умножение
#define EXT_POINT 2 // Номер пункта Выход

#define DEBUG

// Макросы
#define ctoi(c) c - '0'     // Перевод char в int

// Структура для данных потока
typedef struct {
    uint8_t m1_line;    // Номер строки первой матрицы
    uint8_t m2_column;  // Номер столбца второй матрицы
    uint8_t m_size;     // Кол-во элементов в строке/столбце
    float** m1;
    float** m2; // Указатели на матрицы
    float** mr;
} pthr_data;


// Прототипы функций
void start_screen(void);    // Начальный экран, главное меню
void multiplication(void);  // Умножение матриц

#endif