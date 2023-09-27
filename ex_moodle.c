#include "sorting.c"
#include <math.h>

//
// Reallocates an array of integers into a new bigger array, copying the previous into the newer
//
int* my_realloc(int* arr, const size_t size_arr, const size_t new_size) {
    if (new_size <= size_arr) {
        fprintf(stderr, "New size must be bigger than older size!!!");
        return arr;
    }

    int* new_arr = (int *) calloc(new_size, sizeof(int));

    if (arr == NULL)
        return new_arr;
    
    for (size_t i = 0; i < size_arr; i++) {
        new_arr[i] = arr[i];
    }

    free(arr);
    return new_arr;
}

//
// Exercício 6
//
void sequencia() {
    size_t size = 0;
    int* seq = NULL;
    int input;

    do { // hast
        input = Int();

        if (input == 0)
            break;
        
        seq = my_realloc(seq, size, size+1);
        seq[size++] = input;

    } while (true);

    unsigned int soma_par   = 0;
    unsigned int soma_impar = 0;
    unsigned int soma_total = 0;

    for (size_t i = 0; i < size; i++) {
        if (seq[i] % 2 == 0)
            soma_par += seq[i];
        else
            soma_impar += seq[i];

        soma_total += seq[i];
    }
    
    printf("Soma dos pares  : %d\n", soma_par);
    printf("Soma dos impares: %d\n", soma_impar);
    printf("Soma total      : %d\n", soma_total);
    
    printf("The sequence    : ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", seq[i]);
    }

    puts("");
    free(seq);
}

//
// Removes the passed char from the string
//
void remove_char(string str, char c) {
    int length = strlen(str);
    int j = 0;

    for (size_t i = 0; i < length; i++) {
        if (str[i] != c)
            str[j++] = str[i];
    }

    str[j] = '\0';    
}

//
// Swaps two chars by address
//
void swap_char(char *c1, char *c2) {
    char c = *c1;
    *c1 = *c2;
    *c2 = c;
}

