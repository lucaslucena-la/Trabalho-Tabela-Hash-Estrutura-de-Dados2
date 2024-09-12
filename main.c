// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab_hash.h"
#include "gera_arquivo.h"

int main() {
    tipo_tab_hash minha_tab_hash;
    inicializaTabHash(&minha_tab_hash);

    // Geração automática de arquivos na execução do programa
    gerarArquivosAutomaticamente();

    int opcao;
    int metodo;
    int valor, ch;
    int contador_colisoes = 0; // Inicializa o contador de colisões
    tipo_no_hash *aux;
    char dado[MAX_VALOR];

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir na Tabela Hash Manualmente\n");
        printf("2. Inserir dados de um arquivo na Tabela Hash\n");
        printf("3. Remover da Tabela Hash\n");
        printf("4. Imprimir Tabela Hash\n");
        printf("5. Buscar na tabela Hash\n");
        printf("6. Limpar Tabela Hash\n");
        printf("7. Sair\n");
        printf("\nDigite a opção desejada: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                // Inserir manualmente
                printf("\nEscolha o método de inserção:\n");
                printf("1. Método de Divisão\n");
                printf("2. Método da Dobra\n");
                printf("3. Método da Multiplicação\n");
                printf("Digite a opção desejada: ");
                if (scanf("%d", &metodo) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Valor a Inserir: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada inválida para o valor. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Dado a Inserir: ");
                while (getchar() != '\n');
                if (fgets(dado, MAX_VALOR, stdin) != NULL) {
                    dado[strcspn(dado, "\n")] = '\0';
                    switch (metodo) {
                        case 1:
                            insereTabHash(&minha_tab_hash, valor, dado, &contador_colisoes);
                            break;
                        case 2:
                            insereTabHashDobra(&minha_tab_hash, valor, dado, &contador_colisoes);
                            break;
                        case 3:
                            insereTabHashMulti(&minha_tab_hash, valor, dado, &contador_colisoes);
                            break;
                        default:
                            printf("Método de inserção inválido. Tente novamente.\n");
                            break;
                    }
                } else {
                    printf("Erro ao ler o dado. Tente novamente.\n");
                }
                break;

            case 2:
                // Inserir dados de um arquivo
                printf("\nEscolha o método de inserção:\n");
                printf("1. Método de Divisão\n");
                printf("2. Método da Dobra\n");
                printf("3. Método da Multiplicação\n");
                printf("Digite a opção desejada: ");
                if (scanf("%d", &metodo) != 1 || metodo < 1 || metodo > 3) {
                    printf("Método inválido. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }

                contador_colisoes = 0; // Reseta o contador de colisões
                carregarDadosArquivoEscolhido(&minha_tab_hash, metodo, &contador_colisoes);

                printf("\nNúmero de colisões durante a inserção: %d\n", contador_colisoes);

                // Calcula o tamanho médio das listas encadeadas
                double tamanhoMedio = calcularTamanhoMedioLista(&minha_tab_hash);
                printf("\nTamanho médio das listas encadeadas: %.2f\n", tamanhoMedio);
                break;

            case 3:
                // Remover da tabela hash
                printf("Chave para Remover: ");
                if (scanf("%d", &ch) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (removeTabHash(&minha_tab_hash, ch)) {
                    printf("Chave %d removida com sucesso.\n", ch);
                } else {
                    printf("Chave não encontrada para remoção.\n");
                }
                break;

            case 4:
                imprimeTabHash(&minha_tab_hash);
                break;

            case 5:
                printf("Pesquisar chave: ");
                if (scanf("%d", &ch) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                aux = buscaTabHash(&minha_tab_hash, ch);
                if (aux != NULL) {
                    printf("\nChave %d encontrada: dado = %s\n", ch, aux->valor);
                } else {
                    printf("Chave não encontrada\n");
                }
                break;

            case 6:
                limparTabelaHash(&minha_tab_hash);
                break;

            case 7:
                printf("Saindo do programa.\n");
                limparTabelaHash(&minha_tab_hash); // Libera a memória antes de sair
                return EXIT_SUCCESS;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}
