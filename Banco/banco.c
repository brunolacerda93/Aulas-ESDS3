#include "banco.h"

//-------------------------------------------------------------------------------------------------------------//

    // Construtores

    //
    // Retorna um Cliente não preenchido
    //
    Cliente* CriaCliente() {
        Cliente* cliente = (Cliente *) calloc(1, sizeof(Cliente));

        if (!cliente) return NULL;

        cliente->pref = GERAL;
        cliente->prox = NULL;

        return cliente;
    }

    //
    // Retorna um Cliente preenchido
    //
    Cliente* CriaClienteArgs(string nome, int pref) {
        Cliente* cliente = (Cliente *) calloc(1, sizeof(Cliente));

        if (!cliente) return NULL;

        strcpy(cliente->nome, nome);
        cliente->pref = pref;
        cliente->prox = NULL;

        return cliente;
    }

    //
    // Retorna uma Fila de Clientes
    //
    Fila_Banco* CriaFilaBanco() {
        Fila_Banco* fila = (Fila_Banco *) calloc(1, sizeof(Fila_Banco));

        if (!fila) return NULL;

        fila->primeiro = NULL;
        fila->ultimo   = NULL;
        fila->tamanho  = 0;

        return fila;
    }

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

    //
    //
    //
    void ExibeFila(Fila_Banco* fila) {
        Cliente* aux = fila->primeiro;

        if (!aux) puts("vazia");

        while (aux) {
            printf("> %s ", aux->nome);
            aux = aux->prox;
        }
        puts("\n");
    }

    //
    // Retorna uma cópia profunda de um Cliente
    //
    Cliente* ClonaCliente(Cliente* cliente) {
        return CriaClienteArgs(cliente->nome, cliente->pref);
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

    // Tratamento das Filas

    //
    // Insere um elemento no fim da fila
    //
    void Enfileirar(Fila_Banco* fila, Cliente* cliente) {
        if (!cliente) return;

        if (!fila->primeiro) {
            fila->primeiro = cliente;
            fila->ultimo = cliente;
            fila->tamanho++;
            return;
        }

        fila->ultimo->prox = cliente;
        fila->ultimo = cliente;
        fila->tamanho++;
    }

    //
    // Administra a inserção na fila
    //
    void InsereNaFila(Fila_Banco* fila_geral, Fila_Banco* fila_pref) {
        char nome[NOME_LEN];

        cleanScreen();

        if (!NomeInput(nome)) return;

        do { // hast
            cleanScreen();

            puts("Preferencial [p/P]");
            puts("Geral        [g/G]");
            printf(" >> ");

            int opc = getchar(); clearBuffer();

            switch (opc) {
                case 'p': case 'P': Enfileirar(fila_pref,  CriaClienteArgs(nome, 'p')); break;
                case 'g': case 'G': Enfileirar(fila_geral, CriaClienteArgs(nome, 'g')); break;
                case '0': return;
                default : puts("\n INVALIDO!!!"); pause(); continue;
            }

        } while (0);
    }

    //
    // Retorna a fila de Atendimento
    //
    Fila_Banco* FilaAtendimento(Fila_Banco* fila_geral, Fila_Banco* fila_pref) {
        Fila_Banco* fila = CriaFilaBanco();

        if(!fila) return NULL;

        Cliente* aux_g = fila_geral->primeiro;
        Cliente* aux_p = fila_pref->primeiro;

        int i = 1;
        while (aux_p || aux_g) {
            if (aux_p && (i%4 != 0)) {
                Enfileirar(fila, ClonaCliente(aux_p));
                aux_p = aux_p->prox;
            }
            
            else if (aux_g) {
                Enfileirar(fila, ClonaCliente(aux_g));
                aux_g = aux_g->prox;
            }

            i++;
        }

        return fila;
    }

//-------------------------------------------------------------------------------------------------------------//

    //
    // Subemnu do Banco
    //
    void MenuBanco() {
        Fila_Banco* fila_geral = CriaFilaBanco();
        Fila_Banco* fila_pref  = CriaFilaBanco();

        Fila_Banco* fila;
        
        int opc;

        do { // hast
            cleanScreen();

            puts("=========================");
            puts("BANCO\n");
            printf("Fila ");

            fila = FilaAtendimento(fila_geral, fila_pref);
            ExibeFila(fila);
            
            puts(" 1 - Entrar na Fila");
            puts(" 2 - Andar Fila");
            puts(" 0 - Sair\n");
            printf("Escolha: ");
            opc = getchar(); clearBuffer();

            switch (opc) {
                case '1': InsereNaFila(fila_geral, fila_pref); pause(); break;
                case '2':
                case '0': break;
                default : puts("\n INVALIDO!!!"); break;
            }

        } while (opc != '0');
    }