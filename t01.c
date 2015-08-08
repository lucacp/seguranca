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
	int i=0,k=0,f=0,key=3;
	if((arq=fopen(args[1],"r+"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	i=ftell(arq);	
	for(k=0;i>k;k++,f++){
		fread(&c,sizeof(char),1,arq);
		if(feof(arq)) break;
		//printf("%c",c);
		buf[k]=c;
		if(k+1==MAX){
			for(f=0;f<MAX;f++){
				buf[f]+=key;
			};
			fseek(arq,1-MAX,SEEK_CUR);
			fwrite(buf,sizeof(char),MAX,arq);
			f=0;
			for(f=0;f<MAX;f++){
				buf[f]='\0';
			};
			fflush(arq);
		};
	};
	for(k=0;k<f;k++){
		buf[k]+=key;
	};
	fseek(arq,1-k,SEEK_CUR);
	fwrite(buf,sizeof(char),k-1,arq);
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

