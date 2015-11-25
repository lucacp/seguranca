#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1123456
using namespace std;
void inverter(char *campo,int tam){
	int n=tam,i=0;
	char aux[tam];
	memset(aux,0,sizeof(aux));
	for(;n>0;n--,i++){
		aux[i]=campo[n-1];
	}
	if(aux[0]==0)
		for(i=1,n=strlen(campo);i<n;i++){
			campo[i]=aux[i];
		}
		else
			for(i=0,n=tam;i<n;i++){
				campo[i]=aux[i];
			}
}
void Operacao(int op,char *iner,char *iner2,char *outer){
	int niner=0,niner2=0,nouter1=0,nouter2=0,nmaior=0,nmenor=0;
	bool inerflag=false;
	niner=strlen(iner);
	nmaior=niner;
	nmenor=niner;
	niner2=strlen(iner2);		
	switch(op){
		case 1:{//SOMA
			if(nmaior<niner2){ 	
				nmaior=niner2; 
				inerflag=true;
			}
			else 
				nmenor=niner2;
			
			for(nouter2=0,nouter1=0;nouter2<nmaior;nouter2++,nouter1++){
				if(inerflag){
					if(nouter1<nmenor)
						outer[nouter2]=((iner[nouter1]-'0')+(iner2[nouter2]-'0'))+'0';
					else
						outer[nouter2]=iner2[nouter2];
				}else{
					if(nouter1<nmenor)
						outer[nouter2]=((iner[nouter2]-'0')+(iner2[nouter1]-'0'))+'0';
					else
						outer[nouter2]=iner[nouter2];
					};
			};
			nouter2=strlen(outer);
			for(nouter1=0;nouter1<nouter2;nouter1++){
				if(outer[nouter1]>'9'){
					//printf(" %d,'%c' ",outer[nouter1],outer[nouter1]);
					if(outer[nouter1+1]>'0')
						outer[nouter1+1]++;
					else
						outer[nouter1+1]='1';
					outer[nouter1]-=10;
				}/*else if(outer[nouter1]<'0'){
					outer[nouter1]+='0';
				}*/
			};
			break;
		}
		case 2:{ //MULTIPLICACAO
			/**a multiplicação será redução dos characteres em '0' para multiplica-los em ordem reversa,
			 * ou seja, será multiplicado os ultimos numeros( unidades ) colocando os por primeiro na saida
			 * após será invertido sua ordem.
			 * alterado para ja ter invertido a ordem logo de começo!
			 * */
			char aux[MAX];
			memset(aux,0,sizeof(aux));
			nouter2=strlen(iner);int casa=0,casas=strlen(iner2);
			for(nouter1=0;nouter1<nouter2;nouter1++){
				outer[nouter1]=((iner[nouter1]-'0')*(iner2[casa]-'0'));
			}
			for(nouter1=0;nouter1<nouter2+1;nouter1++){
				if(outer[nouter1]>10){
					outer[nouter1+1]+=outer[nouter1]/10;
					outer[nouter1]=(outer[nouter1]%10)+'0';
				}
				else if(nouter1!=nouter2)
					outer[nouter1]+='0';
			}
			for(casa=1;casa<casas;casa++){
				for(nouter1=0;nouter1<nouter2+casa;nouter1++){
					if(nouter1<casa)
						aux[nouter1]='0';
					else
						aux[nouter1]=((iner[nouter1-casa]-'0')*(iner2[casa]-'0'));
				}
				nouter2=strlen(iner);
				for(nouter1=casa;nouter1<nouter2+casa+1;nouter1++){
					if(aux[nouter1]>10){
						if(nouter1+1<nouter2+casa+1)
							aux[nouter1+1]+=aux[nouter1]/10;
						aux[nouter1]=(aux[nouter1]%10)+'0';
					}else if(aux[nouter1]<10)
						aux[nouter1]+='0';
				}
				Operacao(1,outer,aux,outer);
				//printf("%s\n",aux);
				memset(aux,0,sizeof(nouter2+1));
			};
			break;
		}
		case 3:{ //Divisão P/ modulo N (necessitando subtração)
			
			
			
			break;
		}		
		case 4:{ //Exponenciação soma e mult
			
			
			
			break;
		}		
		case 5:{ //inverso multiplicativo (subtração + divisão + soma + multi)
			
			
			
			break;
		}
		case 6:{ //subtração 
			
			
			
			break;
		}		
	}
}

int main(int argc,char* args[]){
	
	int op=0;
	char iner[MAX],iner2[MAX],outer[MAX];
	memset(iner,0,sizeof(iner));
	memset(iner2,0,sizeof(iner2));
	memset(outer,0,sizeof(outer));
	scanf("%s",iner);
	getchar();
	scanf("%s",iner2);
	getchar();
	//printf("\n1-soma\ndigite sua operacao: ");
	scanf("%d",&op);
	//printf("%s\n",iner);
	inverter(iner,strlen(iner));
	//printf("%s\n",iner);
	//printf("%s\n",iner2);
	inverter(iner2,strlen(iner2));
	//printf("%s\n",iner2);
	Operacao(op,iner,iner2,outer);
	//printf("%s\n",outer);
	inverter(outer,strlen(outer));
	printf("%s\n",outer);


	return 0;
}
