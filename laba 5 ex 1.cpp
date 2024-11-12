#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

void getValidInput(int* value) {
    while (1) {
        if (scanf_s("%d", value) != 1) {
            while (getchar() != '\n');
            printf("Ошибка, попробуйте снова!\n");
        }
        else {
            char ch;
            if (scanf_s("%c", &ch, 1) == 1 && ch != '\n') {
                while (getchar() != '\n');
                printf("Ошибка! Введите снова: ");
            }
            else {
                break;
            }
        }
    }
}

void InputArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Введите элемент %d: ", i + 1);
        getValidInput(&arr[i]);
    }
    printf("\n");
}

void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int removeDuplicates(int* arr, int size) {
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < newSize; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            arr[newSize++] = arr[i];
        }
    }

    return newSize;
}

int main() {
    setlocale(LC_ALL, "rus");

    int size;
    do {
        printf("Введите количество элементов в массиве: ");
        getValidInput(&size);
        if (size <= 0) {
            printf("Размер массива должен быть положительным числом. Попробуйте еще раз.\n");
        }
    } while (size <= 0);

    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    InputArray(arr, size);
    printf("Ваш первоначальный массив: ");
    PrintArray(arr, size);

    int newSize = removeDuplicates(arr, size);
    printf("Массив после удаления дубликатов: ");
    PrintArray(arr, newSize);

    free(arr);
    return 0;
}
