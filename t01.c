#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define MAX_PRINT 112
#define KEY_NULL 11
#define KEY_ONE 12
#define OKAY 13

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/
void cesarCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out);
int transposicaoCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out);
void vigenereCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt);
void substituicaoCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt);

int main(int argc,char* args[]){
	FILE *arq=NULL,*out=NULL;
	char tipo='c';
	int ind_arq=0,ind_atual=0,key=3,dcrpt=0,arquivo=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	if(args[2]!=NULL){
		key=atoi(args[2]); 		//argumento 2 é a chave, por padrão a chave será +3. para 
		if(args[3]!=NULL){ 		// argumento 3 é o tipo de criptografia: 'c' para cifra de cesar(cesar é padrão, então se não escrever o 3º argumento em diante será a cifra de cesar),
			tipo=args[3][0]; 	// 't' de transposição, 'v' de vigenere e 's' de subtituição.(para vigenere e substituição para decriptofrafar é necessário um 'd' junto com 'v' ou 's') 
			if(args[4]!=NULL){
				if(args[4]!=args[1]){
					out=fopen(args[4],"w+b");
					if(!out){
						printf("nao e possivel escrever este arquivo neste local");
						exit(0);
					};
					arquivo=1;
				};
			};
		};
	};
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	rewind(arq);
	//rewind(out);
	switch(tipo){
		case 'c':{
			cesarCrypt(arq,key,ind_arq,arquivo,out);
			break;
		};
		case 't':{
			ind_atual=transposicaoCrypt(arq,key,ind_arq,arquivo,out);
			if(ind_atual==KEY_NULL){
				printf("\nA cifra de Transicao necessita uma chave que nao seja nula\n");
				exit(0);
			}
			else if(ind_atual==KEY_ONE){
				printf("\nA cifra de Transicao necessita de uma chave de tamanho maior que 1 uma linha\n");
				exit(0);
			}
			break;
		};
		case 'v':{
			// deixar em função para criptografar e outra para decriptografar
			if(args[3][1]=='d')
				dcrpt=1;
			vigenereCrypt(arq,args[2],ind_arq,arquivo,out,dcrpt);
		};
		case 's':{
			if(args[3][1]=='d')
				dcrpt=1;
			subtituicaoCrypt(arq,args[2],ind_arq,arquivo,out,dcrpt);
			break;
		};
		default:{
			printf("Opcao escolhida nao corresponde a nenhuma criptografia disponivel!\n");
			exit(0);
			break;
		};
	}
	printf("( ° 3 ° )\n");
	fclose(out);
	fclose(arq);
	
	return 0;
}

void cesarCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out){
	char c[2]=" ";
	int ind_atual=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		if(ind_arq<MAX_PRINT)
			printf("%c",c[0]);
		c[0]=(c[0]+(char)key+256)%256;
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
int transposicaoCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out){
	char c[2]=" ";
	int dcrpt=0;
	if(key==0){
		return KEY_NULL;
	}
	else if(key<0){
		key=key*(-1);	
		dcrpt=1;
	};
	if(key==1){
			return KEY_ONE;
	};
	//printf("%d",key);
	char mat[key][MAX];
	char matD[MAX][key];
	int ind_atual=0,caso=0,col=0,colD=0,maxMat=MAX*key,fatMat=0,ind_mat=0;
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		//if(ind_arq<MAX_PRINT)
		//	printf("%c",c[0]);
		caso=ind_atual%key;				
		if(dcrpt==1){
			matD[colD][caso]=c[0];
			if(ind_arq<MAX_PRINT)
				printf("%s",matD[colD]);
			if(caso+1==key)
				colD++;
		}else{
			mat[caso][col]=c[0];
			if(ind_arq<MAX_PRINT)
				printf("%s\n",mat[caso]);
			if(caso+1==key)
				col++;
		};
		fflush(arq);
		ind_mat++;
		if((ind_atual+1)%maxMat==0){
			int id=0;
			if(arquivo==1){	
				for(id=0;id<key;id++){
					if(dcrpt==1)
						fwrite(matD[id],sizeof(char)*MAX,1,out);
					else
						fwrite(mat[id],sizeof(char)*MAX,1,out);
					fflush(out);
				};	
			}
			else{
				for(id=0;id<MAX;id++){
					fseek(arq,(MAX*id),SEEK_SET);
					if(dcrpt==1)
						fwrite(matD[id],sizeof(char)*key,1,arq);
					else
						fwrite(mat[id],sizeof(char)*key,1,arq);
					fflush(arq);
				};
				fatMat++;
			};
			ind_mat=0;
			col=0;
			colD=0;
		};
		fflush(arq);
		ind_atual++;
		
	};
	if(ind_mat<=maxMat){
		char idc='a';
		while(ind_mat<maxMat){
			caso=ind_mat%key;
			if(dcrpt==1){
				matD[colD][caso]=(idc+256)%256;
				if(caso+1==key)
					colD++;
				idc++;
			}
			else{
				mat[caso][col]=(idc+256)%256;
				if(caso+1==key)
					col++;
				idc++;
			}
			ind_mat++;
		};
		if(arquivo==1){
			int id=0;
			for(id=0;id<key;id++){
				if(dcrpt==1)
					fwrite(matD[id],sizeof(char)*MAX,1,out);
				else
					fwrite(mat[id],sizeof(char)*MAX,1,out);
				fflush(out);
			}
			ind_mat=0;
		}
		else{
			int id=0;
			for(id=0;id<key;id++){
				fseek(arq,(MAX)*id,SEEK_SET);
				if(dcrpt==1)
					fwrite(matD[id],sizeof(char)*MAX,1,arq);
				else
					fwrite(mat[id],sizeof(char)*MAX,1,arq);
				fflush(arq);
			};
			fatMat++;
			ind_mat=0;
		};
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
		c[0]=(char)(c[0]+(int)chav+256)%256;
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
	break;
};
void substituicaoCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt){
	char c[2]=" ";
	int campo=1,id_key=strlen(key),chav=0;
	for (campo = 1; campo < id_key; ++campo ){
		for (chav = 0; chav < campo; ++chav ){
			if(key[campo]==key[chav]&&campo<id_key)
				key[campo]=key[campo+1];
		};
	};
	
};