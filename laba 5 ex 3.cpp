#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

typedef struct {
    int** arr;
    int rows;
    int cols;
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

void shiftLeft(int* row, int cols, int k) {
    int* temp = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        temp[i] = row[i];
    }

    for (int i = 0; i < cols - k; i++) {
        row[i] = row[i + k];
    }

    for (int i = 0; i < k; i++) {
        row[cols - k + i] = temp[i];
    }

    free(temp);
}

Matrix scanfMatrix() {
    Matrix matrix;
    do {
        printf("Введите количество строк в матрице: ");
        getValidInput(&matrix.rows);
        if (matrix.rows <= 0) {
            printf("Количество строк должно быть положительным. Попробуйте еще раз.\n");
        }
    } while (matrix.rows <= 0);

    do {
        printf("Введите количество столбцов в матрице: ");
        getValidInput(&matrix.cols);
        if (matrix.cols <= 0) {
            printf("Количество столбцов должно быть положительным. Попробуйте еще раз.\n");
        }
    } while (matrix.cols <= 0);

    matrix.arr = (int**)malloc(matrix.rows * sizeof(int*));
    for (int i = 0; i < matrix.rows; i++) {
        matrix.arr[i] = (int*)malloc(matrix.cols * sizeof(int));
    }

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("Введите [%d][%d] элемент: ", i + 1, j + 1);
            getValidInput(&matrix.arr[i][j]);
        }
    }

    return matrix;
}

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%d ", matrix.arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    Matrix matrix = scanfMatrix();

    int k;
    printf("Введите число k: ");
    getValidInput(&k);

    while (k > matrix.cols) {
        printf("k не может быть больше количества столбцов (%d). Введите k заново: ", matrix.cols);
        getValidInput(&k);
    }

    printf("Исходная матрица:\n");
    printMatrix(matrix);

    for (int i = 0; i < matrix.rows; i++) {
        shiftLeft(matrix.arr[i], matrix.cols, k % matrix.cols);
    }

    printf("Матрица после сдвига:\n");
    printMatrix(matrix);

    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.arr[i]);
    }
    free(matrix.arr);

    return 0;
}
