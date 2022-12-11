#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "processo.h"

#define QTDIMG 1310

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
        ProcessoPGMImage(&img, &img2, dir->d_name, quant,f);
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
