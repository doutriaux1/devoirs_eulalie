#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define TMAX 256

typedef struct etiq{
	int registre;
	char etiquette;
	struct etiq* suivant;
} Etiquette;

typedef struct{
	Etiquette* tete; 
} Liste; 


int code(char* s){
	if (strstr(s,"XOR")!=NULL){
		return 1;
	}
	else if (strstr(s,"OR")!=NULL){
		return 0;
	}
	else if (strstr(s,"AND")!=NULL){
		return 2;
	}
	else if (strstr(s,"ADD")!=NULL){
		return 3;
	}
	else if (strstr(s,"SUB")!=NULL){
		return 4;
	}
	else if (strstr(s,"MUL")!=NULL){
		return 5;
	}
	else if (strstr(s,"DIV")!=NULL){
		return 6;
	}
	else if (strstr(s,"SHR")!=NULL){
		return 7;
	}
	else if (strstr(s,"LDB")!=NULL){
		return 8;
	}
	else if (strstr(s,"LDH")!=NULL){
		return 9;
	}
	else if (strstr(s,"LDW")!=NULL){
		return 10;
	}
	else if (strstr(s,"STB")!=NULL){
		return 11;
	}
	else if (strstr(s,"STH")!=NULL){
		return 12;
	}
	else if (strstr(s,"STW")!=NULL){
		return 13;
	}
	else if (strstr(s,"JMP")!=NULL){
		return 20;
	}
	else if (strstr(s,"JZS")!=NULL){
		return 21;
	}
	else if (strstr(s,"JZC")!=NULL){
		return 22;
	}
	else if (strstr(s,"JCS")!=NULL){
		return 23;
	}
	else if (strstr(s,"JCC")!=NULL){
		return 24;
	}
	else if (strstr(s,"JNS")!=NULL){
		return 25;
	}
	else if (strstr(s,"JNC")!=NULL){
		return 26;
	}
	else if (strstr(s,"IN")!=NULL){
		return 28;
	}
	else if (strstr(s,"OUT")!=NULL){
		return 29;
	}
	else if (strstr(s,"RND")!=NULL){
		return 30;
	}
	else if (strstr(s,"HLT")!=NULL){
		return 31;
	}
	return 99;
}


int destination(char *s){
	if((code(s)>=20 && code(s)<=26) || code(s)==31){
		return 0; 
	}
	else{
		int i=0;
		while(s[i]!='\0' && ( s[i]!='R' || !isdigit(s[i+1])) ){
			i++;
		}
		if(s[i]=='\0' || !isdigit(s[i+1]) ){
			return 99;
		}
		if (isdigit(s[i+2])){
			return 10*(s[i+1]-'0')+(s[i+2]-'0');
		}
		else{
			return s[i+1]-'0';
		}
	}
}

int src1(char *s){
	if((code(s)>=20 && code(s)<=29) || code(s)==31) {
		return 0; 
	}
	else if (code(s)>=11 && code(s)<=13){
		int i=strlen(s)-1; 
		while(!isdigit(s[i]) && i>0){
			i--;
		}
		if (isdigit(s[i-1])){
			return 10*(s[i-1]-'0')+(s[i]-'0');
		}
		else{
			return s[i]-'0';
		}
	}
		
	else{
		int i=0, compt=0;
		while((s[i]!='\0' && ( s[i]!='R' || !isdigit(s[i+1])) ) || compt<2){
			i++;
			if(s[i]=='R' && isdigit(s[i+1])){
				compt++;
			}
		}
		if(s[i]=='\0' || !isdigit(s[i+1]) ){
			return 99;
		}
		if (isdigit(s[i+2])){
			return 10*(s[i+1]-'0')+(s[i+2]-'0');
		}
		else{
			return s[i+1]-'0';
		}
	}
}
		
Liste* TrouverEtiquette(FILE* f){
	char* s;
	int i=0,reg=0;
	Etiquette* e=malloc(sizeof(Etiquette));
	e->registre=0;
	e->etiquette='\0'; 
	e->suivant=NULL; 
	Liste* l=malloc(sizeof(Liste));
	l->tete=e; 
	while(fgets(s,TMAX,f)!=NULL){
		while(s[i]!=':' && s[i]!='\0'){
			i++; 
		}
		if (s[i]==':'){
			e->registre=reg;
			int j,k=0; 
			for(j=0; j<i; j++){
				if (s[j]!=' '){
					e->etiquette=e->etiquette+s[j]; 
				}
			}
			e=e->suivant;
		}		
		reg=reg+4;
		
	}
	return l;
}
		



/*

int main(int argc, char *argv[]){
	char* s;
	if(argc<1){
		return 0;
	}
	FILE *f=fopen(argv[1], "r");
	if(f==NULL){
		printf("Fichier inexistant\n");
	}
	int i=0,registre=0;
	fgets(s,TMAX,f);
	Etiquette* e=malloc(sizeof(Etiquette))
	while(s!=NULL){
		while(s[i]!=':' && s[i]!='\0'){
			i++; 
		}
		if (s[i]==':'){
			e->registre=registre;
			int j,k=0; 
			for(j=0; j<i; j++){
				if (s[j]!=' '){
					e->etiquette=e->etiquette+'s[j]'; 
				}
			}
		}		
		registre=registre+4;
		
	
*/

void afficher(Liste* l){
	Etiquette* tmp=l->tete;
	while (tmp!=NULL){
		printf("%d, ",tmp->etiquette);
		tmp=tmp->suivant; 
	}
}

int main(int argc, char *argv[]){
	char* s;
	Liste* l;
	if(argc<1){
		return 0;
	}
	FILE *f=fopen(argv[1], "r");
	if(f==NULL){
		printf("Fichier inexistant\n");
	}
	
	TrouverEtiquette(f); 
	afficher(l); 
	/*char *s="ici: STB (R13)3 R15";
	printf("%s\n", s);
	printf("%d\n", code(s));
	printf("%d\n", destination(s));
	printf("%d\n", src1(s));
	return 0;*/

}
