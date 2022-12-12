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
