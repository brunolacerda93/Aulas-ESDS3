#include "tools.h"
#include "sorting.h"

#define SIZE ONE_MILLION


// Métodos e funções

    //
    // Bubble Sort
    //
    void bubbleSort(int* array, const int n) {
        bool swapped;

        for (int i = n-1; i>0; i--) {
            swapped = false;

            for (int j = 0; j<i; j++) {
                if (array[j] > array[j+1]) {
                    swap(&array[j], &array[j+1]);
                    swapped = true;
                }
            }
            
            if (!swapped) break;
        }
    }

    //
    // Insertion Sort
    //
    void insertionSort(int* array, const int n) {
        int j, aux;

        for (int i=1; i<n; i++) {
            aux = array[i];
            
            for (j = i-1; j >= 0 && array[j] > aux; j--) {
                array[j+1] = array[j];
            }
            
            array[j+1] = aux;
        }
    }

    //
    // Selection Sort
    //
    void selectionSort(int* array, const int n) {
        int min;

        for (int i=0; i < n-1; i++) {
            min = i;
            
            for (int j = i+1; j<n; j++) {
                if (array[j] < array[min])
                    min = j;
            }
            
            swap(&array[i], &array[min]);
        }
    }

    //
    // Merge
    //
    void merge(int* array, const int ini, const int meio, const int fim) {
        int com1 = ini;
        int com2 = meio+1;
        int tam = fim-ini+1;
        int iAux = 0;
        
        int *vetAux = createArray(tam);

        while (com1 <= meio && com2 <= fim) {
            if (array[com1] < array[com2]) {
                vetAux[iAux] = array[com1];
                com1++;
            } else {
                vetAux[iAux] = array[com2];
                com2++;
            }
            iAux++;
        }

        while (com1 <= meio) {                              // caso ainda haja elementos na primeira metade
            vetAux[iAux] = array[com1];
            iAux++;
            com1++;
        }

        while (com2 <= fim) {                               // caso ainda haja elementos na segunda metade
            vetAux[iAux] = array[com2];
            iAux++;
            com2++;
        }

        for (iAux = ini; iAux <= fim; iAux++) {       // move os elementos de volta para o array original
            array[iAux] = vetAux[iAux-ini];
        }
        
        free(vetAux);
    }

    //
    // Merge Sort
    //
    void mergeSort(int* array, const int ini, const int fim) {
        if (ini >= fim) return;

        int meio = (fim+ini)/2;

        mergeSort(array, ini, meio);
        mergeSort(array, meio+1, fim);
        merge(array, ini, meio, fim);
    }

    //
    // Quick Sort (Lomuto)
    //
    void lomutoQuickSort(int* array, const int ini, const int fim) {
        if (ini >= fim) return;

        int pivot = array[fim];
        int swp;

        // set a pointer to divide array into two parts
        // one part is smaller than the pivot and another larger

        int ptr = ini;
        for (int i = ini; i < fim; i++) {
            if (array[i] < pivot) {
                if (ptr != i) {
                    swp = array[i];                 // swap a[i] with array[ptr]
                    array[i] = array[ptr];          // array[ptr] behind larger than pivot
                    array[ptr] = swp;
                }
                ptr++;
            }
        }

        //swap back pivot to proper position
        swp = array[fim];
        array[fim] = array[ptr];
        array[ptr] = swp;

        lomutoQuickSort(array, ini, ptr - 1);
        lomutoQuickSort(array, ptr + 1, fim);
    }

    //
    // Quick Sort (Hoare) -> Otimizado para evitar o pior caso
    //
    void hoareQuickSort(int* array, const int ini, const int fim) {
        int aux;
        int i = ini, j = fim;
        int meio = (ini + fim) / 2;
        int pivot = array[meio];

        // Hoare’s Partition 
        while (i <= j) {
            if (array[i] < pivot)
                i++;                            // até encontrar um valor maior ou igual o pivot
            else if (array[j] > pivot)
                j--;                            // até encontrar um valor menor ou igual o pivot
            else {
                // troque os valores
                aux = array[i];
                array[i++] = array[j];  
                array[j--] = aux;
            }
        }

        if (ini < j)
            hoareQuickSort(array, ini, j);
        if (fim > i)
            hoareQuickSort(array, i, fim);
    }

    //
    // Cria um Array de Inteiros
    //
    int *createArray(const int size) {
        return (int*) calloc(size, sizeof(int));
    }

    //  
    // Preenche um Array de Inteiros com números aleatórios
    //
    void fillArray(int* array, const int size) {
        static unsigned int ts = 0;
        srand(ts += 36);
        
        for (int i=0; i<size; i++) {
            array[i] = (rand() % RAND_MAX) * ((rand() % 1000) + 1);
        }
    }

    //
    // Exibe um Array de Inteiros
    //
    void showArray(int* array, const int size) {
        for (int i=0; i<size; i++) {
            printf("[%8d] ", array[i]);
            if ((i+1)%10 == 0)
                printf("\n");
        }
    }

    //
    // Gera um Novo Array de Inteiros
    //
    int *resetArray(int* array, const int size) {
        free(array);
        array = createArray(size);
        fillArray(array, size);
        return array;
    }

    //
    // Menu Principal
    //
    void menu(const int size) {
        char opc;
        clock_t t;  // para armazenar o tempo de execução

        int *array = createArray(size);
        fillArray(array, size);

        do { // hast
            cleanScreen();

            printf("\n[0] = %08d\n\n", array[0]);
            puts(" 1 - Bubble Sort");
            puts(" 2 - Insertion Sort");
            puts(" 3 - Selection Sort");
            puts(" 4 - Merge Sort");
            puts(" 5 - Lomuto Quick Sort");
            puts(" 6 - Hoare  Quick Sort");
            puts(" 7 - Show Array");
            puts(" 8 - Reset Array");
            puts(" 0 - Exit\n");
            printf(" Choose: ");
            scanf("%c", &opc); clearBuffer();

            t = clock();    // inicia a contagem do tempo

            switch (opc) {
                case '1':      bubbleSort(array, size);       break;
                case '2':   insertionSort(array, size);       break;
                case '3':   selectionSort(array, size);       break;
                case '4':       mergeSort(array, 0, size);    break;
                case '5': lomutoQuickSort(array, 0, size);    break;
                case '6':  hoareQuickSort(array, 0, size);    break;
                case '7':      showArray(array, size);        break;
                case '8': array = resetArray(array, size);    break;
                case '0': free(array); pause(); exit(0);
                default: puts("INVALID!\n");                  break;
            }

            t = clock() - t;    // finaliza a contagem do tempo
            double time_taken = ((double)t)/CLOCKS_PER_SEC; // em segundos
            
            printf("\nTime taken: %.3lf seconds\n", time_taken);
            pause();

        } while(opc != '0');
    }
