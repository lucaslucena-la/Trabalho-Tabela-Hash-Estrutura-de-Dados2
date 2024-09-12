// gera_arquivo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gera_arquivo.h"
#include <dirent.h> // *Biblioteca para manipulação de diretórios*




// Função para listar os arquivos com extensão .txt no diretório atual
int listarArquivosTxt(char arquivos[MAX_ARQUIVOS][TAM_NOME_ARQUIVO]) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Não foi possível abrir o diretório.");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL && count < MAX_ARQUIVOS) {
        if (strstr(entry->d_name, ".txt") != NULL) {
            strncpy(arquivos[count], entry->d_name, TAM_NOME_ARQUIVO);
            arquivos[count][TAM_NOME_ARQUIVO - 1] = '\0'; // Garante que o nome do arquivo esteja terminado
            count++;
        }
    }

    closedir(dir);
    return count;
}

// Função para carregar dados de um arquivo e inserir na tabela hash
void carregarDadosDoArquivo(tipo_tab_hash *tbh, const char *nomeArquivo, int metodo, int *contador_colisoes) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char linha[MAX_LINHA];
    int chave;
    char valor[MAX_VALOR];

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Extrai chave e valor da linha
        if (sscanf(linha, "chave = %d valor = %s", &chave, valor) == 2) {
            switch (metodo) {
                case 1:
                    insereTabHash(tbh, chave, valor, contador_colisoes);
                    break;
                case 2:
                    insereTabHashDobra(tbh, chave, valor, contador_colisoes);
                    break;
                case 3:
                    insereTabHashMulti(tbh, chave, valor, contador_colisoes);
                    break;
                default:
                    printf("Método de inserção inválido.\n");
                    fclose(arquivo);
                    return;
            }
        } else {
            printf("Erro ao ler a linha ou formato inesperado: %s\n", linha);
        }
    }

    printf("Dados carregados do arquivo %s com sucesso.\n", nomeArquivo);
    fclose(arquivo);
}
// Função para carregar dados de um arquivo escolhido pelo usuário
void carregarDadosArquivoEscolhido(tipo_tab_hash *tbh, int metodo, int *contador_colisoes) {
    char arquivos[MAX_ARQUIVOS][TAM_NOME_ARQUIVO];
    int num_arquivos = listarArquivosTxt(arquivos);

    if (num_arquivos <= 0) {
        printf("Nenhum arquivo .txt disponível para carregar.\n");
        return;
    }

    printf("Arquivos disponíveis:\n");
    for (int i = 0; i < num_arquivos; i++) {
        printf("%d. %s\n", i + 1, arquivos[i]);
    }

    int escolha;
    printf("Escolha o número do arquivo que deseja carregar: ");
    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > num_arquivos) {
        printf("Escolha inválida.\n");
        while (getchar() != '\n');  // Limpa o buffer
        return;
    }

    carregarDadosDoArquivo(tbh, arquivos[escolha - 1], metodo, contador_colisoes);
}

// Função para gerar automaticamente os arquivos necessários e seus respectivos tipos e valores
void gerarArquivosAutomaticamente() {
    int tamanhos[] = {100, 200, 300};
    int tipos[] = {1, 2}; // Tipos de arquivos (1: múltiplos de 2, 2: sem restrição)
    char nomeArquivo[30];

    // Para cada tipo de arquivo
    for (int tp = 0; tp < 2; tp++) {
        // Para cada tamanho
        for (int tam = 0; tam < 3; tam++) {
            // Gerar NUM_FILES arquivos para cada combinação de tipo e tamanho
            for (int f = 0; f < NUM_FILES; f++) {
                // Cria o nome do arquivo
                sprintf(nomeArquivo, "tipo%d_%d_%d.txt", tipos[tp], tamanhos[tam], f + 1);

                // Aloca memória para as chaves e valores
                int *chaves = (int *)malloc(tamanhos[tam] * sizeof(int));
                char valores[tamanhos[tam]][MAX_VALOR];

                if (chaves == NULL) {
                    printf("Erro ao alocar memória para as chaves.\n");
                    return;
                }

                // Gera as chaves e valores
                srand(time(NULL) + tp + tam + f); // Garante uma semente diferente para cada execução
                gerarChavesEValores(chaves, valores, tamanhos[tam], tipos[tp]);

                // Escreve as chaves e valores no arquivo
                if (!escreverArquivo(nomeArquivo, chaves, valores, tamanhos[tam])) {
                    free(chaves);
                    return;
                }

                printf("Arquivo %s gerado com sucesso!\n", nomeArquivo);
                free(chaves);
            }
        }
    }
}

// Função para gerar chaves únicas e valores correspondentes
void gerarChavesEValores(int *chaves, char valores[][MAX_VALOR], int n, int tipo) {
    for (int i = 0; i < n; i++) {
        chaves[i] = geraNumeroUnico(chaves, i, tipo); // Gera chave única
        snprintf(valores[i], MAX_VALOR, "chave = %d valor = %04d", chaves[i], rand() % 10000); // Gera string combinada no formato desejado
    }
}

// Função para gerar um número aleatório único
int geraNumeroUnico(int *numeros, int tamanho, int tipo) {
    int num;
    int valido = 0;

    while (!valido) {
        num = rand() % 1024;
        if (tipo == 1 && num % 2 != 0) continue;
        valido = 1;
        for (int i = 0; i < tamanho; i++) {
            if (numeros[i] == num) {
                valido = 0;
                break;
            }
        }
    }

    return num;
}



// Função para escrever chaves e valores no arquivo
int escreverArquivo(const char *nomeArquivo, int *chaves, char valores[][MAX_VALOR], int n) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%s\n", valores[i]); // Escreve a string combinada no arquivo
    }

    fclose(arquivo);
    return 1;
}


