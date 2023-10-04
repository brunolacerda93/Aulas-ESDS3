#include "../tools.h"

//-------------------------------------------------------------------------------------------------------------//

    // Definição de Constantes

    #define NOME_LEN 100
    #define GERAL 'g'
    #define PREF 'p'

//-------------------------------------------------------------------------------------------------------------//

    // Estrutura dos tipos

    typedef struct Cliente {

        char nome[NOME_LEN];
        int  pref;
        struct Cliente* prox;

    } Cliente;

    typedef struct Fila_Banco {

        Cliente* primeiro;
        Cliente* ultimo;
        size_t   tamanho;

    } Fila_Banco;

//-------------------------------------------------------------------------------------------------------------//

    // Construtores

    Cliente* CriaCliente();
    Cliente* CriaClienteArgs(string, int);
    Fila_Banco* CriaFilaBanco();

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

    void ExibeFila(Fila_Banco*);
    Cliente* ClonaCliente(Cliente*);
    bool NomeInput(string);

//-------------------------------------------------------------------------------------------------------------//

    // Tratamento das Filas

    int Desenfilerar(Fila_Banco*);
    void Enfileirar(Fila_Banco*, Cliente*);
    void InsereNaFila(Fila_Banco*, Fila_Banco*);
    Fila_Banco* FilaAtendimento(Fila_Banco*, Fila_Banco*);
    void RemoveDaFila(Fila_Banco*, Fila_Banco*, Fila_Banco*);

//-------------------------------------------------------------------------------------------------------------//

    void MenuBanco();
    void FreeFila(Fila_Banco*);