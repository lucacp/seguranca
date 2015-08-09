#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL;
	char c[2]=" ",tipo='c';
	int ind_arq=0,ind_atual=0,key=3;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	if(args[2]!=NULL){
		key=atoi(args[2]);
		if(args[3]!=NULL)
			tipo=args[3][0];
	};
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	ind_atual=0;
	rewind(arq);
	switch(tipo){
		case 'c':{
			while(ind_arq>ind_atual){
				if(feof(arq)) break;
				c[0]=fgetc(arq);
				printf("%c",c[0]);
				c[0]=(c[0]+(char)key+126)%126;
				fseek(arq,ind_atual,SEEK_SET);
				fwrite(c,sizeof(char),1,arq);
				ind_atual++;
				fflush(arq);
			};
			break;
		};
		case 't':{
			
			break;
		};
		case 'v':{
			
			break;
		};
		case 's':{
			
			break;
		};
		default:{
			printf("Opcao escolhida nao corresponde a nenhuma criptografia disponivel!");
			exit(0);
			break;
		};
	}
	//printf("(-_-)\n");
	rewind(arq);
	ind_atual=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		fread(c,sizeof(char)*1,1,arq);
		printf("%c",c[0]);
		ind_atual++;
	};
	printf("(>_<)\n");
	fclose(arq);
	return 0;
}

