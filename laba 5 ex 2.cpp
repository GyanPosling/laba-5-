#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    int** arr;
    int* cols;
    int rows;
} Matrix;

void getValidInput(int* value) {
    while (1) {
        if (scanf_s("%d", value) != 1) {

            while (getchar() != '\n');
            printf("Error, try again!\n");
        }
        else {
            char ch;
            if (scanf_s("%c", &ch, 1) == 1 && ch != '\n') {
                while (getchar() != '\n');
                printf("Error!! Enter again: ");
            }
            else {
                break;
            }
        }
    }
}

Matrix scanfMatrix() {
    Matrix matrix;
    do {
        printf("Введите количество строк: ");
        getValidInput(&matrix.rows);
        if (matrix.rows <= 0) {
            printf("Количество строк должно быть положительным числом. Попробуйте еще раз.\n");
        }
    } while (matrix.rows <= 0);

    matrix.cols = (int*)malloc(matrix.rows * sizeof(int));
    matrix.arr = (int**)malloc(matrix.rows * sizeof(int*));

    for (int i = 0; i < matrix.rows; i++) {
        do {
            printf("Введите количество элементов в строке %d (последний элемент должен быть 100): ", i + 1);
            getValidInput(&matrix.cols[i]);
            if (matrix.cols[i] <= 0) {
                printf("Количество элементов в строке должно быть положительным числом. Попробуйте еще раз.\n");
            }
        } while (matrix.cols[i] <= 0);

        matrix.arr[i] = (int*)malloc(matrix.cols[i] * sizeof(int));
        for (int j = 0; j < matrix.cols[i]; j++) {
            printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
            getValidInput(&matrix.arr[i][j]);
        }

        matrix.arr[i][matrix.cols[i] - 1] = 100;
    }

    return matrix;
}

int* deleteNegativeElements(int* arr, int* size) {
    int newSize = 0;
    int* temp = (int*)malloc((*size) * sizeof(int));

    for (int i = 0; i < *size - 1; i++) {
        if (arr[i] >= 0) {
            temp[newSize++] = arr[i];
        }
    }

    temp[newSize++] = arr[*size - 1];
    *size = newSize;
    temp = (int*)realloc(temp, newSize * sizeof(int));

    return temp;
}

void DeleteNegative(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        matrix->arr[i] = deleteNegativeElements(matrix->arr[i], &matrix->cols[i]);
    }
}

void printMatrix(Matrix matrix) {
    printf("Матрица:\n");
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols[i]; j++) {
            printf("%d ", matrix.arr[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->arr[i]);
    }
    free(matrix->arr);
    free(matrix->cols);
}

int main() {
    setlocale(LC_ALL, "rus");

    Matrix matrix = scanfMatrix();

    printf("\nИсходная матрица:\n");
    printMatrix(matrix);

    DeleteNegative(&matrix);

    printf("\nМатрица после удаления отрицательных элементов:\n");
    printMatrix(matrix);

    freeMatrix(&matrix);

    return 0;
}
