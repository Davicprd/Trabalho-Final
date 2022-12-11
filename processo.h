#include <stdio.h>
#include <stdlib.h>
struct pgm
{
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void ProcessoPGMImage(struct pgm *, struct pgm *, char *, int ,FILE *);

void readPGMImage(struct pgm *, char *);
