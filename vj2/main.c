#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student* Position;

typedef struct student {
	char ime[20];
	char prezime[20];
	int god; 

	Position Next;
}_Student;

Position CreateNode(int);
int Insert(Position );
int InsertAfter(char*,Position);
int InsertPrev (char*, Position);
int PrintAll(Position);
Position FindLast(Position );
int InsertLast(Position );
Position Find(char*, Position);
Position FindPrev(char*, Position);
int Brisi(Position);
int Sort(Position);
int PrintInFile(Position);
int ReadFromFile(Position);
int main() 
{
	char izbor;
	char prezime[30];
	Position head = NULL;
	head = CreateNode(1);
	head->Next = NULL;
	if(head == NULL) return -1;
	
	while(izbor != 'q' && izbor != 'Q'){
		printf("\n++++++++++++++++++++++++++++++++++++\n");
		printf("IZBORNIK:\n");
		printf("a) dodaj element u listu,\n");
		printf("b) ispisi listu,\n");
		printf("c) dodaj element na kraj liste,\n");
		printf("d) pronadji element u listi(prezime),\n");
		printf("e) pobrisi element iz liste,\n");
		printf("f) dodaj element iza odredjenog elementa,\n");
		printf("g) dodaj element ispred odredjenog elementa,\n");
		printf("h) sortiraj listu(po prezimenu),\n");
		printf("i) ispis listu u datoteku,\n");
		printf("j) citaj listu iz datoteke,\n");
		printf("q) izlaz iz izbornika,\n");
		printf("++++++++++++++++++++++++++++++++++++\n");
		printf("Biraj: ");
		scanf(" %c", &izbor);
		printf("++++++++++++++++++++++++++++++++++++\n\n");
		switch(toupper(izbor)){
		case 'A': 
			Insert(head);
			break;
		case 'B': 
			PrintAll(head->Next);
			break;
		case 'C': 
			InsertLast(head);
			break;
		case 'D': 
			printf("Unesite prezime: ");
			scanf(" %s", prezime);
			Find(prezime,head->Next);
			memset(prezime, '\0', 30);
			break;
		case 'E': 
			Brisi(head);
			break;
		case 'F': 
			printf("Unesite prezime: ");
			scanf(" %s", prezime);
			InsertAfter(prezime,head->Next);
			memset(prezime, '\0', 30);
			break;
		case 'G': 
			printf("Unesite prezime: ");
			scanf(" %s", prezime);
			InsertPrev(prezime,head);
			memset(prezime, '\0', 30);
			break;
		case 'H': 
			Sort(head);
			break;
		case 'I': 
			PrintInFile(head->Next);
			break;
		case 'J': 
			ReadFromFile(head);
			break;	
		case 'Q': 
			break;	 
		default:
			printf("Odabrali ste nepostojecu radnju\n");
			break;
		}
	}

return 0;
}

Position CreateNode(int n)
{
	Position q = NULL; 

	q = (Position)malloc(n * sizeof(_Student));
	if (q == NULL)
		printf("Dogodila se greska pri alokaciji!\n");
	return q;
}
Position FindLast(Position p)
{
	while(p->Next != NULL)
		p = p->Next; 

return p;
}
int Insert(Position p)
{
	Position q = NULL;
	q = CreateNode(1);
	if(NULL == p){
		printf("\nGreska pri umetanju clana liste\n");
		return -1;
	}
	q->Next = p->Next;
	p->Next = q; 

	printf("Ime? ");
	scanf(" %s", q->ime);
	printf("Prezime? ");
	scanf_s(" %s", q->prezime);
	printf("Godina rodjenja? ");
	scanf("%d", &q->god);
	
return 0;
}
int PrintAll(Position p)
{
	if(p == NULL){
		printf("\nGeska pri ispisu svih elemenata!\n");
		return -1;
	}
	while(p != NULL){
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->Next;
	}	
return 0;
}
int InsertLast(Position p)
{
	p = FindLast(p);
	if(p == NULL){
		printf("\nLista je prazna, ne moze se unijeti zadnji element\n!");
		return -1;
	}
	Insert(p);
return 0;
}

Position Find(char el[20], Position p) /*prima head->Next*/
{
	while(p != NULL && strcmp(p->prezime,el))
		p = p->Next;
	if(NULL == p){
		printf("\nNema trazenog elementa!\n");
		return NULL;
	} else
		return p;
}
Position FindPrev(char el[20], Position p) /*prima head*/
{
	Position prev = NULL; 
	while(p->Next != NULL && strcmp(p->prezime,el)){
		prev = p; 
		p = p->Next;
	}
	if(NULL == prev){
		printf("\nNema prethodnog elementa!\n");
		return NULL;
	} else
		return prev;
}
int Brisi(Position p) /*prima head*/
{
	Position prev=NULL,temp = NULL;
	char prezime[20];
	
	printf("Unesite prezime: ");
	scanf(" %s", prezime);
	
	prev = FindPrev(prezime,p);
	if(NULL == prev){
		printf("\nElement za brisanje ne postoji!\n");
		return -1;
	}
	temp = prev->Next; 
	prev->Next = temp->Next;
	free(temp);
	temp = NULL;
return 0;
}
int InsertAfter(char* element,Position p)
{
	Position curr = NULL; 
	curr = Find(element,p);
	if(NULL == curr) return -1;
	
	return Insert(curr);
return 0;
}
int InsertPrev (char* element, Position p) /*prima head*/
{
	Position prev = NULL;
	prev = FindPrev(element, p);
	if(NULL == prev) return -1;
	
	return Insert(prev);
}
int Sort(Position p)
{
	Position prev_j = NULL;
	Position j = NULL;
	Position i = NULL;
	Position end = NULL;
	i = p;
	
	if(NULL == p) return -1;
	
	while(p->Next != end){
		i = p;
		prev_j = i->Next;
		j = prev_j->Next;
		while(j != end){
			if(strcmp(prev_j->prezime,j->prezime) > 0){
				prev_j->Next = j->Next;
				j->Next = prev_j;
				i->Next = j;
			} else{
				i = prev_j;
			}
			prev_j = i->Next;
			j = prev_j->Next;
		}
		end = prev_j; 
	}
return 0;
}
int PrintInFile(Position p) /*prima head->Next*/
{
	FILE* fp = NULL;
	char filename[30];
	
	printf("Naziv datoteke(sa .txt): ");
	scanf(" %s", filename);
	
	fp = fopen(filename, "w+");
	if(NULL == fp){
		printf("GRESKA! Datoteka / %s / nije otvorena.\n", filename);
		return -1;
	} 
	
	while(p != NULL){
		fprintf(fp,"%s %s %d\n", p->ime,p->prezime,p->god);
		p = p->Next;
	}
	fclose(fp);
	return 0;
}
int ReadFromFile(Position p) /*prima head*/
{
	Position q = NULL;
	FILE* fp = NULL;
	char* buffer = NULL;
	char filename[30];
	
	printf("Naziv datoteke(sa .txt): ");
	scanf(" %s", filename);
	
	buffer = (char* )malloc(250*sizeof(char));
	if(buffer == NULL) return -2;
	fp = fopen(filename, "r");
	if(fp == NULL) return -1;
	
	while(!feof(fp))
	{
		memset(buffer, '\0', 250);
		fgets(buffer,250,fp);
		if(strlen(buffer) > 0){
			q = CreateNode(1);
			if(q == NULL) return -3;
			sscanf(buffer,"%s %s %d", q->ime,q->prezime,&q->god);
			q->Next = p->Next;
			p->Next = q;
		}
	}
	fclose(fp);
	free(buffer);
	return 0;
}
