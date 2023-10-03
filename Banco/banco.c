#include "banco.h"

//-------------------------------------------------------------------------------------------------------------//

    // Construtores

//-------------------------------------------------------------------------------------------------------------//

    // Métodos úteis

//-------------------------------------------------------------------------------------------------------------//

    // CRUD

//-------------------------------------------------------------------------------------------------------------//

    //
    // Subemnu do Banco
    //
    void MenuBanco(Fila_Banco* fila, Fila_Banco* fila_geral, Fila_Banco* fila_pref) {
        int opc;

        do { // hast
            cleanScreen();

            puts("=========================");
            puts("BANCO\n");
            puts(" 1 - Entrar na Fila");
            puts(" 2 - Exibir Fila");
            puts(" 3 - Andar Fila");
            puts(" 0 - Sair\n");
            printf("Escolha: ");
            opc = getchar(); clearBuffer();

            switch (opc) {
                case '1':
                case '2':
                case '3':
                case '0': pause(); return;
                default : break;
            }

        } while (opc != '0');
    }