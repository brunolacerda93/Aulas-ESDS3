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

    //
    // Retorna um Produto não preenchido
    //
    Produto* CriaProduto();

    //
    // Retorna um Produto preenchido
    //
    Produto* CriaProdutoArgs(natural cod,
                             string nome,
                             natural qtde,
                             double preco);

    //
    // Retorna uma Lista de Produtos
    //
    Lista_de_Produtos* CriaListaProdutos();

    //
    // Retorna uma Lista de Produtos com tamanho máximo definido
    //
    Lista_de_Produtos* CriaListaProdutosArgs(size_t max);

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

    //
    // Exibe um Produto formatado para o console
    //
    void ExibeProduto(Produto* produto);

    //
    // Retorna um ponteiro para o Produto com o código passado, ou NULL
    //
    Produto* ProdutoPorCodigo(Lista_de_Produtos* lista, natural cod);
    
    //
    // Retorna um ponteiro para o Produto com o nome passado, ou NULL
    //
    Produto* ProdutoPorNome(Lista_de_Produtos* lista, string nome);

    //
    // Exibe uma lista de Produtos com quantidade menor ou igual à informada
    //
    void ExibeProdutosPorQtde(Lista_de_Produtos* lista);

    //
    // Exibe uma lista de Produtos com preço menor ou igual ao informado
    //
    void ExibeProdutosPorPreco(Lista_de_Produtos* lista);

    //
    // Retorna uma cópia profunda de um Produto
    //
    Produto* ClonaProduto(Produto* produto);

    //
    // Retorna true se o nome digitado for válido
    //
    bool NomeInput(string nome);

    //
    // Tela para administrar a exibição de um ou mais Produtos
    //
    void TelaProdutos(Lista_de_Produtos* lista);

//-------------------------------------------------------------------------------------------------------------//

    // CRUD

    //
    // Procura um Produto com o código informado e exibe na tela, ou simplesmente não exibe nada
    //
    void ExibeProdutoPorCodigo(Lista_de_Produtos* lista);

    //
    // Procura um Produto com o nome informado e exibe na tela, ou simplesmente não exibe nada
    //
    void ExibeProdutoPorNome(Lista_de_Produtos* lista);

    //
    // Exibe toda uma Lista de Produtos
    //
    void ExibeTodosProdutos(Lista_de_Produtos* lista);

    //
    // Retorna um novo produto cadastrado, ou NULL
    //
    Produto* NovoProduto(Lista_de_Produtos* lista);

    //
    // Insere um Produto na última posição da lista
    //
    void InsereProdutoNalista(Lista_de_Produtos* lista, Produto* produto);

    //
    // Encapsula a inserção na Lista
    //
    void Insereproduto(Lista_de_Produtos* lista);

    //
    // Atualiza as informações de um Produto com o codigo informado
    //
    void AtualizaProduto(Lista_de_Produtos* lista);
    
    //
    // Remove um produto com o codigo informado
    //
    void RemoveProduto(Lista_de_Produtos* lista);

//-------------------------------------------------------------------------------------------------------------//

    // Ordenação

    //
    // Bubble Sort que ordena o Estoque por codigo de forma crescente
    //
    void bubbleSort_codigo(Lista_de_Produtos* lista);

    //
    // Bubble Sort que ordena o Estoque por nome em ordem alfabética
    //
    void bubbleSort_nome(Lista_de_Produtos* lista);

    //
    // Bubble Sort que ordena o Estoque por quantidade de forma crescente
    //
    void bubbleSort_qtde_c(Lista_de_Produtos* lista);

    //
    // Bubble Sort que ordena o Estoque por quantidade de forma decrescente
    //
    void bubbleSort_qtde_d(Lista_de_Produtos* lista);

    //
    // Bubble Sort que ordena o Estoque por preco de forma crescente
    //
    void bubbleSort_preco_c(Lista_de_Produtos* lista);

    //
    // Bubble Sort que ordena o Estoque por preco de forma decrescente
    //
    void bubbleSort_preco_d(Lista_de_Produtos* lista);

    //
    // Encapsula a ordenação
    //
    void ExibeOrdenado(Lista_de_Produtos* lista);

//-------------------------------------------------------------------------------------------------------------//

    // Manipulação de Arquivos

    //
    // Registra Produtos em um arquivo PRODUTOS
    //
    void PersistenciaProdutos(Lista_de_Produtos* lista);

    //
    // Lê o arquivo PRODUTOS e retorna uma lista de Produtos de tamanho padrão com os dados obtidos
    //
    Lista_de_Produtos* ReadProdutos();

//-------------------------------------------------------------------------------------------------------------//

    //
    // Submenu de produtos
    //
    void MenuProdutos(Lista_de_Produtos* lista);

    //
    // Breve Menu para salvar ou não as alterações
    //
    int LogOff(Lista_de_Produtos* lista);

    //
    // Apaga completamente uma lista de Produtos
    //
    void FreeEstoque(Lista_de_Produtos* lista);