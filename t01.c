#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL;
	char c[2]=" ";
	int ind_arq=0,ind_atual=0,key=3;
	if((arq=fopen(args[1],"r+"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	ind_atual=0;
	rewind(arq);
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		printf("%c",c[0]);
		c[0]=c[0]+key;
		fseek(arq,ind_atual,SEEK_SET);
		fputs(c[0],arq);
		ind_atual++;
	};
	//printf("(-_-)\n");
	rewind(arq);
	ind_atual=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		printf("%c",c[0]);
		ind_atual++;
	};
	printf("(>_<)\n");
	fclose(arq);
	return 0;
}

