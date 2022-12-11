#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "leitura.h"
#include "processo.h"

#define QTDIMG 1310

struct pgm
{
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void ProcessoPGMImage(struct pgm *, struct pgm *, char *, int);
FILE *f;
DIR *d;
char name[30] = "./oncotex_pgm/";
int main(void)
{

    clock_t begin, end;
    double time_per_img, time_total = 0;
    struct dirent *dir;
    struct pgm img, img2;
    int quant;
    // Aqui nos solicitamos a quantização em N níveis para o usuário
    puts("Digite o número de niveis de quantização: (8/16/32/64/128/256)");
    scanf("%i", &quant);
    // Aqui nós começamos a contagem
    begin = clock();
    // Aqui nós abrimos a pasta contento os arquivos
    d = opendir("./oncotex_pgm");
    // Aqui nós conferimos se existe algum arquivo nessa página
    if (d)
    {

        // Aqui nós usamos dois dir's fora do FOR para "limpar" arquivos que não irão ser utilizados no processo
        dir = readdir(d);
        dir = readdir(d);
        // Aqui inicializamos o Arquivo de texto para captura de dados dos vetores SCM
        f = fopen("SCM.txt", "w+");
        int cont = 0;
        // Aqui nos usamos um FOR para realizar todos os processos para cada duas imagens(sem filtro e com filtro)
        for (int i = 0; i <= (QTDIMG / 2); i++){
        strcpy(name,"./oncotex_pgm/");
        dir = readdir(d);
        strcat(name,dir->d_name);
        readPGMImage(&img,name);
        strcpy(name,"./oncotex_pgm/");
        dir = readdir(d);
        strcat(name,dir->d_name);
        readPGMImage(&img2,name);
        ProcessoPGMImage(&img, &img2, dir->d_name, quant);
        printf("\n%i",cont++);
        }
        // Aqui nós fechamos o arquivo e o diretório
        fclose(f);
        closedir(d);
    }
    else
    {
        printf("Nem abre");
    }

    // Finalizamos a contagem
    end = clock();

    // Armazenando o tempo médio gasto para cada imagem
    time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
    // Armazenando o tempo total gasto nos processos
    time_total += time_per_img;

    printf("\nTempo médio: %lf\n", time_total / QTDIMG);
    printf("\nTempo Total: %lf\n", time_total);
    return 0;
}

void readPGMImage(struct pgm *pio, char *filename)
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