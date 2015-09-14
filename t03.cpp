#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#define MAX 10
#define OKAY 13
#define CHARACTERES 256
#define OKAYT 110000

/**
 * Trabalho 3 ataque força bruta com dicionario
 * objetivo: decifrar com cesar transposição e vigenere(curta) verificando chave com dicionario + heuristicas
 * 
 */
using namespace std;
	void cesarCrypt(char *base,int key,int ind_arq,char *teste);
	void transposicaoCrypt(char *base,int key,int ind_arq,char *teste);
	void vigenereCrypt(char *base,char *key,int tamanhokey,int ind_arq,char *teste);
//	int checkDictCV(char *teste,vector<string>* dic);
	int checkDict(char *teste,std::vector<std::string>* dic);
	void inserirDic(char *dicty,vector<string>* dictionary);
	void AtualizarChave(char key[10],int tamKey);
	
int main(int argc,char* args[]){
	FILE *arq=NULL, *out=NULL;
	char tipo=0;
	int ind_arq=0,key=1,result=0,ind_dic=0,esperado=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	if(args[2]!=NULL){
		out=fopen(args[2],"r+b");
		if(!out){
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
	vector<string> dictionary;
	fseek(out,0,SEEK_END);
	ind_dic=ftell(out);
	rewind(out);
	//cout << ind_dic<<endl;
	char dicty[ind_dic];
	fread(dicty,sizeof(char),ind_dic,out);
	//cout << dicty<<endl;
	inserirDic(dicty,&dictionary);
	/*unsigned int ind_atual=0;
	for(ind_atual=0;ind_atual<dictionary.size();ind_atual++)
		cout << dictionary[ind_atual]<<endl;*/
		esperado=ind_arq/10;
	switch(tipo){
		case 'c':{
			for(key=1;key<CHARACTERES;key++){			
				cesarCrypt(base,key,ind_arq,teste);
				result=checkDict(teste,&dictionary);
				//cout << result<<" , "<<key<<endl;
				if(result<0)
					result*=-1;
				if(result > esperado){
					printf("Cifra de Cesar\nChave:%d\n",key);
					break;
				};
				
			};
			break;
		};
		case 't':{
			key=1;
			esperado=110000;
			while(key<ind_arq){
				transposicaoCrypt(base,key,ind_arq,teste);
				result=(unsigned int)checkDict(teste,&dictionary);
			//	cout << result<<" , "<<key<<endl;
				if(result<0)
					result*=-1;
				if(result > esperado){
					printf("Cifra de Transposicao\nChave:%d\n",key);
					
					break;
				};
				key++;
			};
			//printf("Cifra de Transposição\nChave:%d\n",key);
			//printf("Resultado:%d\n",result);
			break;
		};
		case 'v':{
			char key_str[10]={'0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
			int key_tam=1;
			while(key_tam<10){
				vigenereCrypt(base,key_str,key_tam,ind_arq,teste);
				result=checkDict(teste,&dictionary);
				if(result<0)
					result*=-1;
				if(result > esperado){
					printf("Cifra de Viginere\nChave:%s\n",key_str);
					break;
				};
				AtualizarChave(key_str,key_tam);
			};
			break;
		};
	};
	
	fclose(out);
	return 0;
}
// 1º fazer heuristica com letras solitarias com dicionario = texto original, 2º passo fazer com que este programa funcione para duplas e triplas, 3º passo  

void cesarCrypt(char *base,int key,int ind_arq,char *teste){
	int ind_atual=0;
	while(ind_arq>ind_atual){
		teste[ind_atual]=(base[ind_atual]-key+CHARACTERES)%CHARACTERES;
		ind_atual++;
	};
//	printf("( * - X*)\n");
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
void vigenereCrypt(char *base,char *key,int tamanhokey,int ind_arq,char *teste){
	int campo=0,chav=0,ind_atual=0;
	while(ind_arq>ind_atual){
		campo=ind_atual%tamanhokey;
		chav=key[campo];
		chav=chav*-1;
		teste[ind_atual]=(base[ind_atual]+chav+CHARACTERES)%CHARACTERES;
		ind_atual++;
	};
};
int checkDict(char *teste,vector<string>* dic){
	string texto(teste);
	int ind_tex=strlen(teste),ind_atual=0,pos=0,len=0,result=0;
	unsigned int ind_vec=0;
	while(ind_atual<ind_tex){
		if((teste[ind_atual]==' '||teste[ind_atual]=='\n')&&ind_vec<dic->size()){
			len=ind_atual-pos;
			if(dic->at(ind_vec).compare(texto.substr(pos,len))==0){
				result++;
			}
			else
				result--;
			//cout << ind_vec++<<endl;
			
			pos=ind_atual+1;
		};
		ind_atual++;
	};
	//cout << result;
	return result;
}
/*int checkDictCV(char *teste,vector<string>* dic){
	string texto(teste);
	int ind_tex=strlen(teste),ind_atual=0,pos=0,len=0,result=0;
	unsigned int ind_vec=0;
	while(ind_atual<ind_tex){
		if((teste[ind_atual]==' '||teste[ind_atual]=='\n')&&ind_vec<dic->size()){
			len=ind_atual-pos;
			for(ind_vec=0;ind_vec<dic->size();ind_vec++){
				if(dic->at(ind_vec).compare(texto.substr(pos,len))==0){
					result++;
				};
			};
			//cout << ind_vec++<<endl;
			
			pos=ind_atual+1;
		};
		ind_atual++;
	};
	//cout << result;
	return result;
}*/
void inserirDic(char *dicty,vector<string>* dictionary){
	string dic(dicty);
	int ind_dic=0,ind_atual=0,pos=0,len=0,palavras=0;
	ind_dic=strlen(dicty);
	while(ind_atual<ind_dic){
		if((dicty[ind_atual]==' '||dicty[ind_atual]=='\n')&&palavras<8000){
			len=ind_atual-pos;
			dictionary->push_back(dic.substr(pos,len));
			pos=ind_atual+1;
			palavras++;
		}
		ind_atual++;
	}

}
void AtualizarChave(char key[10],int *tamKey){
	switch (*tamKey){
		case 9:{
			if(key[8]=='9')
				key[8]='a';
			else if(key[8]=='z')
				key[8]='A';
			else if(key[8]=='Z'){
				key[8]='0';
				key[9]='0';
				(*tamKey)++;
			}else
				key[8]++;
			break;
		};
		case 8:{
			if(key[7]=='9')
				key[7]='a';
			else if(key[7]=='z')
				key[7]='A';
			else if(key[7]=='Z'){
				key[7]='0';
				key[8]='0';
				(*tamKey)++;
			}else
				key[7]++;
			break;
		};
		case 7:{
			if(key[6]=='9')
				key[6]='a';
			else if(key[6]=='z')
				key[6]='A';
			else if(key[6]=='Z'){
				key[6]='0';
				key[7]='0';
				(*tamKey)++;
			}else
				key[6]++;
			break;
		};
		case 6:{
			if(key[5]=='9')
				key[5]='a';
			else if(key[5]=='z')
				key[5]='A';
			else if(key[5]=='Z'){
				key[5]='0';
				key[6]='0';
				(*tamKey)++;
			}else
				key[5]++;
			break;
		};
		case 5:{
			if(key[4]=='9')
				key[4]='a';
			else if(key[4]=='z')
				key[4]='A';
			else if(key[4]=='Z'){
				key[4]='0';
				key[5]='0';
				(*tamKey)++;
			}else
				key[4]++;
			break;
		};
		case 4:{
			if(key[3]=='9')
				key[3]='a';
			else if(key[3]=='z')
				key[3]='A';
			else if(key[3]=='Z'){
				key[3]='0';
				key[4]='0';
				(*tamKey)++;
			}else
				key[3]++;
			break;
		};
		case 3:{
			if(key[2]=='9')
				key[2]='a';
			else if(key[2]=='z')
				key[2]='A';
			else if(key[2]=='Z'){
				key[2]='0';
				key[3]='0';
				(*tamKey)++;
			}else
				key[2]++;
			break;
		};
		case 2:{
			if(key[1]=='9')
				key[1]='a';
			else if(key[1]=='z')
				key[1]='A';
			else if(key[1]=='Z'){
				key[1]='0';
				key[2]='0';
				(*tamKey)++;
			}else
				key[1]++;
			break;
		};
		case 1:{
			if(key[0]=='9')
				key[0]='a';
			else if(key[0]=='z')
				key[0]='A';
			else if(key[0]=='Z'){
				key[0]='0';
				key[1]='0';
				(*tamKey)++;
			}else
				key[0]++;
			break;
		};
	};
};
