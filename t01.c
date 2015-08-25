#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define MAX_PRINT 112
#define KEY_NULL 11
#define KEY_ONE 12
#define OKAY 13
#define FILE_INVALID 1313

/**
 *	Trabalho 1  cifra de cesar + transposição + vigenere + substituição
 *  compilar: gcc -Wall t01 t01.c													        (a) para comparação Trabalho 2 a<c,t,v,s>
 * 	Executar ./t01 <nomearquivobase> <numerochave>/<letrasChave>/<nomearquivochave> <c,t,v,s,a> <nomearquivosaida>
 * 								(cesar&transposição)/(vigenere)/(substituição)     tipo da cifra; arq de saida será truncado e criado!
 * 	obs: ./t01 <nomearquivobase> é feito Cesar no proprio arquivo com chave 3!!!
 * 	obs2: ./t01 <nomearquivobase> <numerochave> é Cesar com outra chave no mesmo arquivo!!
 *  obs3: -<numerochave> é decriptografação de cesar e transposição somente! para decriptografação de vigenere junto com v coloque um d ou seja vd 
 **/
void cesarCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out);
int transposicaoCrypt(FILE *arq,int key,int ind_arq,int arquivo,FILE *out);
void vigenereCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt);
int substituicaoCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out,int dcrpt);
int ComparacaoCifraCesar(FILE *arq1,int ind_arq,FILE *arq2);
void comparacaoCifraVigenere(FILE *arq1,int ind_arq,FILE *arq2,char *chave);
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
			if(args[4]!=NULL){	// 'a' é para comparação de dois arquivos um criptografado e outro descriptografado, para achar a chave de césar
				if(args[4]!=args[1]){
					if(tipo!='a')
						out=fopen(args[4],"w+b");
					else
						out=fopen(args[4],"r+b");
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
			break;
		};
		case 's':{
			int retorno=0;
			if(args[3][1]=='d')
				dcrpt=1;
			retorno=substituicaoCrypt(arq,args[2],ind_arq,arquivo,out,dcrpt);
			if(retorno==FILE_INVALID){
				printf("este arquivo chave e invalido");
				exit(0);
			};
			break;
		};
		case 'a':{
			int chave=0;
			char typ=args[3][1];
			char chave_key[ind_arq];
			memset(chave_key,0,sizeof(char)*ind_arq);
			if(typ=='c'){
				chave=ComparacaoCifraCesar(arq,ind_arq,out);
				printf(" %d\n",chave);			
			}
			else if(typ=='v'){
				comparacaoCifraVigenere(arq,ind_arq,out,chave_key); 
				printf("%s",chave_key);
			}
			else if(typ=='t'){
		//		chave=comparacaoCifraTransposicao(arq,ind_arq,out);
				printf(" %d\n",chave);
			}
			else if(typ=='s'){
				int i=0;
			//	comparacaoCifraSubstituicao(arq,ind_arq,out,chave_key);
				for(i = 0; i< ind_arq;i++)
					printf("%d",chave_key[i]);
			};
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
};
int substituicaoCrypt(FILE *arq,char *key,int ind_arq,int arquivo,FILE *out ,int dcrpt ){
	char c[2]=" ",k[3];
	int principal[256],ind_key=0,ind_atual=0,id=0,campo=0;
	/*for( campo = 0, digito=0 ; campo < 256 ; campo++ ){ if(dcrpt==1){if( campo < id_key){bytes[campo]=campo;bytes[(int)key[campo]]=key[campo];}else if(bytes[campo]==' '){if(bytes[digito]==' '){bytes[campo]=campo;bytes[digito]=digito;digito++;}else{while(digito<256){++digito;if(bytes[digito]==' '){bytes[campo]=campo;bytes[digito]=digito;digito++;break;}};};}}else if( campo < id_key){bytes[campo]=key[campo];bytes[(int)key[campo]]=campo;}else if(bytes[campo]==' '){if(bytes[digito]==' '){bytes[campo]=digito;bytes[digito]=campo;digito++;}else{while(digito<256){++digito;if(bytes[digito]==' '){bytes[campo]=digito;bytes[digito]=campo;digito++;break;}};};};};if(dcrpt==1){for(campo=0;campo<256;campo++){bytes[campo]*=(-1);};};*/
	FILE *chave_arq=NULL;
	if((chave_arq=fopen(key,"r+b"))==NULL){
		return FILE_INVALID;
	};
	fseek(chave_arq,0,SEEK_END);
	ind_key=ftell(chave_arq);
	rewind(chave_arq);
	
	while(ind_atual<ind_key){
		if(feof(chave_arq)) break;
		fread(k,sizeof(char),3,chave_arq);
		for(id=0;id<3;id++){
			if(k[id]==' '){
				k[id]='0';
			};
		};	
		id=0;
		fflush(chave_arq);
		fgetc(chave_arq);
		id=atoi(k);
		id=(id+256)%256;
		if(dcrpt==1)
			principal[id]=ind_atual;
		else
			principal[ind_atual]=id;
		ind_atual++;
		fflush(chave_arq);
		
	};
	ind_atual=0;
	fclose(chave_arq);
	while(ind_arq>ind_atual){
		if(feof(arq)) break;
		c[0]=fgetc(arq);
		//printf("%d",c[0]);
		campo=(c[0]+256)%256;
		c[0]=principal[campo];
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
	return OKAY;
}
int ComparacaoCifraCesar(FILE *arq1,int ind_arq,FILE *arq2){
	int chave_atual=0,chave_ant=0,ind_atual=0,alterado=0;
	char c1=' ',c2=' ';
	while(ind_arq>ind_atual){	
		chave_ant=chave_atual;
		fread(&c1,sizeof(char),1,arq1);
		fread(&c2,sizeof(char),1,arq2);
		fflush(arq1);
		fflush(arq2);
		chave_atual=(c2-c1+256)%256;
		//printf("%d",chave_atual);
		if(chave_atual==chave_ant){
			alterado--;
		}else
			alterado++;
		ind_atual++;
		
	};
	//printf("\nalterado: %d \n",alterado); //muito positivo: muita variação, muito negativo: é cesar key-->chave_atual
	if(alterado < (-ind_arq/2))
		printf("Cifra de Cesar\nChave:");
	return chave_ant;
};
void comparacaoCifraVigenere(FILE *arq1,int ind_arq,FILE *arq2,char *chave){
	int chave_atual=0,chave_ant=0,ind_atual=0,ind_key_atual=0,tam_key=0;
	char c1=' ',c2=' ';
	memset(chave,0,sizeof(char)*ind_arq);
	while(ind_arq>ind_atual){	
		fread(&c1,sizeof(char),1,arq1);
		fread(&c2,sizeof(char),1,arq2);
		fflush(arq1);
		fflush(arq2);
		chave_atual=(c2-c1+256)%256;
		if(chave_atual!=chave_ant){
			chave[ind_key_atual++]=chave_atual;
			chave_ant=chave_atual;
		};
		ind_atual++;
	};
	int i=0;
	for(i = 0 ; i < ind_key_atual; i++ ){
		if(chave_atual==chave[i]){
			tam_key+=i-1;
		}
	};
	//printf("%d",tam_key);
	
}
void comparacaoCifraSubstituicao(FILE *arq1,int ind_arq,FILE *arq2,char *chave){
	
}