//
// Bubble sort for strings
//
void str_bubble_sort(string str) {
    int len = strlen(str);
    bool swapped;

    for (size_t i = len - 1; i > 0; i--) {
        swapped = false;

        for (size_t j = 0; j < i; j++) {
            if (str[j] > str[j+1]) {
                swap_char(&str[j], &str[j+1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
}

//
// Removes empty spaces, sorts and then compares both strings
//
bool is_anagram(string str1, string str2) {
    remove_char(str1, ' ');
    remove_char(str2, ' ');

    if (strlen(str1) != strlen(str2))
        return false;
    
    str_bubble_sort(str1);
    str_bubble_sort(str2);

    for (size_t i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i])
            return false;
    }
    
    return true;
}

//
// Returns 1 if crescent, -1 if decrescent and 0 if not sorted
//
int is_sorted_type(int* array, const int size) {
    bool crescent   = true;
    bool decrescent = true;
    bool is_equal   = true;

    for (size_t i = 0; i < size-1; i++) {
        if (array[i] != array[i+1]) {
            is_equal = false;
            break;
        }
    }
    if (is_equal) return 1;

    for (size_t i = 0; i < size-1; i++) {
        if (array[i] > array[i+1]) {
            crescent = false;
            break;
        }
    }
    if (crescent) return 1;
    
    for (size_t i = 0; i < size-1; i++) {
        if (array[i] < array[i+1]) {
            decrescent = false;
            break;
        }
    }
    if (decrescent) return -1;

    return 0;
}

//
// Returns 1 if there's repetition, otherwise returns 0
//
int repeated_char(string str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len-1; i++) {
        for (size_t j = i+1; j <= len; j++) {
            if (str[i] == str[j])
                return 1;
        }
    }
    
    return 0;
}

//
// Prints H = 1 + 1/2 + 1/3 + ... + 1/n and returns H
//
double harmonics(const unsigned int n) {
    if (n == 0)
        return 0.0;

    double harmonic = 1.0;

    printf("\nHarmonic of %d\n H = 1", n);

    for (int i = 2; i <= n; i++) {
        harmonic += (1/(double)i);
        printf(" + 1/%d", i);
    }
    
    return harmonic;
}

//
// Prints text based on the age inputed
//
void eleitor(const int idade) {
    // if (idade == 16 || idade == 17)
    //     puts("Eleitor Facultativo");
    // else if (idade >= 18 && idade < 70)
    //     puts("Eleitor Obrigatorio");
    // else
    //     puts("Eleitor Dispensado");

    switch (idade) {
        case 16 :
        case 17 :       puts("Eleitor Facultativo"); break;
        case 18 ... 69: puts("Eleitor Obrigatorio"); break;
        default :       puts("Eleitor Dispensado");  break;
    }
}

//
// Returns the factorial of the integer n
//
unsigned long factorial(const unsigned int n) {
    unsigned long fat = 1L;
    
    for (size_t i = 2; i <= n; i++) {
        fat *= i;
    }

    return fat;
}

//
// Returns true if the integer n is prime
//
bool is_prime(const int n) {
    const int val = (int) sqrt((double) n);

    for (size_t i = 2; i <= val; i++) {
        if (n%i == 0)
            return false;
    }
    
    return true;
}

//
// Returns the sum of factorials between 0 and the integer n
//
unsigned long sum_factorial(const unsigned int n) {
    unsigned long s_fat = 1L;

    for (size_t i = 2; i <= n; i++) {
        s_fat += factorial(i);
    }

    return s_fat;
}

//
// Returns the frequency of the integer x in the vector vec
//
unsigned int freq_vector(const int* vec, const size_t vec_size, const int x) {
    unsigned int freq = 0;
    
    for (size_t i = 0; i < vec_size; i++) {
        if (vec[i] == x)
            freq++;
    }
    
    return freq;
}


int main(int argc, char const *argv[]) {
    // Exercício 6
        puts("EXERCICIO 06");
        // sequencia();

    // Exercício 11
        puts("\nEXERCICIO 11");

        int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int arr2[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        int arr3[] = { 3, 9, 2, 7, 6, 1, 6, 4, 2 };
        int arr4[] = { 6, 6, 6, 6, 6, 6, 6, 6, 6 };

        printf("arr1 -> %2d\n", is_sorted_type(arr1, 9));
        printf("arr2 -> %2d\n", is_sorted_type(arr2, 9));
        printf("arr3 -> %2d\n", is_sorted_type(arr3, 9));
        printf("arr4 -> %2d\n", is_sorted_type(arr4, 9));

    // Exercício 14
        puts("\nEXERCICIO 14");

        char str1[] = "course the gerg";
        char str2[] = "het source ergg";
        char str3[] = "course the gerr";

        if (is_anagram(str1, str2))
            puts("true");
        else
            puts("false");

        if (is_anagram(str2, str3))
            puts("true");
        else
            puts("false");

    // Exercício 15
        puts("\nEXERCICIO 15");
        printf("professor -> %d\n", repeated_char("professor"));
        printf("belazurin -> %d\n", repeated_char("belazurin"));

    // Exercício 05
        puts("\nEXERCICIO 05");
        printf("\nH = %.2lf\n", harmonics(1));
        printf("\nH = %.2lf\n", harmonics(2));
        printf("\nH = %.2lf\n", harmonics(10));
        printf("\nH = %.2lf\n", harmonics(23));

    // Exercício ..
        puts("\nEXERCICIO ..");
        eleitor(13);
        eleitor(16);
        eleitor(28);
        eleitor(77);

    // Exercício ..
        puts("\nEXERCICIO ..");
        int n = 5;
        printf("Fatorial de %2d! = %d\n", n, factorial(n));
        n = 10;
        printf("Fatorial de %2d! = %d\n", n, factorial(n));

    // Exercício ..
        puts("\nEXERCICIO ..");
        for (size_t i = 19; i < 40; i++) {
            printf("[%d] => |%d|\n", i, is_prime(i));
        }
    
    // Exercício ..
        puts("\nEXERCICIO ..");
        n = 5;
        printf("Soma dos fatorias de %2d! = %d\n", n, sum_factorial(n));
        n = 10;
        printf("Soma dos fatorias de %2d! = %d\n", n, sum_factorial(n));

    // Exercício ..
        puts("\nEXERCICIO ..");
        
        int size = HUN_THOUSAND;
        int* vetor = createArray(size);

        srand(time(NULL));
        for (int i=0; i<size; i++) {
            vetor[i] = rand() % 1000;
        }

        int elemento = rand() % 1000;
        printf("O elemento %3d aparece %3d vezes\n", elemento, freq_vector(vetor, size, elemento));
        
        elemento = rand() % 1000;
        printf("O elemento %3d aparece %3d vezes\n", elemento, freq_vector(vetor, size, elemento));

        free(vetor);

    return 0;
}
