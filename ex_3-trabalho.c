#include "estoque.c"

int main(int argc, char const *argv[]) {
    Lista_de_Produtos* lista = CriaListaProdutos(10);

    MenuProdutos(lista);

    FreeEstoque(lista);

    return 0;
}
