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
	char key=3,c='0';
	int i=0,k=0;
	if((arq=fopen(args[1],"r+"))==NULL){
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
		c=(c+key)%256;
		//printf("%c",c);
		fwrite(&c,sizeof(char),1,arq);
		k++;
		if(feof(arq)) break;
	};
	printf("(-_-)\n");
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

