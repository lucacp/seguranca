#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1123456
using namespace std;

bool negative=false;

void zeroEsquerda(char *campo,int tam){
	int n=tam,i=0;
	if(!negative) i++;
	for(n=tam;n>=i;n--){
		if(campo[n]<='0'){
			campo[n]=0;
		}
		else
			return;
	}
}
void deslocarDireita(char *campo,int tam,int casas){
	int n=tam,i=0;
	for(i=0;i<n-casas+1;i++){
		campo[i]=campo[i+casas];
	};
	return;
}
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
	char Dobro[2]="2",Zero[2]="0";
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
			//printf("%s\n",outer);
			zeroEsquerda(outer,strlen(outer));
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
					if(nouter1+1==nouter2+1)
						outer[nouter1+1]+=outer[nouter1]/10+'0';
					else
						outer[nouter1+1]+=outer[nouter1]/10;
					outer[nouter1]=(outer[nouter1]%10)+'0';
				}
				else
					outer[nouter1]+='0';
			};
			zeroEsquerda(outer,sizeof(outer));
			for(casa=1;casa<casas;casa++){
				for(nouter1=0;nouter1<nouter2+casa;nouter1++){
					if(nouter1<casa)
						aux[nouter1]='0';
					else
						aux[nouter1]=((iner[nouter1-casa]-'0')*(iner2[casa]-'0'));
				}
				nouter2=strlen(iner);
				for(nouter1=casa;nouter1<nouter2+casa+1;nouter1++){
					if(aux[nouter1]>=10){
						if(nouter1+1<nouter2+casa+1)
							aux[nouter1+1]+=aux[nouter1]/10;
						aux[nouter1]=(aux[nouter1]%10)+'0';
					}else
						aux[nouter1]+='0';
				}
				Operacao(1,outer,aux,outer);
				//printf("%s\n",aux);
				zeroEsquerda(outer,sizeof(outer));
				memset(aux,0,sizeof(nouter2+1));
			};
			break;
		}
		case 3:{ //Divisão P/ modulo N (necessitando subtração)
			/** a divisão será realizada pela multiplicação do iner2 para poder subtrair do iner pelos numeros de maior valia
			 * caso a mult==0 aumenta o numero de casas iniciais, caso contrario é só fazer a mult para ver qual numero 
			 * que da resultado nao negativo para prosseguir as contas até terminar as possibilidades
			 * é necessário apresentar o quociente e o resto!
			 * nesta "case 3:" será unicamente o resto!
			 * o quociente sera na "case 7:"
			 * */
			char aux2[3][strlen(iner)*2],aux3[strlen(iner)];
			memset(aux3,0,sizeof(aux3));
			memset(aux2,0,sizeof(aux2));
			int casas=niner2,desloca=niner-niner2,i=0;
			for(i=0;i<desloca;i++){
				aux2[0][i]='0';
			};
			for(i=0;i<casas;i++){
				aux2[0][i+desloca]=iner2[i];
			};
			//printf("n1=%d\nn2=%d\n",niner,niner2);
			Operacao(2,aux2[0],Dobro,aux2[1]);
			Operacao(2,aux2[1],Dobro,aux2[2]);
			//printf("aux2= %s\n %s\n %s\ndesloca=%d\n",aux2[0],aux2[1],aux2[2],desloca);
			do{	
				Operacao(6,iner,aux2[0],aux3);
				//printf("%s, %s, %s.\n",aux2[0],aux2[1],aux2[2]);
				if(negative&&(desloca>0||aux2[0][0]=='0')){
					deslocarDireita(aux2[0],strlen(aux2[0]),1);
					deslocarDireita(aux2[1],strlen(aux2[1]),1);
					deslocarDireita(aux2[2],strlen(aux2[2]),1);
					negative=false;
				};
				memset(aux3,0,sizeof(aux3));
				Operacao(6,iner,aux2[0],aux3);//							1
				//printf("%s !  ",aux3);
				if(!negative){
					memcpy(iner,aux3,sizeof(aux3));
					memset(aux3,0,sizeof(aux3));
					Operacao(6,iner,aux2[1],aux3);//						+2
					if(negative){//										não
						negative=false;
						Operacao(6,iner,aux2[0],aux3);//					+1
						if(negative){
							negative=false;
							//printf("1:= %s\n",iner);
							//memcpy(iner,aux,sizeof(aux));//				1
						}
						else{
							//printf("2:= %s\n",aux3);
							memcpy(iner,aux3,sizeof(aux3));//			sim 1+1=2;
						}
					}
					else{//												3
						memcpy(iner,aux3,sizeof(aux3));
						memset(aux3,0,sizeof(aux3));	
						Operacao(6,iner,aux2[2],aux3);//                 +4
						if(negative){//									não
							negative=false;
							Operacao(6,iner,aux2[1],aux3);//				+2
							if(negative){//								não
								negative=false;
								Operacao(6,iner,aux2[0],aux3);//			+1
								if(negative){//							não
									//printf("3:= %s\n",iner);							
									negative=false;
									//memcpy(iner,aux,sizeof(aux));//		3;
								}
								else{//									sim	1+2+1=4;
									//printf("4:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
								}
							}
							else{//										5
								memcpy(iner,aux3,sizeof(aux3));
								memset(aux3,0,sizeof(aux3));
								Operacao(6,iner,aux2[0],aux3);//			+1
								if(negative){//							não
									//printf("5:= %s\n",iner);							
									negative=false;
									//memcpy(iner,aux,sizeof(aux));//		5
								}
								else{//									sim 5+1=6;
									//printf("6:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
								}
							}
						}
						else{//											7
							memcpy(iner,aux3,sizeof(aux3));
							memset(aux3,0,sizeof(aux3));
							Operacao(6,iner,aux2[1],aux3);//			   	+2
							if(negative){//								não
								negative=false;
								Operacao(6,iner,aux2[0],aux3);//		   	+1
								if(negative){//							não 7+0=7
									//printf("7:= %s\n",iner);							
									negative=false;
									//memcpy(iner,aux,sizeof(aux));
								}
								else{// 								sim: 7+1=8
									//printf("8:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
								}
							}
							else{ // 					 				sim: 7+2=9
								//printf("9:= %s\n",aux3);							
								memcpy(iner,aux3,sizeof(aux3));
							}	
						}
					}
				}
				//printf("%s,%d.\n",iner,desloca);
				desloca--;
			}while(desloca>=0);
			//printf("%s,%s.\n",iner,aux3);
			Operacao(1,iner,Zero,outer);
			break;
		}		
		case 4:{ //Exponenciação soma e mult
			if(niner2==1&&iner2[0]=='0'){
				outer[0]='1';
				return;
			}
			else if(niner2==1&&iner2[0]=='1'){
				iner2[0]='0';
				memcpy(outer,iner,strlen(iner)+1);
				return;}
			// Apartir daqui começa as exponenciações!
			char itera[23][8]={"2","4","8","61","23","46","821","652","215","4201","8402","6904","2918",
						   "48361","86723","63556","270131","441262","882425","6758401","2517902",
						   "4034914","8068838"};//2¹ até 2²³
			int iteracao=23,tamanho=strlen(iner2);
			char aux[strlen(iner2)+1],aux2[strlen(iner)+2];
			memset(aux,0,sizeof(aux));
			memset(aux2,0,sizeof(aux2));
			if(tamanho<8){
				negative=false;
				for(nouter1=0;nouter1<23;nouter1++){
					Operacao(6,iner2,itera[nouter1],aux);
					if(negative){
						iteracao=nouter1-1;
						nouter1=22;
					}
				}
				Operacao(6,iner2,itera[iteracao],aux);
				memset(iner2,0,strlen(iner2));
				Operacao(2,iner,iner,outer);
				for(nouter1=1;nouter1<iteracao;nouter1++){
					memcpy(iner2,outer,strlen(outer));
					getchar();
					Operacao(2,iner2,iner2,outer);
				}
			}
			else{
			
			}
			
			break;
		}		
		case 5:{ //inverso multiplicativo (subtração + divisão + soma + multi)
			
			
			
			break;
		}
		case 6:{ //subtração 
			/**a subtração pode ser somente para numeros positivos(resultado)
			 * então se o niner2 for maior então retorna no outer o numero todo zerado
			 * */
			if(nmaior<niner2){ 	
				nmaior=niner2; 
				inerflag=true;
			}
			else 
				nmenor=niner2;
			if(niner==niner2){
				if(iner[niner-1]<iner2[niner-1])
					inerflag=true;
			};
			bool passe=false;
			for(nouter1=0,nouter2=0;nouter2<nmaior&&!inerflag;nouter1++,nouter2++){
				if(nouter1<nmenor){
					if((iner[nouter2])<(iner2[nouter1])){ 
						passe=true;
					}
					else if((iner[nouter2])>(iner2[nouter1])){ 
						passe=false;
					}
					else if(passe) passe=true;
				}
				else{
					outer[nouter2]=iner[nouter2];
					passe=false;
				}
				if(passe&&nouter2+1==nmaior){
					if((iner[nouter2])<=(iner2[nouter1])) inerflag=true;
				}
			};
			
			int i=0;
			if(inerflag){
				for(i=0;i<nmaior;i++){
					outer[i]='0';
				}
				negative=true;
				zeroEsquerda(outer,sizeof(outer));
				break;
			};
			negative=false;
			for(nouter1=0,nouter2=0;nouter2<nmaior;nouter1++,nouter2++){
				if(nouter1<nmenor)
					outer[nouter2]=iner[nouter2]-iner2[nouter1];
				else
					outer[nouter2]=iner[nouter2];
			};
			passe=false;
			for(nouter2=0;nouter2<nmaior;nouter2++){
				//if(nouter1<nmenor)
					//outer[nouter2]+='0';
				//else
				if(outer[nouter2]<0&&!passe){
					outer[nouter2]+=10+'0';
					outer[nouter2+1]-=1;
					passe=true;
				}
				else if(outer[nouter2]<0&&passe){
					outer[nouter2]+=10+'0';
					outer[nouter2+1]-=1;
					passe=true;
				}
				else if(outer[nouter2]>=0&&outer[nouter2]<=9){
					outer[nouter2]+='0';
					passe=false;
				}
			};
			zeroEsquerda(outer,sizeof(outer));
			break;
		}
		case 7:{ //Divisão P/ modulo N (necessitando subtração)
			/** a divisão será realizada pela multiplicação do iner2 para poder subtrair do iner pelos numeros de maior valia
			 * caso a mult==0 aumenta o numero de casas iniciais, caso contrario é só fazer a mult para ver qual numero 
			 * que da resultado nao negativo para prosseguir as contas até terminar as possibilidades
			 * é necessário apresentar o quociente e o resto!
			 * nesta "case 7:" será unicamente o quociente!
			 * o resto sera na "case 3:"
			 * */
			char aux2[3][strlen(iner)*2],aux3[strlen(iner)],aux[]="0123456789";
			memset(aux3,0,sizeof(aux3));
			memset(aux2,0,sizeof(aux2));
			int casas=niner2,desloca=niner-niner2,i=0,pos=0;
			for(i=0;i<desloca;i++){
				aux2[0][i]='0';
			};
			for(i=0;i<casas;i++){
				aux2[0][i+desloca]=iner2[i];
			};
			//printf("n1=%d\nn2=%d\n",niner,niner2);
			Operacao(2,aux2[0],Dobro,aux2[1]);
			Operacao(2,aux2[1],Dobro,aux2[2]);
			//printf("aux2= %s\n %s\n %s\ndesloca=%d\n",aux2[0],aux2[1],aux2[2],desloca);
			do{	
				Operacao(6,iner,aux2[0],aux3);
				//printf("%s, %s, %s.\n",aux2[0],aux2[1],aux2[2]);
				if(negative&&(desloca>0||aux2[0][0]=='0')){
					negative=false;
					deslocarDireita(aux2[0],strlen(aux2[0]),1);
					deslocarDireita(aux2[1],strlen(aux2[1]),1);
					deslocarDireita(aux2[2],strlen(aux2[2]),1);
				}else if(desloca==0&&negative)	outer[pos++]=aux[0];
				memset(aux3,0,sizeof(aux3));
				Operacao(6,iner,aux2[0],aux3);//							1
				//printf("%s !   ",aux3);
				if(!negative){
					memcpy(iner,aux3,sizeof(aux3));
					memset(aux3,0,sizeof(aux3));
					Operacao(6,iner,aux2[1],aux3);//						+2
					if(negative){//										não
						negative=false;
						Operacao(6,iner,aux2[0],aux3);//					+1
						if(negative){
							negative=false;
							//printf("1:= %s\n",iner);
							outer[pos++]=aux[1];//				1
						}
						else{
							//printf("2:= %s\n",aux3);
							memcpy(iner,aux3,sizeof(aux3));//			sim 1+1=2;
							outer[pos++]=aux[2];
						}
					}
					else{//												3
						memcpy(iner,aux3,sizeof(aux3));
						memset(aux3,0,sizeof(aux3));	
						Operacao(6,iner,aux2[2],aux3);//                 +4
						if(negative){//									não
							negative=false;
							Operacao(6,iner,aux2[1],aux3);//				+2
							if(negative){//								não
								negative=false;
								Operacao(6,iner,aux2[0],aux3);//			+1
								if(negative){//							não
									//printf("3:= %s\n",iner);							
									negative=false;
									outer[pos++]=aux[3];//				3;
								}
								else{//									sim	1+2+1=4;
									//printf("4:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
									outer[pos++]=aux[4];
								}
							}
							else{//										5
								memcpy(iner,aux3,sizeof(aux3));
								memset(aux3,0,sizeof(aux3));
								Operacao(6,iner,aux2[0],aux3);//			+1
								if(negative){//							não
									//printf("5:= %s\n",iner);							
									negative=false;
									outer[pos++]=aux[5];//		5
								}
								else{//									sim 5+1=6;
									//printf("6:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
									outer[pos++]=aux[6];
								}
							}
						}
						else{//											7
							memcpy(iner,aux3,sizeof(aux3));
							memset(aux3,0,sizeof(aux3));
							Operacao(6,iner,aux2[1],aux3);//			   	+2
							if(negative){//								não
								negative=false;
								Operacao(6,iner,aux2[0],aux3);//		   	+1
								if(negative){//							não 7+0=7
									//printf("7:= %s\n",iner);							
									negative=false;
									outer[pos++]=aux[7];
								}
								else{// 								sim: 7+1=8
									//printf("8:= %s\n",aux3);							
									memcpy(iner,aux3,sizeof(aux3));
									outer[pos++]=aux[8];
								}
							}
							else{ // 					 				sim: 7+2=9
								//printf("9:= %s\n",aux3);							
								memcpy(iner,aux3,sizeof(aux3));
								outer[pos++]=aux[9];
							}	
						}
					}
				}
				//printf("%s,%d.\n",iner,desloca);
				desloca--;
			}while(desloca>=0);
			//printf("%s,%s.\n",iner,aux3);
			//Operacao(1,iner,Zero,outer);
			break;		
		};
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
	//printf("\n1-soma\n2-multiplicacao\n3-divisao-resto\n4-exponenciacao(incompleta)\n5-inversa-multiplicativa(incompleta)\n6-subtracao\n7-divisao-quociente(incompleta)\ndigite sua operacao: ");
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
