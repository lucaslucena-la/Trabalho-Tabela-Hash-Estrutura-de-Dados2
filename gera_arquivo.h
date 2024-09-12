// gera_arquivo.h
#ifndef __GERA_ARQUIVO_H__
#define __GERA_ARQUIVO_H__

#include "tab_hash.h"

#define NUM_FILES 5 // Número de arquivos por tipo e quantidade
#define NUM_FILES 5 // Número de arquivos a serem gerados por tipo e tamanho
#define MAX_LINHA 100 // Tamanho máximo de uma linha no arquivo
#define MAX_ARQUIVOS 100 // Número máximo de arquivos que podem ser listados
#define TAM_NOME_ARQUIVO 100 // Tamanho máximo do nome do arquivo

int geraNumeroUnico(int *numeros, int tamanho, int tipo);
void gerarNumeros(int *numeros, int n, int tipo);
int escreverArquivo(const char *nomeArquivo, int *chaves, char valores[][MAX_VALOR], int n);
void carregarDadosDoArquivo(tipo_tab_hash *tbh, const char *nomeArquivo, int metodo, int *contador_colisoes);
void gerarChavesEValores(int *chaves, char valores[][MAX_VALOR], int n, int tipo);
void gerarArquivosAutomaticamente();
void carregarDadosArquivoEscolhido(tipo_tab_hash *tbh, int metodo, int *contador_colisoes);
int listarArquivosTxt(char arquivos[][TAM_NOME_ARQUIVO]);


#endif
