#include "processo.h"
void ProcessoPGMImage(struct pgm *pio, struct pgm *pio2, char *filename, int quant)
{
    int **scm = calloc(quant, sizeof(int));
    for (int i = 0; i < (quant); i++)
    {
        scm[i] = calloc(quant, sizeof(int));
    }
    for (int i = 0; i < (quant); i++)
    {
        for (int j = 0; j < (quant); j++)
        {
            scm[i][j] = 0;
        }
    }
    for (int i = 0; i < (pio->c * pio2->r); i++)
    {

        scm[*(pio->pData + i) / (256 / quant)][*(pio2->pData + i) / (256 / quant)] += 1;
    }

    for (int i = 0; i < (quant); i++)
    {
        for (int j = 0; j < (quant); j++)
        {
            fprintf(f, "%i, ", scm[i][j]);
        }
    }
    fprintf(f, "%c\n", filename[0]);

}