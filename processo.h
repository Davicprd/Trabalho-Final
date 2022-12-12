//*******************************************************************//
//* Alunos: Allan Neil, Francisco Davi, Leonardo Borges            *//
//* Matriculas: 20221045050028, 20221045050125, 20221045050230    *//
//* Avaliação 04: Trabalho Final                                 *//
//* 04.505.23 - 2022.2 - Prof. Daniel Ferreira                  *//
//* Compilador gcc Versão 6.3.0                                *//
//*************************************************************//

//Aqui foi declarada as bibliotecas, a estrutura, as variáveis globais e as funções que irão ser utilizadas nos arquivos '.c'
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#define QTDIMG 1312

FILE *file;
DIR *diretorio;
clock_t begin, end;
struct dirent *dir;
struct pgm img, img2;
int quant;
char name[50], arq_name[10];
double time_per_img, time_total;

struct pgm
{
    int tipo;
    int i;
    int j;
    int quan;
    unsigned char *pData;
};

void Processo(struct pgm *, struct pgm *, char *);
void LerIMG(struct pgm *, char *);
