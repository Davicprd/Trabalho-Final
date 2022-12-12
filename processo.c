//*******************************************************************//
//* Alunos: Allan Neil, Francisco Davi, Leonardo Borges            *//
//* Matriculas: 20221045050028, 20221045050125, 20221045050230    *//
//* Avaliação 04: Trabalho Final                                 *//
//* 04.505.23 - 2022.2 - Prof. Daniel Ferreira                  *//
//* Compilador gcc Versão 6.3.0                                *//
//*************************************************************//

#include "processo.h"

void LerIMG(struct pgm *img, char *filename)
{
    FILE *fp;
    char ch;

    //Aqui foi conferido se existe algum arquivo txt para ser armazenado os vetores concatenados.
    if (!(fp = fopen(filename, "r")))
    {
        perror("Erro.");
        exit(1);
    }
    //Aqui é conferido se a imagem possui uma tipagem pgm.
    if ((ch = getc(fp)) != 'P')
    {
        puts("A imagem fornecida não está no formato pgm");
        exit(2);
    }

    img->tipo = getc(fp) - 48;
    
    fseek(fp, 1, SEEK_CUR);
    //Aqui é utlizado um "while" para não contabilizar a linha de comentário, presente em algumas imagens.
    while ((ch = getc(fp)) == '#')
    {     
        while ((ch = getc(fp)) != '\n')
            ;
    }
    
    fseek(fp, -2, SEEK_CUR);
    //Aqui são salvas as dimensões da imagem processada.
    fscanf(fp, "%d %d", &img->i, &img->j);
    //Verifica o indicador de erro em fp.
    if (ferror(fp))
    {
        perror(NULL);
        exit(3);
    }
    //Aqui é salvo o nível de quantização escolhido.
    fscanf(fp, "%d", &img->quan);
    fseek(fp, 0, SEEK_CUR);

    img->pData = (unsigned char *)malloc(img->j * img->i * sizeof(unsigned char));
//Aqui o switch case analisa o tipo da imagem, para definir a maneira que matriz vai ser formada.
    switch (img->tipo)
    {
    //Caso seja textual(P2):  
    case 2:
        for (int k = 0; k < (img->j * img->i); k++)
        {
            fscanf(fp, "%hhu", img->pData + k);
        }
        break;
    //Caso seja binária(P5):   
    case 5:
        fread(img->pData, sizeof(unsigned char), img->j * img->i, fp);
        break;
    //Caso não atenda nenhuma das situações:  
    default:
        puts("Não está implementado");
    }

    fclose(fp);
}

void Processo(struct pgm *img, struct pgm *img2, char *filename)
{   //Criamos a matriz SCM
    int **scm = calloc(quant, sizeof(int));
    //Nós alocamos o espaço necessário para a matriz SCM, já quantizada
    for (int i = 0; i < (quant); i++)
    {
        scm[i] = calloc(quant, sizeof(int));
    }
    //Aqui será preenchido a matriz SCM com os dados das duas imagens vetorizadas, de acordo com a quantização
    for (int i = 0; i < (img->i * img2->j); i++)
    {

        scm[(*(img->pData + i) / ((img->quan + 1) / quant))][(*(img2->pData + i) / ((img2->quan + 1) / quant))] += 1;
    }
    //Preenchemos o arquivo de caracteristicas(txt) com os valores da matriz SCM vetorizada e quantizada
    for (int i = 0; i < (quant); i++)
    {
        for (int j = 0; j < (quant); j++)
        {
            fprintf(file, "%i, ", scm[i][j]);
        }
    }
    //Armazena o rótulo da imagem correspondente no fim de cada vetor SCM presente no arquivo de caracteristicas
    fprintf(file, "%c\n", filename[0]);
}
