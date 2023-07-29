#include "tools.h"

int *allocateArray(int size) {
    return (int *) calloc(size, sizeof(int));
}

int **allocateMatrix(int linhas, int colunas) {
    int** temp = (int **) calloc(linhas, sizeof(int *));
    
    for (size_t i = 0; i < linhas; i++) {
        temp[i] = allocateArray(colunas);
    }

    return temp;
}

void matrixis() {
    int linhas = 3;
    int colunas = 4;

    int **arr = allocateMatrix(linhas, colunas);

    for (size_t i = 0; i < linhas; i++) {
        for (size_t j = 0; j < colunas; j++) {
            arr[i][j] = rand() % RAND_MAX;
        }
    }

    for (size_t i = 0; i < linhas; i++) {
        for (size_t j = 0; j < colunas; j++) {
            printf("%8d ", arr[i][j]);
        }
        puts("");
    }

    for (size_t i = 0; i < linhas; i++) {
        free(arr[i]);
    }
}

int isPalindrome(string str) {
    size_t size = strlen(str);

    size_t j = 0;

    for (size_t i = size-1; i >= 0 && j < size; i--) {
        if (str[i] != str[j++])
            return 0;
    }
    
    return 1;
}

void palindromers() {
    string str = "arara";
    printf("%s = %d\n", str, isPalindrome(str));

    str = "araras";
    printf("%s = %d\n", str, isPalindrome(str));
}

int findValue(int* arr, int size, int n) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == n)
            return i;
    }

    return -1;
}

void finders() {
    int n = 0;
    int x = 0;

    printf("Informe o tamanho do vetor: ");
    n = Int();

    printf("Informe o valor a ser buscado: ");
    x = Int();
    
    int *arr = allocateArray(n);

    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % RAND_MAX;
    }

    int y = findValue(arr, n, x);

    printf("\narr[%d] = %d", y, arr[y]);
}

int main(int argc, char const *argv[]) {
    matrixis();
    palindromers();
    finders();
    return 0;
}
