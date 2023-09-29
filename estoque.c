#include "tools.h"

//-------------------------------------------------------------------------------------------------------------//

    // Definição de Constantes

    #define NOME_LEN 100
    #define PRODUTOS "PRODUTOS"
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
    Produto* CriaProduto() {
        Produto* produto = (Produto *) calloc(1, sizeof(Produto));

        if (!produto) return NULL;

        produto->proximo = NULL;
        
        return produto;
    }

    //
    // Retorna um Produto preenchido
    //
    Produto* CriaProdutoArgs(natural cod,
                             string nome,
                             natural qtde,
                             double preco) {
        
        Produto* produto = (Produto *) calloc(1, sizeof(Produto));

        if (!produto) return NULL;

        strcpy(produto->nome, nome);
        
        produto->codigo = cod;
        produto->quantidade = qtde;
        produto->preco = preco;

        produto->proximo = NULL;
        
        return produto;
    }

    //
    // Retorna uma Lista de Produtos
    //
    Lista_de_Produtos* CriaListaProdutos(size_t max) {
        Lista_de_Produtos* lista = (Lista_de_Produtos *) calloc(1, sizeof(Lista_de_Produtos));

        if (!lista) return NULL;

        lista->primeiro = NULL;
        lista->ultimo   = NULL;
        lista->tamanho  = 0;
        lista->max      = max;

        return lista;
    }

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

    //
    // Exibe um Produto formatado para o console
    //
    void ExibeProduto(Produto* produto) {
        printf("\n Codigo     : %2d",    produto->codigo);
        printf("\n Nome       : %s",     produto->nome);
        printf("\n Quantidade : %3d",    produto->quantidade);
        printf("\n Preco     R$ %5.2lf", produto->preco);
        puts("\n========================================");
    }

    //
    // Retorna um ponteiro para o Produto com o código passado, ou NULL
    //
    Produto* ProdutoPorCodigo(Lista_de_Produtos* lista, natural cod) {
        Produto* aux = lista->primeiro;
        while (aux) {
            if (aux->codigo == cod)
                return aux;
            aux = aux->proximo;
        }
        return NULL;
    }
    
    //
    // Retorna um ponteiro para o Produto com o nome passado, ou NULL
    //
    Produto* ProdutoPorNome(Lista_de_Produtos* lista, string nome) {
        Produto* aux = lista->primeiro;
        while (aux) {
            if (!strcmp(aux->nome, nome))
                return aux;
            aux = aux->proximo;
        }
        return NULL;
    }

    //
    // Retorna uma cópia profunda de um Produto
    //
    Produto* ClonaProduto(Produto* produto) {
        return CriaProdutoArgs(produto->codigo, produto->nome, produto->quantidade, produto->preco);
    }

    //
    // Retorna true se o nome digitado for válido
    //
    bool NomeInput(string nome) {
        do { // hast
            
            printf("\nDigite o nome: ");
            fgets(nome, NOME_LEN, stdin);
            nome[strcspn(nome, "\n")] = 0;

            if (!strcmp(nome, "0")) return false;

            return true;

        } while (true);
    }

