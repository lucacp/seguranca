#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1123456
using namespace std;

void Operacao(int op,char *iner,char *iner2,char *outer){
	int niner=0,niner2=0,nouter1=0,nouter2=0,nmaior=0,nmenor=0;
	bool inerflag=false;
	niner=strlen(iner);
	nmaior=niner;
	nmenor=niner;
	niner2=strlen(iner2);		
	switch(op){
		case 1:{//SOMA
			if(nmaior<niner2){ 	nmaior=niner2; inerflag=true;}
			else 				nmenor=niner2;
			
			for(nouter1=nmenor,nouter2=nmaior;nouter2>=0;nouter1--,nouter2--){
				if(inerflag){
					if(nouter1>=0)
						outer[nouter2+1]=((iner[nouter1]-'0')+(iner2[nouter2]-'0'))+'0';
					else
						outer[nouter2+1]=iner2[nouter2];
				}else{
					if(nouter1>=0)
						outer[nouter2+1]=((iner[nouter2]-'0')+(iner2[nouter1]-'0'))+'0';
					else
						outer[nouter2+1]=iner[nouter2];
					};
			};
			
			for(nouter1=nmaior;nouter1>=0;nouter1--){
				if(outer[nouter1]>'9'){
					if(outer[nouter1-1]>'0')
						outer[nouter1-1]++;
					else
						outer[nouter1-1]='1';
					outer[nouter1]-=10;
				}else if(outer[nouter1]<'0'){
					outer[nouter1]+='0';
				}
			};
			break;
		}
		case 2:{ //MULTIPLICACAO
			
			
			
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
	Operacao(op,iner,iner2,outer);
	printf("%s\n",outer);


	return 0;
}
