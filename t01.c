#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL;
	char buf[MAX]={"\0"},c;
	int ind_arq=0,ind_atual=0,ind_auxiliar=0,key=3;
	if((arq=fopen(args[1],"r+"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);	
	for(ind_atual=0;ind_arq>ind_atual;ind_atual++,ind_auxiliar++){
		fread(&c,sizeof(char),1,arq);
		if(feof(arq)) break;
		//printf("%c",c);
		buf[ind_atual]=c;
		if(ind_atual+1==MAX){
			for(ind_auxiliar=0;ind_auxiliar<MAX;ind_auxiliar++){
				buf[ind_auxiliar]+=key;
			};
			fseek(arq,1-MAX,SEEK_CUR);
			fwrite(buf,sizeof(char),MAX,arq);
			ind_auxiliar=0;
			for(ind_auxiliar=0;ind_auxiliar<MAX;ind_auxiliar++){
				buf[ind_auxiliar]='\0';
			};
			fflush(arq);
		};
	};
	for(ind_atual=0;ind_atual<ind_auxiliar;ind_atual++){
		buf[ind_atual]+=key;
	};
	fseek(arq,1-ind_atual,SEEK_CUR);
	fwrite(buf,sizeof(char),ind_atual-1,arq);
	//printf("(-_-)\n");
	rewind(arq);
	ind_atual=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		fread(&c,sizeof(char),1,arq);
		//printf("%c",c);
		ind_atual++;
	};
	printf("(>_<)\n");
	fclose(arq);
	return 0;
}

