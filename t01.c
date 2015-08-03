#include <stdio.h>
#include <stdlib.h>

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 * 
 * 
 * 
 **/

int main(int args,char args[][]){
	FILE *arq=NULL;
	char c;
	int key=13;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )");
		exit(0);
	}
	fread(&c,sizeof(char),1,arq);
	fseek(arq,-1,SEEK_CUR);
	c=(c+key)%256;
	fwrite(&c,sizeof(char),1,arq);
	
	return 0;
}
