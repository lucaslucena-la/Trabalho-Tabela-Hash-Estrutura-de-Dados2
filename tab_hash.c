// tab_hash.c
#include "tab_hash.h"

// Função para inicializar a tabela hash
void inicializaTabHash(tipo_tab_hash *tbh) {
    for (int i = 0; i < TAM_HASH; i++) {
        tbh->tabela_hash[i] = NULL; // Define todas as posições como NULL, indicando que estão vazias.
    }
}

// Função para alocar um novo nó na tabela hash
tipo_no_hash *alocaNoHash(int chave, const char* dado) {
    tipo_no_hash *novo_no = (tipo_no_hash *)malloc(sizeof(tipo_no_hash));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }
    novo_no->chave = chave;
    strncpy(novo_no->valor, dado, MAX_VALOR - 1);
    novo_no->valor[MAX_VALOR - 1] = '\0';
    novo_no->prox = NULL;
    return novo_no;
}

// Funções de hash
int funcaoHash(int chave) {
    return chave % TAM_HASH;
}

int hashDobra(int chave, int Tb_size) {
    int parte1 = chave >> 16;
    int parte2 = chave & 0xFFFF;
    int resultado = parte1 + parte2;
    return resultado % Tb_size;
}

int hashMultiplicacao(int chave, int Tb_size) {
    double A = 0.9287;
    double val = (double)chave * A;
    val = val - (long)val;
    int indice = (int)(val * Tb_size);
    return indice;
}

void insereTabHash(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes) {
    int pos = funcaoHash(chave);

    tipo_no_hash *aux = buscaTabHash(tbh, chave);
    if (aux != NULL) {
        printf("Erro: Chave %d já existente. Inserção não realizada.\n", chave);
        return;
    }

    tipo_no_hash *novo_no = alocaNoHash(chave, dado);

    if (tbh->tabela_hash[pos] == NULL) {
        tbh->tabela_hash[pos] = novo_no;
    } else {
    
        (*contador_colisoes)++; // Incrementa o contador de colisões
        printf("Colisão detectada na posição %d para a chave %d\n", pos, chave); // Mensagem de depuração

        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    }
}


// Função para inserir um nó na tabela hash usando o método da Dobra
void insereTabHashDobra(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes) {
    int pos = hashDobra(chave, TAM_HASH);

    tipo_no_hash *aux = buscaTabHash(tbh, chave);
    if (aux != NULL) {
        printf("Erro: Chave %d já existente. Inserção não realizada.\n", chave);
        return;
    }

    tipo_no_hash *novo_no = alocaNoHash(chave, dado);

    if (tbh->tabela_hash[pos] == NULL) {
        tbh->tabela_hash[pos] = novo_no;
    } else {
        (*contador_colisoes)++; // Incrementa o contador de colisões
        
        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    }
}

// Função para inserir um nó na tabela hash usando o método da Multiplicação
void insereTabHashMulti(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes) {
    int pos = hashMultiplicacao(chave, TAM_HASH);

    tipo_no_hash *aux = buscaTabHash(tbh, chave);
    if (aux != NULL) {
        printf("\nErro: Chave %d já existente. Inserção não realizada.\n", chave);
        return;
    }

    tipo_no_hash *novo_no = alocaNoHash(chave, dado);

    if (tbh->tabela_hash[pos] == NULL) {
        tbh->tabela_hash[pos] = novo_no;
    } else {
        (*contador_colisoes)++; // Incrementa o contador de colisões
    
        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    }
}


char* removeTabHash(tipo_tab_hash *tbh, int chave) {
    int pos = funcaoHash(chave);
    tipo_no_hash *aux = tbh->tabela_hash[pos];
    tipo_no_hash *ant = NULL;

    while (aux != NULL && aux->chave != chave) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Chave não encontrada para remoção.\n");
        return NULL;
    }

    char* dado = (char*)malloc(MAX_VALOR * sizeof(char));
    if (dado == NULL) {
        printf("Erro ao alocar memória para o valor removido.\n");
        exit(1);
    }
    strncpy(dado, aux->valor, MAX_VALOR - 1);
    dado[MAX_VALOR - 1] = '\0';

    if (ant == NULL) {
        tbh->tabela_hash[pos] = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux);
    return dado;
}

tipo_no_hash *buscaTabHash(tipo_tab_hash *tbh, int chave) {
    int pos = funcaoHash(chave);
    tipo_no_hash *aux = tbh->tabela_hash[pos];

    while (aux != NULL) {
        if (aux->chave == chave) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void imprimeTabHash(tipo_tab_hash *tbh) {
    printf("Tabela HASH:\n");
    for (int i = 0; i < TAM_HASH; i++) {
        printf("[%d] -> ", i);
        tipo_no_hash *aux = tbh->tabela_hash[i];

        if (aux == NULL) {
            printf("(NULL)\n");
        } else {
            while (aux != NULL) {
                printf("[ %d | %s ] -> ", aux->chave, aux->valor);
                aux = aux->prox;
            }
            printf("(NULL)\n");
        }
    }
}


// Função para limpar a tabela hash e desalocar memória
void limparTabelaHash(tipo_tab_hash *tbh) {
    for (int i = 0; i < TAM_HASH; i++) {
        tipo_no_hash *no_atual = tbh->tabela_hash[i];
        while (no_atual != NULL) {
            tipo_no_hash *no_prox = no_atual->prox; // Armazena o próximo nó
            free(no_atual); // Libera o nó atual
            no_atual = no_prox; // Avança para o próximo nó
        }
        tbh->tabela_hash[i] = NULL; // Define a posição como vazia
    }
    printf("Tabela hash limpa com sucesso.\n");
}


// Função para calcular o tamanho médio das listas encadeadas na tabela hash
double calcularTamanhoMedioLista(tipo_tab_hash *tbh) {
    int total_elementos = 0; // Total de elementos na tabela hash
    int num_listas = 0;      // Número de listas (posições ocupadas)

    for (int i = 0; i < TAM_HASH; i++) {
        tipo_no_hash *no_atual = tbh->tabela_hash[i];
        if (no_atual != NULL) {
            num_listas++;
            int tamanho_lista = 0;
            // Contando o número de elementos na lista encadeada
            while (no_atual != NULL) {
                tamanho_lista++;
                no_atual = no_atual->prox;
            }
            total_elementos += tamanho_lista;
        }
    }

    if (num_listas == 0) return 0.0; // Evita divisão por zero
    return (double)total_elementos / num_listas;
}