#ifndef sorting_H_
#define sorting_H_

    void bubbleSort     (int*, const int);
    void insertionSort  (int*, const int);
    void selectionSort  (int*, const int);
    void merge          (int*, const int, const int, const int);
    void mergeSort      (int*, const int, const int);
    void lomutoQuickSort(int*, const int, const int);
    void hoareQuickSort (int*, const int, const int);
    int* createArray    (const int);
    void fillArray      (int*, const int);
    void showArray      (int*, const int);
    int* resetArray     (int*, const int);

#endif