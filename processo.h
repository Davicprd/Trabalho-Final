#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#define QTDIMG 1312

FILE *f;
DIR *d;
clock_t begin, end;
struct dirent *dir;
struct pgm img, img2;
int quant;
char name[50], a_name[10];
double time_per_img, time_total;

struct pgm
{
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void Processo(struct pgm *, struct pgm *, char *, int, FILE *);
void LerIMG(struct pgm *, char *);
