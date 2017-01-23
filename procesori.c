#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char proizvodjac[31];
	char oznaka[21];
	unsigned brjez;
	float brzina;
	}procesor;
typedef struct cvor_st{
	procesor inf;
	struct cvor_st *levi;
	struct cvor_st *desni;
	}BCVOR;
FILE *safe_open(char *fajl,char *mod);
void ucitaj(FILE *f,BCVOR **p);
void dodaj(BCVOR **p,procesor pr);
void print(BCVOR *p,FILE *f);
void print1(BCVOR *p,FILE *f,char *x);
float prosek(BCVOR *p,char *x);
void print11(BCVOR *p,FILE *f,char x[]);
float prosek1(BCVOR *p,char *x);

int main(int argc,char* argv[]){
		BCVOR *p=NULL;	
		if(argc!=4){
			printf("Program je nepravilno pozvan\n");
			exit(EXIT_FAILURE);
		}
		FILE *ulaz=safe_open(argv[1],"r");
		ucitaj(ulaz,&p);

		char out[56];
		strcpy(out,"procesori_sortirano.txt");
		FILE *izlaz=safe_open(out,"w");
		print(p,izlaz);

		char out1[56];
		char x[56];
		strcpy(x,argv[2]);
		strcpy(out1,argv[2]);
		strcat(out1,"_procesori.txt");
		FILE *izlaz1=safe_open(out1,"w");
		print1(p,izlaz1,x);
		print11(p,izlaz1,x);
		
	
		fclose(ulaz);
		fclose(izlaz);
		fclose(izlaz1);
		return 0;
}
FILE *safe_open(char *fajl,char *mod){
	FILE *f=fopen(fajl,mod);
	if(f==NULL){
		printf("Nije uspelo otvaranje fajla\n");
		exit(EXIT_FAILURE);
	}
	return f;
}
void ucitaj(FILE *f,BCVOR **p){
	procesor pr;
	while(fscanf(f,"%s %s %u %f",pr.proizvodjac,pr.oznaka,&pr.brjez,&pr.brzina)!=EOF)
		dodaj(p,pr);
}
void dodaj(BCVOR **p,procesor pr){
	if(*p==NULL){
	*p=(BCVOR *)malloc(sizeof(BCVOR));
	(*p)->inf=pr;
	}else{
		if((*p)->inf.brjez>pr.brjez || ((*p)->inf.brjez==pr.brjez && (*p)->inf.brzina>pr.brzina))
			dodaj(&(*p)->levi,pr);
		else
			dodaj(&(*p)->desni,pr);
		}
}
void print(BCVOR *p,FILE *f){
	if(p!=NULL){
		print(p->desni,f);
		fprintf(f,"%s %s %u %.2f GHz\n",p->inf.proizvodjac,p->inf.oznaka,p->inf.brjez,p->inf.brzina);
		print(p->levi,f);
	}
}
void print1(BCVOR *p,FILE *f,char x[]){
	if(p!=NULL){
		if(strcmp(p->inf.proizvodjac,x)==0){
		fprintf(f,"%s %s %u %.2f GHz\n",p->inf.proizvodjac,p->inf.oznaka,p->inf.brjez,p->inf.brzina);
		}
		print1(p->desni,f,x);
		print1(p->levi,f,x);
	}
}
void print11(BCVOR *p,FILE *f,char x[]){
	float m;
	m=prosek(p,x);
	float n;
	n=prosek1(p,x);
	float s;
	s=m/n;
	int i;
	for(i=0;i<30;i++){
		fprintf(f,"-");
	}
	fprintf(f,"\n%.2f\n",s);
}
	
float prosek(BCVOR *p,char *x){
	float m;
	float *d;
	d=&m;
	if(p==NULL)
	return 0;
	if(p!=NULL){
		*d=p->inf.brzina;
		if(strcmp(p->inf.proizvodjac,x)!=0)
		*d=0;
		
	}
	return m+prosek(p->levi,x)+prosek(p->desni,x);
}
float prosek1(BCVOR *p,char *x){
	int m;
	int *d;
	d=&m;
	if(p==NULL)
	return 0;
	if(p!=NULL){
		*d=1;
		if(strcmp(p->inf.proizvodjac,x)!=0)
		*d=0;
		
	}
	return m+prosek1(p->levi,x)+prosek1(p->desni,x);
}






