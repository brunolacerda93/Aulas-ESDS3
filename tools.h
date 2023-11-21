#ifndef tools_H
#define tools_H

//-------------------------------------------------------------------------------------------------------------//

  // Bibliotecas

  #include <time.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <locale.h>

//-------------------------------------------------------------------------------------------------------------//

  // Definindo tipos

  typedef enum bool { false, true } bool;
  typedef unsigned int uint;
  typedef char* string;
  typedef void* var;

  // Definindo constantes

  #define HUN_THOUSAND 100000
  #define ONE_MILLION  1000000
  #define TEN_MILLION  10000000

//-------------------------------------------------------------------------------------------------------------//
  
  // MACROS

  //
  // MACRO para funções não implementadas
  //--------------------------------------------
  //
  #define UNIMPLEMENTED \
    do { \
      fprintf(stderr, "\n%s:%d: %s is not implemented yet...\n\n", \
              __FILE__, __LINE__, __func__); \
      abort(); \
    } while (0)

  //
  // MACRO para exibir o nome da função
  //----------------------------------------
  //
  #define CALLING printf("\n\n||===== Calling: %s =====||\n", __func__)

  //
  // MACRO para texto padrão de erro
  //-------------------------------------
  //
  #define FERROR "Erro ao abrir "

  //
  // MACRO para retornar o maior valor
  //---------------------------------------
  //
  #define max(a, b)  (((a) >= (b)) ? (a) : (b))

//-------------------------------------------------------------------------------------------------------------//

  // FUNÇÕES E MÉTODOS

  //
  // Define o padrão UTF8 para os caracteres do terminal
  //
  void Locale() { setlocale(LC_ALL, ".UTF8"); }

  //
  // Limpa o buffer de entrada
  //
  void clearBuffer() { while(getchar() != '\n') {} }

  //
  // Pausa e espera um input
  //
  void pause() { fputs("\nPressione <enter> para continuar... ", stdout); getchar(); }

  //
  // Limpa a tela do console
  //
  void cleanScreen() { fputs("\e[1;1H\e[2J", stdout); }

  //
  // Retorna um ponteiro para uma string vazia do tamanho passado como argumento
  //
  string String(const size_t size) { return (string) calloc(size, sizeof(char)); }

  //
  // Troca o conteúdo de dois ponteiros
  //
  void
  swap_void(var n1, var n2, size_t size) {
    var temp = calloc(1, size);

    memcpy(temp, n1, size);
    memcpy(n1,   n2, size);
    memcpy(n2, temp, size);

    free(temp);
  }

  //
  // Troca dois inteiros por endereço
  //
  void
  swap(int* n1, int* n2) {
    int temp;
    temp = *n1;
    *n1  = *n2;
    *n2  = temp;
  }

  //
  // Troca dois inteiros por endereço "inline"
  //
  static __attribute__((__always_inline__)) inline void
  swap_inline(int* n1, int* n2) {
    int temp;
    temp = *n1;
    *n1  = *n2;
    *n2  = temp;
  }

  //
  // Retorna true se a hora é válida
  //
  bool
  isValidTime(const int hour, const int min, const int sec) {
    if (hour < 0 || hour > 24)
      return false;

    if (min < 0 || min > 59)
      return false;

    if (sec < 0 || sec > 59)
      return false;

    return true;
  }

  //
  // Captura a entrada de um inteiro
  //
  int
  Int() {
    int num  = 0;
    int sign = 1;
    int c;

    while ((c = getchar()) != '\n') {
      if (c == '-')
        sign = -1;

      else if (c >= '0' && c <= '9')
        num = num * 10 + (c - '0');
    }

    return num * sign;
  }

  //
  // Captura a entrada de um double
  //
  double
  Double() {
    char input[100];
    fgets(input, 100, stdin);

    return strtod(input, NULL);
  }

  //
  // Formata o CPF para exibição
  //
  void
  PrintCPF(string cpf) {
    size_t i = 0;

    while (cpf[i] != '\0') {
      putchar(cpf[i]);

      switch(i++) {
        case 2:
        case 5: putchar('.'); break;
        case 8: putchar('/'); break;
      }
    }
  }

  //
  // Formata a Placa do Veículo para exibição
  //
  void
  PrintPlaca(string placa) {
    size_t i = 0;

    while (placa[i] != '\0') {
      if (i == 3) putchar('-');
      putchar(placa[i++]);
    }
  }

  //
  // Exibe a mensagem de erro no Console
  //
  void
  fprint_err(string Filename) {
    string error = String(50);
    strcat(error, FERROR);
    strcat(error, Filename);
    perror(error);
    free(error);
  }

  //
  // Algoritmo utilizado no jogo Quake 3 para o cálculo do inverso da raiz quadrada de um número
  //
  float
  fast_inverse_sqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = * (long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (threehalfs - ( x2 * y * y ));  // can be repeated N times for more precision
    y = y * (threehalfs - ( x2 * y * y ));  // two repetitions already reach float's maximum precision

    return y;
  }

#endif
