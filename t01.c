#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define MAX_PRINT 212

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 * 
 **/

int main(int argc,char* args[]){
	FILE *arq=NULL,*out=NULL;
	char c[2]=" ",tipo='c';
	int ind_arq=0,ind_atual=0,key=3,dcrpt=0,arquivo=0;
	if((arq=fopen(args[1],"r+b"))==NULL){
		printf("nao foi possivel abrir ( - _ - )\n");
		exit(0);
	}
	if(args[2]!=NULL){
		key=atoi(args[2]); 		//argumento 2 é a chave, por padrão a chave será +3. para 
		if(args[3]!=NULL){ 		//	argumento 3 é o tipo de criptografia: 'c' para cifra de cesar(cesar é padrão, então se não escrever o 3º argumento será cifra de cesar),
			tipo=args[3][0]; 	//   't' de transposição, 'v' de vigenere e 's' de subtituição. 
			if(args[4]!=NULL){
				out=fopen(args[4],"w+b");
				if(!out){
					printf("nao e possivel escrever este arquivo neste local");
					exit(0);
				}
				arquivo=1;
			}
		}
	};
	//printf("%s\n",args[0]);
	//printf("%s\n",args[1]);
	fseek(arq,0,SEEK_END);
	ind_arq=ftell(arq);
	ind_atual=0;
	rewind(arq);
	rewind(out);
	switch(tipo){
		case 'c':{
			while(ind_arq>ind_atual){
				if(feof(arq)) break;
				c[0]=fgetc(arq);
				if(ind_arq<MAX_PRINT)
					printf("%c",c[0]);
				c[0]=(c[0]+(char)key+126)%126;
				if(arquivo==1){
					fwrite(c,sizeof(char),1,out);
					fflush(out);
				}
				else{
					fseek(arq,ind_atual,SEEK_SET);
					fwrite(c,sizeof(char),1,arq);
					fflush(arq);
				};
				ind_atual++;
				
			};
			break;
		};
		case 't':{
			if(key==0){
				printf("\nA cifra de Transicao necessita uma chave que nao seja nula\n");
				exit(0);
			}
			else if(key<0){
				key=key*(-1);
				if(key==1){
					printf("\nA cifra de Transicao necessita de uma chave de tamanho maior que 1 uma linha\n");
					exit(0);
				};
				dcrpt=1;
			};
			//printf("%d",key);
			char mat[key][MAX];
			char matD[MAX][key];
			int caso=0,col=0,colD=0,maxMat=MAX*key,fatMat=0,ind_mat=0;
			while(ind_arq>ind_atual){
				if(feof(arq)) break;
				c[0]=fgetc(arq);
				//if(ind_arq<MAX_PRINT)
					printf("%c",c[0]);
				caso=ind_atual%key;				
				if(dcrpt==1){
					matD[colD][caso]=(c[0]+126)%126;
					printf("%s",matD[0]);
					if(caso+1==key)
						colD++;
				}else{
					mat[caso][col]=(c[0]+126)%126;
					printf("%s\n",mat[0]);
					if(caso+1==key)
						col++;
				};
				//fflush(arq);
				ind_mat++;
				if(ind_atual+1%maxMat==0){
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
					col=0;
					colD=0;
				};
				fflush(arq);
				ind_atual++;
				
			};
			if(ind_mat<maxMat){
				while(ind_mat<maxMat){
					if(dcrpt==1){
						
					}
					else{
					
					}
				}
			};
			
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
	rewind(out);
	ind_atual=0;
	if(ind_arq<MAX_PRINT)
		while(ind_arq>ind_atual){
			if(feof(arq)) break;
			fread(c,sizeof(char)*1,1,arq);
			if(ind_arq<MAX_PRINT)
				printf("%c",c[0]);
			ind_atual++;
		};
	printf("(>_<)\n");
	fclose(out);
	fclose(arq);
	
	return 0;
}

