#include "estoque.h"

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
    Produto* CriaProdutoArgs(uint   cod,
                             string nome,
                             uint   qtde,
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
    Lista_de_Produtos* CriaListaProdutos() {
        Lista_de_Produtos* lista = (Lista_de_Produtos *) calloc(1, sizeof(Lista_de_Produtos));

        if (!lista) return NULL;

        lista->primeiro = NULL;
        lista->ultimo   = NULL;
        lista->tamanho  = 0;
        lista->max      = DEFAULT_SIZE;

        return lista;
    }

    //
    // Retorna uma Lista de Produtos com tamanho máximo definido
    //
    Lista_de_Produtos* CriaListaProdutosArgs(size_t max) {
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
        printf("\n Codigo     : %02d",    produto->codigo);
        printf("\n Nome       : %s",     produto->nome);
        printf("\n Quantidade : %2d",    produto->quantidade);
        printf("\n Preco     R$ %5.2lf", produto->preco);
        puts("\n========================================");
    }

    //
    // Retorna um ponteiro para o Produto com o código passado, ou NULL
    //
    Produto* ProdutoPorCodigo(Lista_de_Produtos* lista, int cod) {
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

    //
    // Tela para administrar a exibição de um ou mais Produtos
    //
    void TelaProdutos(Lista_de_Produtos* lista) {
        int opc;

        do { // hast
            cleanScreen();

            puts("\nSelecione:");
            puts(" Codigo     [c/C]");
            puts(" Nome       [n/N]");
            puts(" Quantidade [q/Q]");
            puts(" Preco      [p/P]");
            printf(" >> ");

            opc = getchar(); clearBuffer();
            if (opc == '0') return;

            switch (opc) {
                case 'c': case 'C': ExibeProdutoPorCodigo(lista); break;
                case 'n': case 'N':   ExibeProdutoPorNome(lista); break;
                case 'q': case 'Q':  ExibeProdutosPorQtde(lista); break;
                case 'p': case 'P': ExibeProdutosPorPreco(lista); break;
                default : puts("\n INVALIDO!!!"); break;
            }

            pause();

        } while(1);
    }

//-------------------------------------------------------------------------------------------------------------//

    // CRUD

    //
    // Procura um Produto com o código informado e exibe na tela, ou simplesmente não exibe nada
    //
    void ExibeProdutoPorCodigo(Lista_de_Produtos* lista) {
        printf("\nDigite o codigo: ");
        int input = Int();

        if (input <= 0) return;

        Produto* aux = ProdutoPorCodigo(lista, input);

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
    // Exibe uma lista de Produtos com quantidade menor ou igual à informada
    //
    void ExibeProdutosPorQtde(Lista_de_Produtos* lista) {
        printf("\nDigite a quantidade: ");
        int input = Int();

        if (input <= 0) return;

        Lista_de_Produtos* filtrada = CriaListaProdutos(lista->tamanho);

        bubbleSort_qtde_c(lista);

        Produto* aux = lista->primeiro;

        while (aux) {
            if (aux->quantidade <= input)
                InsereProdutoNalista(filtrada, ClonaProduto(aux));
            aux = aux->proximo;
        }

        ExibeTodosProdutos(filtrada);

        FreeEstoque(filtrada);
    }

    //
    // Exibe uma lista de Produtos com preço menor ou igual ao informado
    //
    void ExibeProdutosPorPreco(Lista_de_Produtos* lista) {
        printf("\nDigite o preco: ");
        double input = Double();

        if (input <= 0) return;

        Lista_de_Produtos* filtrada = CriaListaProdutos(lista->tamanho);

        bubbleSort_preco_c(lista);

        Produto* aux = lista->primeiro;

        while (aux) {
            if (aux->preco <= input)
                InsereProdutoNalista(filtrada, ClonaProduto(aux));
            aux = aux->proximo;
        }

        ExibeTodosProdutos(filtrada);

        FreeEstoque(filtrada);
    }

    //
    // Exibe toda uma Lista de Produtos
    //
    void ExibeTodosProdutos(Lista_de_Produtos* lista) {
        Produto* produto = lista->primeiro;

        printf("\nTamanho: %ld\n", lista->tamanho);

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

        if (cod <= 0) return NULL;

        if (ProdutoPorCodigo(lista, cod)) {
            puts("\nO codigo informado ja se encontra cadastrado no sistema...");
            return NULL;
        }

        if (!NomeInput(nome)) return NULL;

        printf("\nDigite a quantidade: ");
        int qtde = Int();

        if (qtde <= 0) return NULL;

        printf("\nDigite o preco: ");
        double preco = Double();

        if (preco < 0) return NULL;

        return CriaProdutoArgs((uint)cod, nome, (uint)qtde, preco);
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

        lista->ultimo->proximo = produto;
        lista->ultimo = produto;
        lista->tamanho++;
    }

    //
    // Encapsula a inserção na Lista
    //
    void InsereProduto(Lista_de_Produtos* lista) {
        if (!lista) return;

        if (lista->tamanho >= lista->max) {
            puts("\nLista Cheia!!!");
            return;
        }

        InsereProdutoNalista(lista, NovoProduto(lista));
    }

    //
    // Atualiza as informações de um Produto com o codigo informado
    //
    void AtualizaProduto(Lista_de_Produtos* lista) {
        printf("\nDigite o codigo: ");
        int cod = Int();

        if (cod < 0) return;

        Produto* aux = ProdutoPorCodigo(lista, cod);

        if (!aux) {
            puts("\nProduto nao encontrado...");
            pause();
            return;
        }

        int opc;
        do { // hast
    	    cleanScreen();
            ExibeProduto(aux);

            puts("O que deseja alterar?\n");
            puts(" 1 - Nome");
            puts(" 2 - Quantidade");
            puts(" 3 - Preco");
            puts(" 0 - Retornar");
            printf("\nEscolha: ");
            opc = getchar(); clearBuffer();

            if (opc == '0') break;

            if (opc < '1' || opc > '3') {
                puts("\nINVALIDO!!!");
                pause();
                continue;
            }

            switch (opc) {
                case '1': {
                    string str = String(NOME_LEN);
                    
                    if (NomeInput(str))
                        strcpy(aux->nome, str);
                    
                    free(str);
                } break;
                case '2': {
                    printf("\nDigite a quantidade: ");
                    int qtde = Int();

                    if (qtde < 0) break;

                    aux->quantidade = (uint)qtde;
                } break;
                case '3': {
                    printf("\nDigite o preco: ");
                    double preco = Double();

                    if (preco < 0) break;

                    aux->preco = preco;
                } break;
                default : break;
            }

        } while(1);
    }
    
    //
    // Remove um produto com o codigo informado
    //
    void RemoveProduto(Lista_de_Produtos* lista) {
        printf("\nDigite o codigo: ");
        int cod = Int();

        if (cod < 0) return;

        Produto* anterior = NULL;
        Produto* atual    = lista->primeiro;

        while (atual && atual->codigo != cod) {
            anterior = atual;
            atual = atual->proximo;
        }

        if ((!anterior && atual->codigo != cod) || !atual) {
            puts("\nNao existe produto com o codigo informado no sistema...");
            return;
        }

        ExibeProduto(atual);
        printf("\nTem certeza? [s/S]: ");
        int opc = getchar(); clearBuffer();

        if (opc != 's' && opc != 'S')
            return;
        
        if (!anterior) {
            Produto* temp = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(temp);
        }
        else {
            anterior->proximo = atual->proximo;
            free(atual);
        }

        lista->tamanho--;
        puts("\n\t Removido!");
    }

//-------------------------------------------------------------------------------------------------------------//

    // Ordenação

    //
    // Bubble Sort que ordena o Estoque por codigo de forma crescente
    //
    void bubbleSort_codigo(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (p1->codigo > p2->codigo) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Bubble Sort que ordena o Estoque por nome em ordem alfabética
    //
    void bubbleSort_nome(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (strcmp(p1->nome, p2->nome) > 0) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Bubble Sort que ordena o Estoque por quantidade de forma crescente
    //
    void bubbleSort_qtde_c(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (p1->quantidade > p2->quantidade) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Bubble Sort que ordena o Estoque por quantidade de forma decrescente
    //
    void bubbleSort_qtde_d(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (p1->quantidade < p2->quantidade) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Bubble Sort que ordena o Estoque por preco de forma crescente
    //
    void bubbleSort_preco_c(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (p1->preco > p2->preco) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Bubble Sort que ordena o Estoque por preco de forma decrescente
    //
    void bubbleSort_preco_d(Lista_de_Produtos* lista) {
        Produto** head;
        bool swapped;

        for (size_t i = 0; i < lista->tamanho; i++) {
            head = &lista->primeiro;
            swapped = false;

            for (size_t j = 0; j < lista->tamanho - i - 1; j++) {
                Produto* p1 = *head;
                Produto* p2 = p1->proximo;

                if (p1->preco < p2->preco) {
                    Produto* temp = p2->proximo;
                    p2->proximo = p1;
                    p1->proximo = temp;
                    *head = p2;
                    swapped = true;
                }

                head = &(*head)->proximo;
            }

            if (!swapped) break;
        }
    }

    //
    // Encapsula a ordenação
    //
    void ExibeOrdenado(Lista_de_Produtos* lista) {
        int opc;

        do { // hast
            cleanScreen();

            puts("\nOrdernar por:");
            puts(" 1 - Codigo");
            puts(" 2 - Nome");
            puts(" 3 - Quantidade Crescente");
            puts(" 4 - Quantidade Decrescente");
            puts(" 5 - Preco Crescente");
            puts(" 6 - Preco Decrescente");
            puts(" 0 - Retorna");
            printf(" >> ");

            opc = getchar(); clearBuffer();
            if (opc == '0') return;

            switch(opc) {
                case '1':  bubbleSort_codigo(lista); break;
                case '2':    bubbleSort_nome(lista); break;
                case '3':  bubbleSort_qtde_c(lista); break;
                case '4':  bubbleSort_qtde_d(lista); break;
                case '5': bubbleSort_preco_c(lista); break;
                case '6': bubbleSort_preco_d(lista); break;
                case '0': return;
                default : puts("\n INVALIDO!!!"); pause(); continue;
            }

            ExibeTodosProdutos(lista);

            pause();

        } while(1);
    }

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

        while (aux) {
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
        Lista_de_Produtos* lista = CriaListaProdutos();

        file = fopen(PRODUTOS, "rb");
        if (!file) {
            fprint_err(PRODUTOS);
            return lista;
        }

        fread(&produto, sizeof(Produto), 1, file);
        while (!feof(file)) {
            if (lista->tamanho == lista->max) lista->max++;
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
            puts(" 4 - Ordenar");
            puts(" 5 - Atualizar");
            puts(" 6 - Remover");
            puts(" 0 - Sair\n");
            printf("Escolha: ");
            opc = getchar(); clearBuffer();

            switch (opc) {
                case '1':      InsereProduto(lista); pause(); break;
                case '2':       TelaProdutos(lista);          break;
                case '3': ExibeTodosProdutos(lista); pause(); break;
                case '4':      ExibeOrdenado(lista); pause(); break;
                case '5':    AtualizaProduto(lista);          break;
                case '6':      RemoveProduto(lista); pause(); break;
                case '0':       opc = LogOff(lista); pause(); break;
                default :    puts("\n INVALIDO!!!"); pause(); break;
            }

        } while (opc != '0');
    }

    //
    // Breve Menu para salvar ou não as alterações
    //
    int LogOff(Lista_de_Produtos* lista) {
        puts("\nDeseja salvar as alteracoes?");
        puts("Digite qualquer tecla para voltar");
        puts("   1 = SIM  ||  0 = NAO");
        printf(" >> ");
        int opc = getchar(); clearBuffer();

        if (opc == '1') {
            PersistenciaProdutos(lista);
            return '0';
        }

        return opc;
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