#include <stdio.h>
#include <stdlib.h>

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 * 
 * 
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL;
	char c='0';
	int key=3,i=0,k=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	i=ftell(arq);	
	while(i<=k){
		fread(&c,sizeof(char),1,arq);
		k++;
		fseek(arq,-1,SEEK_CUR);
		printf("%c",c);
		c=(c+key);
		fwrite(&c,sizeof(char),1,arq);
		if(feof(arq)) break;
	};
	printf(" (-_-)\n");
	rewind(arq);
	k=0;
	while(i<=k){
		if(feof(arq)) break;
		fread(&c,sizeof(char),1,arq);
		printf("%c",c);
		k++;
	};
	fclose(arq);
	return 0;
}
