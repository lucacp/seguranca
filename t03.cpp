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
	void AtualizarChave(char key[10],int *tamKey);
	void compararCharacteres(char *base,int *vetor);
	void Duplas(vector<string> *str);
	void Triplas(vector<string> *str);
	void comparaDuplas(vector<string> *str, char *texto,vector<unsigned int> *dup);
	void comparaTriplas(vector<string> *str, char *texto,vector<unsigned int> *trp);
	
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
			char key_str[10]={'A','b','c','d','\0','\0','\0','\0','\0','\0'};
			int key_tam=4;
			esperado=80000;
			while(key_tam<10){
				vigenereCrypt(base,key_str,key_tam,ind_arq,teste);
				result=checkDict(teste,&dictionary);
				//if(key_tam>3)
					//cout << result<< " , "<<key_str<<endl;
				if(result<0)
					result*=-1;
				if(result > esperado){
					printf("Cifra de Viginere\nChave:%s\n",key_str);
					break;
				};
				AtualizarChave(key_str,&key_tam);
			};
			break;
		};
		case 's':{
			//adicionar função de mapeamento de letras sozinhas duplas e triplas.
			int characteresSoloDict[256],characteresSoloBase[256];
			vector<string> strD,strT; 
			vector<unsigned int> compD,compT;
			
			memset(characteresSoloDict,0,sizeof(int)*CHARACTERES);
			memset(characteresSoloBase,0,sizeof(int)*CHARACTERES);
			
			compararCharacteres(dicty,characteresSoloDict);
			compararCharacteres(base,characteresSoloBase);
			
			Duplas(&strD);
			Triplas(&strT);
			
			comparaDuplas(&strD,dicty,&compD);
			comparaTriplas(&strT,dicty,&compT);
			
			/*int indice=0;
			
			for(indice=0;indice<256;indice++){
				cout << (char)indice << ": " << characteresSoloDict[indice] << ", " <<characteresSoloBase[indice] <<"\t    \t";
				if(indice%5==0)
					cout << endl;
			};// */
			cout << compD.at(0);
			cout << endl;
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
	// começa no 'A' até 'Z' vai para 'a' até 'z' aumenta um digito 'A','A'
	if(key[0]=='Z')
		key[0]='a';
	else if(key[0]=='z'){
		key[0]='A';
		if(key[1]=='\0'){
			key[1]='A';
			(*tamKey)++;
		}
		else if(key[1]=='Z')
			key[1]='a';
		else if(key[1]=='z'){
			key[1]='A';
			if(key[2]=='\0'){
				key[2]='A';
				(*tamKey)++;
			}
			else if(key[2]=='Z')
				key[2]='a';
			else if(key[2]=='z'){
				key[2]='A';
				if(key[3]=='\0'){
					key[3]='A';
					(*tamKey)++;
				}
				else if(key[3]=='Z')
					key[3]='a';
				else if(key[3]=='z'){
					key[3]='A';
					if(key[4]=='\0'){
						key[4]='A';
						(*tamKey)++;
					}
					else if(key[4]=='Z')
						key[4]='a';
					else if(key[4]=='z'){
						key[4]='A';
						if(key[5]=='\0'){
							key[5]='A';
							(*tamKey)++;
						}
						else if(key[5]=='Z')
							key[5]='a';
						else if(key[5]=='z'){
							key[5]='A';
							if(key[6]=='\0'){
								key[6]='A';
								(*tamKey)++;
							}
							else if(key[6]=='Z')
								key[6]='a';
							else if(key[6]=='z'){
								key[6]='A';
								if(key[7]=='\0'){
									key[7]='A';
									(*tamKey)++;
								}
								else if(key[7]=='Z')
									key[7]='a';
								else if(key[7]=='z'){
									key[7]='A';
									if(key[8]=='\0'){
										key[8]='A';
										(*tamKey)++;
									}
									else if(key[8]=='Z')
										key[8]='a';
									else if(key[8]=='z'){
										key[8]='A';
										if(key[9]=='\0'){
											key[9]='A';
											(*tamKey)++;
										}
										else if(key[9]=='Z')
											key[9]='a';
										else if(key[9]=='z'){
											(*tamKey)++;
										}else
											key[9]++;
										
									}else
										key[8]++;
								}else
									key[7]++;
							}else
								key[6]++;
						}else
							key[5]++;
					}else
						key[4]++;
				}else
					key[3]++;
			}else
				key[2]++;
		}else
			key[1]++;
	}else
		key[0]++;
};
void compararCharacteres(char *base,int *vetor){
	int indice=0,tam_string=strlen(base),local=0;
	for(indice=0;indice<tam_string;indice++){
		local=(base[indice]+CHARACTERES)%CHARACTERES;
		vetor[local]++;
	};
};
void Duplas(vector<string> *str){
	int i=0,j=0;
	char vec[2]={0,0};
	for(i=0,j=0;i<256;j++){
		if(j==0)
			vec[0]=i;
		vec[1]=j;
		string st(vec);
		str->push_back(st);
		if(j+1==256){
			i++;
			j=-1;
		};
	};
};
void Triplas(vector<string> *str){
	int i=0,j=0,k=0;
	char vec[3]={0,0,0};
	for(i=0,j=0,k=0;k<256;j++){
		if(j==0){
			vec[1]=i;
			if(i==0)
				vec[0]=k;
		}
		vec[2]=j;
		string st(vec);
		str->push_back(st);
		if(j+1==256){
			i++;
			j=-1;
			if(i+1==256){
				k++;
				i=0;
			};
		};
	};
};
void comparaDuplas(vector<string> *str, char *texto,vector<unsigned int> *dup){
	string dic(texto);
	unsigned int i=0,j=0;
	for(i=0 ; i < dic.size() -1; i++){
		string dp(dic.substr(i,2));
		for(j=0;j<str->size() ; j++){
			if(str->at(j).compare(dp)==0)
				dup->at(j)++;
			
		};
	};
};
void comparaTriplas(vector<string> *str, char *texto,vector<unsigned int> *trp){
	string dic(texto);
	unsigned int i=0,j=0;
	for(i=0 ; i < dic.size() -2; i++){
		string dp(dic.substr(i,3));
		for(j=0;j<str->size() ; j++){
			if(str->at(j).compare(dp)==0)
				trp->at(j)++;
			
		};
	};
};
