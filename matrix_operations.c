#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix_operations.h"


// Global variables
int n, m, l;	// Matrix dimensions


// Thread function
void* thr_mul(void* thr_data) {
	pthr_data *data = (pthr_data*) thr_data;	// Get data structure
	float _mul_res = 0;							// Result matrix element

	#ifdef DEBUG
	printf("\t--\t%d, %d, %d\n", data->m1_line, data->m2_column, data->m_size);
	#endif

	// Sum of multiplication of i elements of first matrix line and second matrix column
	for (uint8_t i = 0; i < data->m_size; i++) {
		_mul_res += data->m1[i][data->m1_line] * data->m2[data->m2_column][i];

		#ifdef DEBUG
		printf("\t--\tmultiplying %.2f * %.2f: %.2f\n", data->m1[i][data->m1_line], data->m2[data->m2_column][i], _mul_res);
		#endif
	}
	data->mr[data->m1_line][data->m2_column] = _mul_res;	// Add result element to result matrix

	return NULL;
}


// Main menu
void start_screen() {
	uint8_t continue_flag = 0;

	while(!continue_flag) {
		continue_flag = 1;
		system("clear");	// Clear screen
		char inp_s = 0;		// Input symbol

		printf("Matrix operations.\nChoose operation and press Enter key.\n\n");
		printf("%d. Multiplication\n", MUL_POINT);
		printf("%d. Exit\n\n>>", EXT_POINT);

		scanf("%c", &inp_s);	// Input

		// Select menu point
		if (ctoi(inp_s) == MUL_POINT) {			// Multiplication
			multiplication();
		} else if (ctoi(inp_s) == EXT_POINT) {	// Exit
			system("clear");	// Clear screen
			printf("Thank you for using this program.\n");
			exit(0);			// Program exit
		} else {
			continue_flag = 0;
			printf("\nEnter number between %d to %d:\n", MUL_POINT, EXT_POINT);
		}
	}
}


void multiplication() {
	//int inp_m[10];
	do {
		system("clear");	// Clear screen
		printf("Matrix multiplication: NxM x MxL\n \n");
		printf("    / x ... x \\     / x ... x \\  \n");
		printf("   |  . ... .  |   |  . ... .  |   \n");
		printf("N  |  . ... .  | X |  . ... .  |  M\n");
		printf("   |  . ... .  |   |  . ... .  |   \n");
		printf("    \\ x ... x /     \\ x ... x /  \n\n");
		printf("         M               L\n\n");
		printf("Enter sizes: M, N, L\n");

		// Enter matrix dimensions
		printf("N = ");
		scanf("%d", &n);
		//n = atoi(inp_m);

		printf("M = ");
		scanf("%d", &m);
		//m = atoi(inp_m);

		printf("L = ");
		scanf("%d", &l);
		//l = atoi(inp_m);

		//printf("M = %d, N = %d, L = %d", m, n, l);
	} while (m <= 0 || n <= 0 || l <= 0);

	// Matrices
	// float matrix1[n][m], matrix2[m][l], matrix_result[n][l];

	// Memory allocation for 2d arrays
	float** matrix1 = (float**) malloc(n * sizeof(float*));
	float** matrix2 = (float**) malloc(m * sizeof(float*));
	float** matrix_result = (float**) malloc(n * sizeof(float*));

	// Memory allocation for matrix elements
	for (uint8_t i = 0; i < m; i++) {
		matrix1[i] = (float*) malloc(m * sizeof(float));
	}
	for (uint8_t i = 0; i < l; i++) {
		matrix2[i] = (float*) malloc(l * sizeof(float));
		matrix_result[i] = (float*) malloc(l * sizeof(float));
	}

	uint8_t calcN = n * l;	// Threads count (number of every element calculation)
	#ifdef DEBUG
	printf("\t--\tcalcN = %d\n", calcN);
	#endif

	// Memory allocation for array of thread IDs
	pthread_t* thr = (pthread_t*) malloc(calcN * sizeof(pthread_t));

	// Memory allocation for thread data structures
	pthr_data* thr_data = (pthr_data*) malloc(calcN * sizeof(pthr_data));

	// Matrix input
	printf("Input first matrix:\n");
	for (uint8_t i = 0; i < m; i++) {
		for (uint8_t j = 0; j < n; j++) {
			scanf("%f", &matrix1[i][j]);
		}
	}
	printf("Input second matrix:\n");
	for (uint8_t i = 0; i < l; i++) {
		for (uint8_t j = 0; j < m; j++) {
			scanf("%f", &matrix2[i][j]);
		}
	}


	uint8_t number = 0;	// Number of thread

	// Thread structures init
	for (uint8_t i = 0; i < n; i++) {
		for (uint8_t j = 0; j < l; j++) {

			// Fill thread structure
			thr_data[number].m1_line = i;
			thr_data[number].m2_column = j;
			thr_data[number].m_size = m;
			thr_data[number].m1 = matrix1;
			thr_data[number].m2 = matrix2;
			thr_data[number].mr = matrix_result;

			#ifdef DEBUG
			//printf("\t--\tInit thread #%d: %d, %d, %d\n", number, i, j, m);
			#endif

			// Start thread
			pthread_create(&(thr[number]), NULL, thr_mul, &thr_data[number]);
			number++;	// Next thread
		}
	}

	// Wait for all threads
	for (uint8_t i = 0; i < calcN; i++) {
		pthread_join(thr[i], NULL);
	}

	// Print result matrix
	printf("\n\nResult:\n\n");
	for (uint8_t i = 0; i < n; i++) {
		for (uint8_t j = 0; j < l; j++) {
			printf("%10.2f", matrix_result[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main() {
	start_screen();

	return 0;
}