#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct _Node;
typedef struct _Node* Pos;

typedef struct _Node
{
	int el;
	Pos Next;
}_NODE;

Pos CreateNode(int);
int ReadFromFile(Pos);
int Unija(Pos,Pos,Pos);
int Presjek(Pos,Pos,Pos);
int Print(Pos);

int main(int argc, char *argv[]) {
	Pos head1 = NULL;
	Pos head2 = NULL; 
	Pos headU = NULL;
	Pos headP = NULL; 
	char izbor;
	
	head1 = CreateNode(1);
	if(head1 == NULL) return -1;
	head1->Next = NULL;
	
	head2 = CreateNode(1);
	if(head2 == NULL) return -1;
	head2->Next = NULL;
	
	headU = CreateNode(1);
	if(headU == NULL) return -1;
	headU->Next = NULL;
	
	headP = CreateNode(1);
	if(headP == NULL) return -1;
	headP->Next = NULL;
	
	
	while(izbor != 'q' && izbor != 'Q'){
		printf("IZBORNIK:\n");
		printf("a) Unos i ispis listi iz datoteke;\n");
		printf("b) Unija listi;\n");
		printf("c) Presjek listi;\n");
		printf("q) Izlaz;\n");
		printf("++++++++++++++++++++++++++++++++++++++\n");
		printf("Izbor: ");
		scanf(" %c", &izbor);
		printf("++++++++++++++++++++++++++++++++++++++\n");
		
		switch(toupper(izbor)){
			case 'A':
				ReadFromFile(head1);
				Print(head1->Next);
				ReadFromFile(head2);
				Print(head2->Next);
				break;
			case 'B':
				Unija(headU,head1->Next,head2->Next);
				Print(headU->Next);
				break;
			case 'Q': 
				break;
			default: 
			printf("Unesen je pogresan izbor!\n");
				break;
		}
	}
	
	return 0;
}

Pos CreateNode(int n)
{
	Pos q = NULL; 
	q = (Pos)malloc(n*sizeof(_NODE));
return q; 	
} 

int ReadFromFile(Pos p){
	Pos q = NULL; 
	Pos tmp = NULL; 
	char* buffer = NULL; 
	char* fName = NULL;
	FILE* fp = NULL; 
	
	fName = (char *)malloc(40*sizeof(char));
	if(fName == NULL) return -1;
	buffer = (char *)malloc(250*sizeof(char));
	if(buffer == NULL) return -1;
	
	printf("Unesite ime datoteke(sa .txt): ");
	scanf(" %s", fName);
	
	fp = fopen(fName, "r");
	if(fp == NULL) return -1;
	
	while(!feof(fp)){
		memset(buffer, '\0', 250);
		tmp = p;
		fgets(buffer,250, fp);
		if(strlen(buffer)>0){
			q = CreateNode(1);
			if(q == NULL) return -1; 
			sscanf(buffer, "%d", &q->el);
			
			while(tmp->Next != NULL && tmp->Next->el > q->el)
				tmp = tmp->Next;
			if(tmp->el == q->el) 
				free(q);
			q->Next = tmp->Next;
			tmp->Next = q; 
		} 
	}
return 0;	
}
int Print(Pos p)
{
	Pos tmp = p;
	
	if(tmp == NULL) return -1;
	
	while(tmp != NULL){
		printf("%d ", tmp->el);
		tmp = tmp->Next;
	}
	printf("\n");
return 0;
}
int Unija (Pos U, Pos p1, Pos p2)
{
	Pos tmp1 = p1; 
	Pos tmp2 = p2; 
	Pos tmpU = U; 
	Pos q = NULL;
	Pos tmp = NULL;
	if(tmp1 == NULL || tmp2 == NULL) return -1;
	
	while(tmp1 != NULL && tmp2 != NULL){
			q = CreateNode(1); 
			if(q == NULL) return -1;
		
			if(tmp1->el > tmp2->el){
				q->el = tmp1->el;
				tmp1 = tmp1->Next;
			}else if(tmp1->el < tmp2->el){
				q->el = tmp2->el;
				tmp2 = tmp2->Next;
			}else{
				q->el = tmp1->el;
				tmp2 = tmp2->Next;
				tmp1 = tmp1->Next;
			} 	
		q->Next = tmpU->Next;
		tmpU->Next = q;
	}
	if(tmp1 == NULL) tmp = tmp2;
	else tmp = tmp1;
	
	while(tmp != NULL){
		q = CreateNode(1);
		q->el = tmp->el;
		tmp = tmp->Next;
		
		q->Next = tmpU->Next;
		tmpU->Next = q;
	}
	return 0;
}











