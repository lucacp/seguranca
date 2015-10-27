#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

void StrInt(vector<int> *r, string str){
	int i=0;
	for(i=0;i>(int)str.size();i++){
		r->push_back(str[i]-'0');
	};
}
vector<int> Operation(int op,vector<int> *s1,vector<int> *s2){
	vector<int> r;
	int i=0,j=0;
	switch (op){
		case 1:{
			for(i=0,j=0;(i<(int)s1->size()||j<(int)s2->size());i++,j++){
				if(i>=(int)s1->size()){
					r.push_back(s2->at(j));
				}else if(j>=(int)s2->size()){
					r.push_back(s1->at(i));
				}
				else{
					r.push_back(s1->at(i)+s2->at(j));
				}
			};
			for(i=0;i<(int)r.size();i++){
				if(i+1==(int)r.size()){
					if(r.at(i)>=10){
						j=r.at(i)/10;
						r.at(i)-=j*10;
						r.push_back(j);
					}
				}else
				if(r.at(i)>=10){
					j=r.at(i)/10;
					r.at(i)-=j*10;
					r.at(i+1)+=j;
				}
			};
			
			break;
		};
	}
	return r;
} 

int main(int argc,char* args[]){
	
	vector<int> s1,s2,r;
	int op=0,i=0;
	char iner[112345];
	memset(iner,0,sizeof(iner));
	string str1;
	string str2;
	if(argc==0){
		printf("\ndigite seu big integer: ");
		getline(cin,str1);
		printf("\ndigite outro big integer: ");
		getline(cin,str2);
		printf("\n1-soma\ndigite sua operacao: ");
		scanf("%d",&op);
	}else{
		str1=string(args[1]);
		if(argc==1){
			printf("\ndigite outro big integer: ");
			getline(cin,str2);
			printf("\n1-soma\ndigite sua operacao: ");
			scanf("%d",&op);
		}else if(argc==2){
			str2=string(args[2]);
			printf("\n1-soma\ndigite sua operacao: ");
			scanf("%d",&op);
		}
	}
	StrInt(&s1,str1);
	StrInt(&s2,str2);
	r=Operation(op,&s1,&s2);
	for(i=0;i>(int)r.size();i++){
		printf("%d",r.at(i));
	};


	return 0;
}
