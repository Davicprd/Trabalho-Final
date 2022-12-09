#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};
 
int main(void)
{
    void readPGMImage(struct pgm *, char *);
    void ProcessoPGMImage(struct pgm *,struct pgm *);
    DIR *d;
    struct dirent *dir;
    struct pgm img,img2;
    d = opendir("./oncotex_pgm");
    if (d)
    {
        dir = readdir(d);
        dir = readdir(d);
        dir = readdir(d);
        dir = readdir(d);
        readPGMImage(&img,dir->d_name);
        dir = readdir(d);
        readPGMImage(&img2,dir->d_name);
        ProcessoPGMImage(&img,&img2);

        printf("%s\n", dir->d_name);
        closedir(d);
    
    }

    return(0);
}

void readPGMImage(struct pgm *pio, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		exit(1);
	}

	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->mv);
	fseek(fp,1, SEEK_CUR);

	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);

}

void ProcessoPGMImage(struct pgm *pio,struct pgm *pio2){
    int **mat1,**mat2,**scm;
    mat1 = calloc(pio->r,sizeof(int));
    mat2 = calloc(pio->r,sizeof(int));
    scm = calloc(pio->r,sizeof(int));
        for(int i = 0; i<pio->r;i++){
        mat1[i] = calloc(pio->c,sizeof(int));
        mat2[i] = calloc(pio->c,sizeof(int));
        scm[i] = calloc(pio->c,sizeof(int));
    }
	printf("Max: %d\n",pio->mv);

	for (int k=0; k < (pio->r * pio->c); k++){
		if (!( k % pio->c)) printf("\n");
		printf("%2hhu ",*(pio->pData+k));
	}	
	printf("\n");
}
