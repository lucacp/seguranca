#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL;
	char c;
	int i=0,k=0,key=3,teste=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	i=ftell(arq);	
	while(i>k){
		fread(&c,sizeof(char),1,arq);
		fseek(arq,k,SEEK_SET);
		//printf("%c",c);
		teste=(int)c+key;
		printf("%c",c);
		c=(char)teste;
		fwrite(&c,sizeof(char),1,arq);
		k++;
		if(feof(arq)) break;
	};
	//printf("(-_-)\n");
	rewind(arq);
	k=0;
	while(i>k){
		if(feof(arq)) break;
		fread(&c,sizeof(char),1,arq);
		//printf("%c",c);
		k++;
	};
	printf("(>_<)\n");
	fclose(arq);
	return 0;
}

