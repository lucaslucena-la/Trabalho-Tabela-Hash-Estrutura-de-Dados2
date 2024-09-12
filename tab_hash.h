// tab_hash.h
#ifndef __TAB_HASH_H__
#define __TAB_HASH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 100
#define MAX_VALOR 40 // Tamanho máximo para o valor

// Estrutura de um nó da tabela hash
struct est_no_hash {
    int chave; // Chave que identifica o conjunto de dados
    char valor[MAX_VALOR]; // Dado que será armazenado
    struct est_no_hash *prox; // Ponteiro para o próximo nó (encadeamento externo)
};
typedef struct est_no_hash tipo_no_hash;

// Estrutura da tabela hash
struct est_tab_hash {
    tipo_no_hash *tabela_hash[TAM_HASH];
};
typedef struct est_tab_hash tipo_tab_hash;

// Prototipagem das funções
void inicializaTabHash(tipo_tab_hash*);
tipo_no_hash *alocaNoHash(int, const char*);
int funcaoHash(int);
int hashDobra(int, int);
int hashMultiplicacao(int, int);
void insereTabHash(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes);
void insereTabHashDobra(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes);
void insereTabHashMulti(tipo_tab_hash *tbh, int chave, const char* dado, int *contador_colisoes);
char* removeTabHash(tipo_tab_hash*, int);
tipo_no_hash *buscaTabHash(tipo_tab_hash*, int);
void imprimeTabHash(tipo_tab_hash*);
void limparTabelaHash(tipo_tab_hash *tbh);
double calcularTamanhoMedioLista(tipo_tab_hash *tbh);

#endif
