#include "../tools.h"

//-------------------------------------------------------------------------------------------------------------//

    // Definição de Constantes

    #define NOME_LEN 100
    #define PRODUTOS "PRODUTOS"
    #define DEFAULT_SIZE 10
    
    typedef unsigned int natural;

//-------------------------------------------------------------------------------------------------------------//

    // Estrutura dos tipos

    typedef struct Produto {

        natural codigo;
        char    nome [NOME_LEN];
        natural quantidade;
        double  preco;
        struct  Produto* proximo;

    } Produto;

    typedef struct Lista_de_Produtos {

        Produto* primeiro;
        Produto* ultimo;
        size_t   tamanho;
        size_t   max;

    } Lista_de_Produtos;

//-------------------------------------------------------------------------------------------------------------//

    // Construtores

    Produto*           CriaProduto();
    Produto*           CriaProdutoArgs(natural, string, natural, double);
    Lista_de_Produtos* CriaListaProdutos();
    Lista_de_Produtos* CriaListaProdutosArgs(size_t);

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

    bool     NomeInput             (string);
    void     TelaProdutos          (Lista_de_Produtos*);
    void     ExibeProduto          (Produto*);
    void     ExibeProdutosPorQtde  (Lista_de_Produtos*);
    void     ExibeProdutosPorPreco (Lista_de_Produtos*);
    Produto* ClonaProduto          (Produto*);
    Produto* ProdutoPorNome        (Lista_de_Produtos*, string);
    Produto* ProdutoPorCodigo      (Lista_de_Produtos*, natural);

//-------------------------------------------------------------------------------------------------------------//

    // CRUD

    void     ExibeProdutoPorCodigo (Lista_de_Produtos*);
    void     ExibeProdutoPorNome   (Lista_de_Produtos*);
    void     ExibeTodosProdutos    (Lista_de_Produtos*);
    void     InsereProduto         (Lista_de_Produtos*);
    void     AtualizaProduto       (Lista_de_Produtos*);
    void     RemoveProduto         (Lista_de_Produtos*);
    void     InsereProdutoNalista  (Lista_de_Produtos*, Produto*);
    Produto* NovoProduto           (Lista_de_Produtos*);

//-------------------------------------------------------------------------------------------------------------//

    // Ordenação

    void bubbleSort_codigo  (Lista_de_Produtos*);
    void bubbleSort_nome    (Lista_de_Produtos*);
    void bubbleSort_qtde_c  (Lista_de_Produtos*);
    void bubbleSort_qtde_d  (Lista_de_Produtos*);
    void bubbleSort_preco_c (Lista_de_Produtos*);
    void bubbleSort_preco_d (Lista_de_Produtos*);
    void ExibeOrdenado      (Lista_de_Produtos*);

//-------------------------------------------------------------------------------------------------------------//

    // Manipulação de Arquivos

    void PersistenciaProdutos(Lista_de_Produtos*);
    Lista_de_Produtos* ReadProdutos();

//-------------------------------------------------------------------------------------------------------------//

    int  LogOff       (Lista_de_Produtos*);
    void MenuProdutos (Lista_de_Produtos*);
    void FreeEstoque  (Lista_de_Produtos*);