#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1123456
using namespace std;

void Operacao(int op,char *iner,char *iner2,char *outer){
	int niner=0,niner2=0,nouter=0,nmaior=0;
	switch(op){
		case 1:{
			for(niner=0;niner<MAX;niner++){
				if(iner[niner]==0){
					break;
				}
			}
			nmaior=niner;
			for(niner2=0;niner2<MAX;niner2++){
				if(iner2[niner2]==0){
					break;
				}
			}
			if(nmaior<niner2) nmaior=niner2;
			
			for(nouter=0;nouter<nmaior+1;nouter++){
				outer[nouter]=((iner[nouter]-'0')+(iner2[nouter]-'0'))+'0';
			};
			for(nouter=0;nouter<nmaior+2;nouter++){
				if(outer[nouter]>'9'){
					if(outer[nouter+1]>'0')
						outer[nouter+1]++;
					else
						outer[nouter+1]='1';
					outer[nouter]-=10;
				}else if(outer[nouter]<'0'){
					outer[nouter]+='0';
				}
			};
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