//-------------------------------------------------------------------------------------------------------------//

    // CRUD

    //
    // Procura um Produto com o código informado e exibe na tela, ou simplesmente não exibe nada
    //
    void ExibeProdutoPorCodigo(Lista_de_Produtos* lista) {
        printf("\nDigite o codigo: ");
        int input = Int();

        if (input < 0) return;

        Produto* aux = ProdutoPorCodigo(lista, (natural)input);

        if (!aux) {
            puts("\nNao foi encontrado produto com o codigo especificado...");
            return;
        }

        ExibeProduto(aux);
    }

    //
    // Procura um Produto com o nome informado e exibe na tela, ou simplesmente não exibe nada
    //
    void ExibeProdutoPorNome(Lista_de_Produtos* lista) {
        char input [NOME_LEN];

        if (!NomeInput(input)) return;

        Produto* aux = ProdutoPorNome(lista, input);

        if (!aux) {
            puts("\nNao foi encontrado produto com o nome especificado...");
            return;
        }

        ExibeProduto(aux);
    }

    //
    // Exibe toda uma Lista de Produtos
    //
    void ExibeTodosProdutos(Lista_de_Produtos* lista) {
        Produto* produto = lista->primeiro;
        while (produto) {
            ExibeProduto(produto);
            putchar('\n');
            produto = produto->proximo;
        }
    }

    //
    // Retorna um novo produto cadastrado, ou NULL
    //
    Produto* NovoProduto(Lista_de_Produtos* lista) {
        char nome [NOME_LEN];

        cleanScreen();

        printf("\nDigite o codigo: ");
        int cod = Int();

        if (cod < 0) return NULL;

        if (ProdutoPorCodigo(lista, (natural)cod)) {
            puts("\nO codigo informado ja se encontra cadastrado no sistema...");
            return NULL;
        }

        if (!NomeInput(nome)) return NULL;

        printf("\nDigite a quantidade: ");
        int qtde = Int();

        if (qtde < 0) return NULL;

        printf("\nDigite o preco: ");
        double preco = Double();

        if (preco < 0) return NULL;

        return CriaProdutoArgs((natural)cod, nome, (natural)qtde, preco);
    }

    //
    // Insere um Produto na última posição da lista
    //
    void InsereProdutoNalista(Lista_de_Produtos* lista, Produto* produto) {
        if (!produto) return;

        if (!lista->primeiro) {
            lista->primeiro = produto;
            lista->ultimo = produto;
            lista->tamanho++;
            return;
        }

        Produto* aux = lista->primeiro;

        while (aux->proximo)
            aux = aux->proximo;
        
        aux->proximo = produto;
        
        lista->ultimo = produto;
        lista->tamanho++;
    }

    //
    // Encapsula a inserção na Lista
    //
    void Insereproduto(Lista_de_Produtos* lista) {
        if (!lista) return;

        if (lista->tamanho >= lista->max) {
            puts("\nLista Cheia!!!");
            return;
        }

        InsereProdutoNalista(lista, NovoProduto(lista));
    }

    //
    //
    //

//-------------------------------------------------------------------------------------------------------------//

    // Manipulação de Arquivos

    //
    // Registra Produtos em um arquivo PRODUTOS
    //
    void PersistenciaProdutos(Lista_de_Produtos* lista) {
        if (!lista) return;

        FILE* file;
        Produto* aux = lista->primeiro;

        file = fopen(PRODUTOS, "wb");

        if (!file) {
            fprint_err(PRODUTOS);
            return;
        }

        for (size_t i = 0; i < lista->tamanho; i++) {
            fwrite(aux, sizeof(Produto), 1, file);
            aux = aux->proximo;
        }

        fclose(file);
    }

    //
    // Lê o arquivo PRODUTOS e retorna uma lista de Produtos de tamanho padrão com os dados obtidos
    //
    Lista_de_Produtos* ReadProdutos() {
        FILE* file;
        Produto produto;
        Lista_de_Produtos* lista = CriaListaProdutos(10);

        file = fopen(PRODUTOS, "rb");
        if (!file) {
            fprint_err(PRODUTOS);
            return lista;
        }

        fread(&produto, sizeof(Produto), 1, file);
        while (!feof(file)) {
            InsereProdutoNalista(lista, ClonaProduto(&produto));
            fread(&produto, sizeof(Produto), 1, file);
        }

        fclose(file);
        return lista;
    }

//-------------------------------------------------------------------------------------------------------------//

    //
    // Submenu de produtos
    //
    void MenuProdutos(Lista_de_Produtos* lista) {
        int opc;

        do { // hast
            cleanScreen();

            puts("=======================");
            puts("ESTOQUE\n");
            puts(" 1 - Cadastrar");
            puts(" 2 - Exibir Um");
            puts(" 3 - Exibir Todos");
            puts(" 4 - Atualizar");
            puts(" 5 - Remover");
            puts(" 0 - Sair\n");
            printf("Escolha: ");
            opc = getchar(); clearBuffer();

            switch (opc) {
                case '1':      Insereproduto(lista); pause(); break;
                case '2':                            pause(); break;
                case '3': ExibeTodosProdutos(lista); pause(); break;
                case '4':                                     break;
                case '5':                            pause(); break;
                case '0':                                     break;
                default :    puts("\n INVALIDO!!!"); pause(); break;
            }

        } while (opc != '0');
    }

    //
    // Apaga completamente uma lista de Produtos
    //
    void FreeEstoque(Lista_de_Produtos* lista) {
        Produto* aux = lista->primeiro;
        Produto* temp;

        while (aux) {
            temp = aux;
            aux = aux->proximo;
            free(temp);
        }

        free(lista);
    }