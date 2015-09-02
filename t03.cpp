#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#define MAX 10
#define OKAY 13
#define CHARACTERES 256

/**
 * Trabalho 3 ataque força bruta com dicionario
 * objetivo: decifrar com cesar transposição e vigenere(curta) verificando chave com dicionario + heuristicas
 * 
 */
using namespace std;
	void cesarCrypt(char *base,int key,int ind_arq,char *teste);
	void transposicaoCrypt(char *base,int key,int ind_arq,char *teste);
	void vigenereCrypt(char *base,char *key,int ind_arq,char *teste);
	int checkDict(char *teste,std::vector<std::string> dic);

	
int main(int argc,char* args[]){
	FILE *arq=NULL;
	std::fstream out;
	char tipo=0;
	int ind_arq=0,ind_atual=0,key=1,result=0,total=0,ind_dic=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	if(args[2]!=NULL){
		out.open(args[2],std::fstream::in | std::fstream::out | std::fstream::app);
		if(!out.is_open()){
			printf("nao e possivel abrir ( - _ - )\n");
			exit(0);
		};
	};
	if(args[3]!=NULL)
		tipo=args[3][0];
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	rewind(arq);
	char base[ind_arq],teste[ind_arq];
	memset(base,0,sizeof(char)*ind_arq);
	memset(teste,0,sizeof(char)*ind_arq);
	fread(base,sizeof(char),ind_arq,arq);
	fflush(arq);
	fclose(arq);
	std::vector<std::string> dictionary;
	out.seekg(0,out.end);
	ind_dic=out.tellg();
	out.seekg(0,out.beg);
	char dicty[ind_dic],c=0;
	while(ind_atual<ind_dic){
		out.get(c);
		dicty[ind_dic]=c;
		ind_atual++;
	};
	switch(tipo){
		case 'c':{
			for(key=1;key<CHARACTERES;key++){
				cesarCrypt(base,key,ind_arq,teste);
				result=checkDict(teste,dictionary);
				if(result > total){
					printf("Cifra de Cesar\nChave:%d\n",key);
					break;
				}
			};
			break;
		};
		case 'v':{
			
			//vigenereCrypt(base,,ind_arq,teste);
			result=checkDict(teste,dictionary);
			break;
		};
		case 't':{
			key=1;
			while(result<total){
				transposicaoCrypt(base,key,ind_arq,teste);
				result=checkDict(teste,dictionary);
				key++;
			};
			printf("Cifra de Transposição\nChave:%d\n",key);
			break;
		};
	};
	
	out.close();
	return 0;
}
void cesarCrypt(char *base,int key,int ind_arq,char *teste){
	int ind_atual=0;
	while(ind_arq>ind_atual){
		teste[ind_atual]=(base[ind_atual]+key+CHARACTERES)%CHARACTERES;
		ind_atual++;
	};
};
void transposicaoCrypt(char *base,int key,int ind_arq,char *teste){
	int resto=0,tamLin=0;
	resto=ind_arq%key;
	tamLin=ind_arq/key;
	if(resto!=0)
		tamLin++;
	int ind_atual=0,caso=0,col=0;
	while(ind_arq>ind_atual){				
		caso=ind_atual%tamLin;
		teste[key*caso+col]=base[ind_atual];
		if(caso+1==tamLin)
			col++;
		ind_atual++;
	};
	if(resto!=0){
		char idc=0;
		int i;
		for( i = 0 ; i < resto ; i++ ){
			teste[ind_atual]=idc;
			idc++;
		};
	};
}
void vigenereCrypt(char *base,char *key,int ind_arq,char *teste){
	int campo=0,id_key=strlen(key),chav=0,ind_atual=0;
	while(ind_arq>ind_atual){
		campo=ind_atual%id_key;
		chav=key[campo];
		chav=chav*-1;
		teste[ind_atual]=(base[ind_atual]+chav+CHARACTERES)%CHARACTERES;
		ind_atual++;
	};
};
int checkDict(char *teste,std::vector<std::string> dic){
	
	return 0;
}
