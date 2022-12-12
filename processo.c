#include "processo.h"

void LerIMG(struct pgm *pio, char *filename)
{
    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "r")))
    {
        perror("Erro.");
        exit(1);
    }

    if ((ch = getc(fp)) != 'P')
    {
        puts("A imagem fornecida não está no formato pgm");
        exit(2);
    }

    pio->tipo = getc(fp) - 48;

    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#')
    {
        while ((ch = getc(fp)) != '\n')
            ;
    }

    fseek(fp, -2, SEEK_CUR);

    fscanf(fp, "%d %d", &pio->c, &pio->r);
    if (ferror(fp))
    {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 1, SEEK_CUR);

    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));

    switch (pio->tipo)
    {
    case 2:
        for (int k = 0; k < (pio->r * pio->c); k++)
        {
            fscanf(fp, "%hhu", pio->pData + k);
        }
        break;
    case 5:
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
        break;
    default:
        puts("Não está implementado");
    }

    fclose(fp);
}

void Processo(struct pgm *pio, struct pgm *pio2, char *filename, int quant, FILE *f)
{
    int **scm = calloc(quant, sizeof(int));
    for (int i = 0; i < (quant); i++)
    {
        scm[i] = calloc(quant, sizeof(int));
    }

    for (int i = 0; i < (pio->c * pio2->r); i++)
    {

        scm[(*(pio->pData + i) / ((pio->mv + 1) / quant))][(*(pio2->pData + i) / ((pio2->mv + 1) / quant))] += 1;
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
