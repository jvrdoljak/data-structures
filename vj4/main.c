#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
struct _Polynomial;
typedef struct _Polynomial* Pos;
typedef struct _Polynomial
{
	int Coeff;
	int Exp;
	Pos Next;
}_POLY;

int ReadFromFile(Pos); //prima head
int PrintPol(Pos); //prima head-next
Pos CreateNode(int); //prima broj za alociranje
int Delete(Pos, int); //prima head
int Suma(Pos,Pos,Pos); //prima head sume, head->Next prvog pol. i head->Next drugog pol.
int Produkt(Pos,Pos,Pos); //prima head produkta, head->Next prvog pol. i head->Next drugog pol.
int main(int argc, char *argv[]) {
	Pos headS = NULL; 
	Pos head2 = NULL;
	Pos head1 = NULL;
	Pos headP = NULL;
	char izbor;
	//alokacija heada za produkt
	headP = CreateNode(1);
	if(headP == NULL){
		printf("Dogodila se greska pri alokaciji headP-a!\n");
		return -1;
	}
	headP->Next = NULL;
	//alokacija heada za sumu
	headS = CreateNode(1);
	if(headS == NULL){
		printf("Dogodila se greska pri alokaciji headS-a!\n");
		return -1;
	}
	headS->Next = NULL;
	//alokacija heada 2. polinoma
	head2 = CreateNode(1);
	if(head2 == NULL){
		printf("Dogodila se greska pri alokaciji head2!\n");
		return -2;
	}
	head2->Next = NULL;
	//alokacija heada 1. polinoma
	head1 = CreateNode(1);
	if(head1 == NULL){
		printf("Dogodila se greska pri alokaciji head1!\n");
		return -3;
	}
	head1->Next = NULL;

	while(izbor != 'q' && izbor != 'Q'){
		printf("\n");
		printf("IZBORNIK:\n");
		printf("a) Zbroji polinome iz datoteka.\n");
		printf("b) Pomnozi polinome iz datoteka.\n");
		printf("c) Ucitaj i ispisi polinome iz datoteka.\n");
		printf("q) Izlaz.\n");
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("Odaberi: ");
		scanf(" %c", &izbor);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		
		switch(toupper(izbor)){
			case 'A':
				Suma(headS,head1->Next,head2->Next);
				PrintPol(headS->Next);
				break;
			case 'B': 
				Produkt(headP,head1->Next,head2->Next);
				PrintPol(headP->Next);
			case 'C': 
				printf("Polinom 1:\n");
				ReadFromFile(head1);
				PrintPol(head1->Next);
				printf("Polinom 2:\n");
				ReadFromFile(head2);
				PrintPol(head2->Next);
				break;
			case 'Q':
				printf("\nIzasli ste iz izbornika.\n");
				break;
			default: 
				printf("Niste unijeli ispravnu vrijednost za izbor!!!\n");
		}
	}
	
	return 0;
}

Pos CreateNode(int n)
{
	Pos q = NULL;
	q = (Pos)malloc(n*sizeof(_POLY));
	return q;
}

int ReadFromFile(Pos P)
{
	FILE* fp=NULL;
	Pos q=NULL;
	Pos tmp=NULL;	
	char* buffer;
	char* fName;
	
	buffer = (char *)malloc(250*sizeof(char));
	fName = (char *) malloc(40*sizeof(char));
	
	printf("Unesite ime datoteke(sa .txt): ");
	scanf(" %s", fName);
	
	fp = fopen(fName, "r");
	if(fp==NULL){
		printf("Funkcija ReadFromFile(): Datoteka nije otvorena!\n");
		return -1;
	};
	
	while(!feof(fp)){
		memset(buffer,'\0', 250);
		tmp = P;
		fgets(buffer,250,fp);
		
		if(strlen(buffer) > 0){
			q = CreateNode(1);
			if(q==NULL) return -2;  
			sscanf(buffer, "%d %d", &q->Coeff, &q->Exp);
			
			while(tmp->Next!=NULL && tmp->Next->Exp >= q->Exp)
				tmp = tmp->Next;
			if(tmp->Exp == q->Exp){
				tmp->Coeff += q->Coeff;
				/*if(tmp->Coeff)
					Delete(tmp->Coeff)*/
				free(q);
			} 
			else /*if(tmp->Exp > q->Exp)*/{
				q->Next = tmp->Next;
				tmp->Next = q;
			}
			if(tmp->Coeff == 0)
				Delete(P,tmp->Coeff);		
		}
	}
}

