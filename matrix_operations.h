#ifndef __MATRIX_OPERATIONS_H
#define __MATRIX_OPERATIONS_H


#define MUL_POINT 1		// Multiplication menu number
#define EXT_POINT 2		// Exit menu number

#define DEBUG			// Print debug information

// Macroses
#define ctoi(c) c - '0'	// Translate char to int


// Thread data structure
typedef struct {
    uint8_t m1_line;	// 1st matrix line number
    uint8_t m2_column;	// 2nd matrinx column number
    uint8_t m_size;		// Elements count in line/column
    float** m1;
    float** m2;			// Matrix pointers
    float** mr;
} pthr_data;


// Prototypes
void* thr_mul(void* thr_data);	// Thread function
void start_screen(void);		// Start screen, main menu
void multiplication(void);		// Matrix multiplication mode

#endif