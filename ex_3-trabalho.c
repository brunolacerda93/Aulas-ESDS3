#include "estoque.c"

void PreencheEstoque(Lista_de_Produtos* lista) {
    InsereProdutoNalista(lista, CriaProdutoArgs(6, "Tiphareth", 56, 36.93));
    InsereProdutoNalista(lista, CriaProdutoArgs(93, "Crowley", 93, 93.56));
}

int main(int argc, char const *argv[]) {
    Lista_de_Produtos* lista = ReadProdutos();

    if (!lista->primeiro) PreencheEstoque(lista);

    MenuProdutos(lista);

    FreeEstoque(lista);

    return 0;
}
