#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Lista* Position;

typedef struct Lista{
	int el;
	Position Next; 
}_LISTA;

//sve funkcije primaju head element 
int PushStog(Position);
int PopStog(Position);
int PushRed(Position);
int PopRed(Position);
Position CreateNode(int);
int GetElement();
int Print(Position); //prima head->Next

int main(int argc, char *argv[]) {
	Position head1 = NULL; 
	Position head2 = NULL;
	char izbor;
	
	head1 = CreateNode(1);
	if(head1 == NULL){
		printf("Main(): Geska pri alociranju head1 elementa!\n");
		return -1;
	}
	head2 = CreateNode(1);
	if(head2 == NULL){
		printf("Main(): Geska pri alociranju head2 elementa!\n");
		return -1;
	}
	
	while(izbor != 'q' && izbor != 'Q'){
		printf("IZBORNIK:\n");
		printf("a) Umetni element na STOG\n");
		printf("b) Skini element sa STOGA\n");
		printf("c) Umetni element na RED\n");
		printf("d) Skini element s REDA\n");
		printf("e) Print STOG\n");
		printf("f) Print RED\n");
		printf("q) IZLAZ\n");
		printf("+++++++++++++++++++++++++++++++++++++++++\n");
		printf("Izbor: ");
		scanf(" %c", &izbor);
		printf("+++++++++++++++++++++++++++++++++++++++++\n");
		
		switch(toupper(izbor)){
			case 'A': 
				PushStog(head1);
			break;
			case 'B':
				PopStog(head1);
			break;
			case 'C': 
				PushRed(head2);
			break;
			case 'D':
				PopRed(head2);
			break;
			case 'E': 
				Print(head1->Next);
			break;
			case 'F':
				Print(head2->Next);
			break;
			case 'Q': 
			break;
			default: 
				printf("Unijeli ste pogresan odabir, pokusajte ponovno\n");
			break;
		}
	}
	
	while(head1->Next != NULL){
		PopStog(head1);
	}
	while(head2->Next != NULL){
		PopRed(head2);
	}
	Print(head1->Next);
	Print(head2->Next);
	
	return 0;
}
Position CreateNode(int n)
{
	Position q = NULL;
	q = (Position)malloc(n*sizeof(_LISTA));
	q->Next = NULL;
	return q;
}
int GetElement(){
	int el = 0;
	
	srand((unsigned) time(NULL));
	el = (int)rand() % (100-10) +10 ;

	if(el < 100 && el > 10)
		return el;
}

int PushStog(Position p){
	Position q; 
	
	if (p == NULL)
		return -1;
	q = CreateNode(1);
	if(q == NULL)
		return -1;
		
	q->el = GetElement();
	
	q->Next = p->Next;
	p->Next = q;
	
	return 0;
}
int PopStog(Position p){
	Position tmp = NULL;
	
	if(p == NULL)
		return -1;
	if(p->Next == NULL){
		printf("PopStog(): Stog je prazan\n");
		return -1; 
	}
	
	tmp = p->Next;
	p->Next = p->Next->Next;
	
	free(tmp);
	tmp = NULL;
	return 0;
}
int PushRed(Position p){
	Position q; 
	static Position last = NULL;
	
	if (p == NULL)
		return -1;
	q = CreateNode(1);
	if(q == NULL)
		return -1;
		
	q->el = GetElement();
	if(last == NULL)
		last = p;
		
	q->Next = last->Next;
	last->Next = q;
	last = q; 
	return 0;
}
int PopRed(Position p){
	Position tmp = NULL;
	
	if(p == NULL)
		return -1;
	if(p->Next == NULL){
		printf("PopRed(): Red je prazan\n");
		return -1; 
	}
	
	tmp = p->Next;
	p->Next = p->Next->Next;
	
	free(tmp);
	tmp = NULL;
	return 0;
}
int Print(Position p){
	Position tempp = p; 
	
	if(tempp == NULL){
		printf("Print(): Lista je prazna\n");
		return -1;
	}	
	
	printf("L: ");
	
	while(tempp != NULL){
		printf(" %d", tempp->el);
		tempp = tempp->Next;
	}
	printf("\n");
return 0;	
}




