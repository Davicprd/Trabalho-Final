#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#define QTDIMG 1312

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
