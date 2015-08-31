#include <cstdio>
#include <cstdlib>
#include <string.h>
#define MAX 10
#define MAX_PRINT 112
#define KEY_NULL 11
#define KEY_ONE 12
#define OKAY 13
#define FILE_INVALID 1313
#define CHARACTERES 256

/**
 * Trabalho 3 ataque força bruta com dicionario
 * objetivo: decifrar com cesar transposição e vigenere(curta) verificando chave com dicionario + heuristicas
 * 
 */
	void cesarCrypt(char *base,int key,int ind_arq,char *teste);
	int transposicaoCrypt(char *base,int key,int ind_arq,char *teste);
	void vigenereCrypt(char *base,char *key,int ind_arq,char *teste,int dcrpt);
 
int main(int argc,char* args[]){
	FILE *arq=NULL,*out=NULL;
	int ind_arq=0,ind_atual=0,key=1;
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
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	rewind(arq);
	char base[ind_arq],teste[ind_arq];
	memset(base,0,sizeof(char)*ind_arq);
	memset(teste,0,sizeof(char)*ind_arq);
	fread(base,sizeof(char),ind_arq,arq);
	fflush(arq);
	
	
	fclose(arq);
	fclose(out);
	return 0;
}
int cesarCrypt(char *base,int key,int ind_arq,char *teste){
	char c=0;
	int ind_atual=0,chave_atual=0,chave_ant=0;
	while(ind_arq>ind_atual){
		c=(base[ind_atual]+key+CHARACTERES)%CHARACTERES;
		teste[ind_atual]=c;
		ind_atual++;
	};
};
int transposicaoCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out){
	char c[2]=" ";
	int dcrpt=0,resto=0,tamMat,tamLin=0;
	if(key==0){
		return KEY_NULL;
	}
	else if(key<0){
		key=key*(-1);	
		dcrpt=1;
	};
	resto=ind_arq%key;
	tamMat=ind_arq+resto;
	tamLin=ind_arq/key;
	if(resto!=0)
		tamLin++;
	//printf("%d",key);
	char mat[tamMat];
	//char matD[MAX*key];
	int ind_atual=0,caso=0,col=0,colD=0,ind_mat=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		//if(ind_arq<MAX_PRINT)
		//	printf("%c",c[0]);
						
		if(dcrpt==1){
			caso=ind_atual%tamLin;
			mat[key*caso+colD]=c[0];
			//if(ind_arq<MAX_PRINT)
			//	printf("%s",mat);
			if(caso+1==tamLin)
				colD++;
		}else{
			caso=ind_atual%key;
			mat[caso*tamLin+col]=c[0];
			//if(ind_arq<MAX_PRINT)
				//printf("%s\n",mat[caso]);
			if(caso+1==key)
				col++;
		};
		fflush(arq);
		ind_atual++;
		ind_mat++;
	};
	if(resto!=0){
		char idc=0;
		int i;
		for( i = 0 ; i < resto ; i++ ){
			mat[ind_mat]=idc;
			idc++;
		};
	};
	if(arquivo==1){
		fwrite(mat,sizeof(char)*tamMat,1,out);
		fflush(out);
	}
	else{
		fseek(arq,0,SEEK_SET);
		fwrite(mat,sizeof(char)*tamMat,1,arq);
		fflush(arq);
	};
	return OKAY;
};
void vigenereCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt){
	char c[2]=" ";
	int campo=0,id_key=strlen(key),chav=0,ind_atual=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		if(ind_arq<MAX_PRINT)
			printf("%c",c[0]);
		campo=ind_atual%id_key;
		chav=(char)key[campo];
		if (dcrpt==1)
		{
			chav=chav*-1;
		};
		if(ind_arq<MAX_PRINT)
			printf("%c",(char)chav);
		c[0]=(char)(c[0]+(int)chav+CHARACTERES)%CHARACTERES;
		if(arquivo==1){
			fwrite(c,sizeof(char),1,out);
			fflush(out);
		}
		else{
			fseek(arq,ind_atual,SEEK_SET);
			fwrite(c,sizeof(char),1,arq);
		};
		fflush(arq);
		ind_atual++;	
	};
};
