//*******************************************************************//
//* Alunos: Allan Neil, Francisco Davi, Leonardo Borges            *//
//* Matriculas: 20221045050028, 20221045050125, 20221045050230    *//
//* Avaliação 04: Trabalho Final                                 *//
//* 04.505.23 - 2022.2 - Prof. Daniel Ferreira                  *//
//* Compilador gcc Versão 6.3.0                                *//
//*************************************************************//

#include "processo.h"

int main(int argc, char *argv[])
{
    // Quantização em N níveis
    quant = atoi(argv[1]);
    strcpy(name, "./oncotex_pgm/");
    sprintf(arq_name, "%i-scm.txt", quant);
    // Aqui nós começamos a contagem
    begin = clock();
    // Aqui nós abrimos a pasta contento os arquivos
    diretorio = opendir("./oncotex_pgm");
    if (diretorio)
    {

        // Aqui nós usamos dois dir's fora do FOR para "limpar" arquivos que não irão ser utilizados no processo
        dir = readdir(diretorio);
        dir = readdir(diretorio);
        // Aqui inicializamos o Arquivo de texto para captura de dados dos vetores SCM
        file = fopen(arq_name, "w+");
        // Aqui nos usamos um FOR para realizar todos os processos para cada duas imagens(sem filtro e com filtro)
        for (int i = 1; i <= (QTDIMG / 2); i++)
        {
            // Nós salvamos os nomes dos arquivos em uma string "name" para ser utilizada nas funções
            strcpy(name, "./oncotex_pgm/");
            // Foi utilizado um "dir" para receber um arquivo do diretório
            dir = readdir(diretorio);
            strcat(name, dir->d_name);
            // Aqui é usada a função da leitura da imagem
            LerIMG(&img, name);
            strcpy(name, "./oncotex_pgm/");
            dir = readdir(diretorio);
            strcat(name, dir->d_name);
            LerIMG(&img2, name);
            // Aqui é usada a função do processo das imagens
            Processo(&img, &img2, dir->d_name);
        }

        // Aqui nós fechamos o arquivo e o diretório
        fclose(file);
        closedir(diretorio);
    }
    // Finalizamos a contagem
    end = clock();

    // Armazenando o tempo médio gasto para cada imagem
    time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
    // Armazenando o tempo total gasto nos processos
    time_total += time_per_img;

    // Aqui nós imprimimos o tempo médio e total de processamento
    printf("\nTempo Médio: %lf\n", time_total / QTDIMG);
    printf("\nTempo Total: %lf\n", time_total);
    return 0;
}