int PrintPol(Pos p)
{
	if(p == NULL){
		printf("Funkcija Ispis(): Lista je prazna!\n");
		return -1;
	}
	while(p != NULL)
	{
		printf("%d*X^%d + ", p->Coeff, p->Exp);
		p = p->Next;
	}
	printf("\n");
return 0;
}

int Delete(Pos p, int coeff) 
{
	Pos tmp = p; 
	Pos q = NULL;
	
	if(tmp->Next == NULL){
		printf("Funkcija Delete(): Greska! Prazna lista.\n");
		return -1; 
	}
	q = CreateNode(1);
	if(q == NULL){
		printf("Funkcija Delete(): Greska pri alokaciji varijable q.\n");
		return -2; 
	} 
	while(tmp->Next != NULL && tmp->Next->Coeff != coeff){
		tmp = tmp->Next;
	}
	q = tmp->Next;
	tmp->Next = q->Next;
	free(q);
}

int Suma(Pos z, Pos p, Pos q){
	Pos tmpp = p;
	Pos tmpq = q;
	Pos tmpz = NULL;
	Pos tmp = NULL;
	
	if(tmpp == NULL || tmpq == NULL){
		printf("Funkcija Suma(): Greska! Jedna od listi su prazne!");
		return -1;
	}
	while(tmpp != NULL && tmpq != NULL ){
		tmpz = CreateNode(1);
		if(tmpz == NULL){
			printf("Funkcija Suma(): Greska pri alokaciji pokazivaca\n");
			return -1;
		}
		if(tmpp->Exp < tmpq->Exp){
			tmpz->Exp = tmpq->Exp;
			tmpz->Coeff = tmpq->Coeff;
			tmpq = tmpq->Next;
		}
		else if(tmpp->Exp > tmpq->Exp){
			tmpz->Exp = tmpp->Exp;
			tmpz->Coeff = tmpp->Coeff;
			tmpp = tmpp->Next;
		}
		else{
			tmpz->Exp = tmpp->Exp;
			tmpz->Coeff = tmpp->Coeff + tmpq->Coeff;
			tmpp = tmpp->Next;
			tmpq = tmpq->Next;
		}
		tmpz->Next = z->Next;
		z->Next = tmpz;
		z = z->Next;
	}
	if(tmpp == NULL)
		tmp = tmpq;
 	else 
		tmp = tmpp;
		
	while(tmp != NULL){
		tmpz = CreateNode(1);
		if(tmpz == NULL) return -1;
		
		tmpz->Exp = tmp->Exp;
		tmpz->Coeff = tmp->Coeff;
		
		tmpz->Next = z->Next;
		z->Next = tmpz;
		z = z->Next;
		tmp = tmp->Next;
	}
return 0;
}
int Produkt(Pos P, Pos pol1, Pos pol2)
{
	Pos i = NULL;
	Pos j = NULL;
	Pos q = NULL; //pomocna varijabla za spremanje podataka
	Pos tmp = NULL; //pomocna varijabla za produkt
	i = pol1; 
	if(i == NULL){
		printf("Funkcija Produkt(): Greska, poslana je prazna lista\n");
		return -1;
	}
	while(i != NULL){
		tmp = P;
		j = pol2; 
		if(j == NULL){
		printf("Funkcija Produkt(): Greska, poslana je prazna lista\n");
		return -1;
		}
		while(j != NULL){
			q = CreateNode(1); 
			if(q == NULL){
				printf("Funkcija Produkt(): Greska pri alokaciji pomocne varijable q\n"); 
				return -1; 
			}
			q->Exp = j->Exp + i->Exp;
			q->Coeff = j->Coeff * i->Coeff;
			while(tmp->Next != NULL && q->Exp <= tmp->Next->Exp)
				tmp = tmp->Next;
				
			if(tmp->Next != NULL && tmp->Exp == q->Exp){
				tmp->Coeff += q->Coeff;
				free(q);			
			}
			else{
				q->Next = tmp->Next;
				tmp->Next = q;
				free(q);
			}
			if(tmp->Coeff == 0)
				Delete(P,tmp->Coeff);
				
			j = j->Next;
		}
	i = i->Next;
	}
return 0;
}
