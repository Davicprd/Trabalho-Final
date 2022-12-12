#include "processo.h"

void LerIMG(struct pgm *img, char *filename)
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

    img->tipo = getc(fp) - 48;

    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#')
    {
        while ((ch = getc(fp)) != '\n')
            ;
    }

    fseek(fp, -2, SEEK_CUR);

    fscanf(fp, "%d %d", &img->i, &img->j);
    if (ferror(fp))
    {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%d", &img->quan);
    fseek(fp, 0, SEEK_CUR);

    img->pData = (unsigned char *)malloc(img->j * img->i * sizeof(unsigned char));

    switch (img->tipo)
    {
    case 2:
        for (int k = 0; k < (img->j * img->i); k++)
        {
            fscanf(fp, "%hhu", img->pData + k);
        }
        break;
    case 5:
        fread(img->pData, sizeof(unsigned char), img->j * img->i, fp);
        break;
    default:
        puts("Não está implementado");
    }

    fclose(fp);
}

void Processo(struct pgm *img, struct pgm *img2, char *filename)
{
    int **scm = calloc(quant, sizeof(int));
    for (int i = 0; i < (quant); i++)
    {
        scm[i] = calloc(quant, sizeof(int));
    }

    for (int i = 0; i < (img->i * img2->j); i++)
    {

        scm[(*(img->pData + i) / ((img->quan + 1) / quant))][(*(img2->pData + i) / ((img2->quan + 1) / quant))] += 1;
    }

    for (int i = 0; i < (quant); i++)
    {
        for (int j = 0; j < (quant); j++)
        {
            fprintf(file, "%i, ", scm[i][j]);
        }
    }
    fprintf(file, "%c\n", filename[0]);
} 
