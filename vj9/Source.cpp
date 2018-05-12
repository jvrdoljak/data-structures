#include <stdio.h>
#include <stdlib.h>

struct _Node;
typedef struct _Node *Pos;

struct _Node
{
	int El;
	Pos Right;
	Pos Left;
};

Pos Insert(Pos, int);
void Print(Pos);
Pos FindMin(Pos);
Pos FindMax(Pos);
Pos Delete(Pos, int);
Pos Find(Pos, int);

int main(int argc, char** argv)
{

	Pos root = NULL;
	Pos fnd = NULL;
	char izbor = 0;
	int n = 0;


	while (izbor != 'k' && izbor != 'K')
	{
		printf("\r\n");
		printf("\r\n");
		printf("\r\n\t\t************************");
		printf("\r\n\t\t***     IZBORNIK     ***");
		printf("\r\n");
		printf("\r\n\t\t***   Vjezba br. 9   ***");
		printf("\r\n\t\t************************");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n\t1.\tUnos");
		printf("\r\n\t2.\tIspis");
		printf("\r\n\t3.\tBrisanje");
		printf("\r\n\t4.\tTrazenje");
		printf("\r\n\tIzbor : ");

		scanf_s(" %c", &izbor, 1);

		switch (izbor)
		{
		case '1':
			printf("\r\nUnesite broj koji zelite unijeti : ");
			scanf(" %d", &n);
			root = Insert(root, n);
			break;
		case '2':
			if (root == NULL)
				printf("\r\nStablo je prazno");
			else
				Print(root);
			break;
		case '3':
			printf("\r\nUnesite broj koji zelite izbrisati : ");
			scanf(" %d", &n);
			root = Delete(root, n);
			break;
			break;
		case '4':
			printf("\r\nUnesite broj koji trazite : ");
			scanf(" %d", &n);
			fnd = Find(root, n);
			if (fnd != NULL)
				printf("\r\nTrazeni element %d se nalazi na adresi %x", fnd->El, fnd);
			else
				printf("\r\nTrazeni broj %d nije pronaden.", n);
			break;
		case 'k':
		case 'K':
			break;
		default:
			printf("\r\nPogresan izbor!\r\nPokusajte ponovno.\r\n");
		}
	}
	return 0;
}


Pos Insert(Pos P, int n)
{
	if (P == NULL)
	{
		P = (Pos)malloc(sizeof(struct _Node));
		if (P)
		{
			P->El = n;
			P->Left = NULL;
			P->Right = NULL;
		}
	}
	else if (P->El < n)
		P->Right = Insert(P->Right, n);
	else if (P->El > n)
		P->Left = Insert(P->Left, n);
	else
		printf("\r\nElement vec postoji u stablu.");
	return P;
}

void Print(Pos P) 
{ 
	if (P != NULL)
	{
		Print(P->Left);
		printf(" %d", P->El);
		Print(P->Right);
	}
	return; 
}
Pos FindMin(Pos P) 
{ 
	if (P == NULL)
		return P;
	else if (P->Left == NULL)
		return P;
	else
		return FindMin(P->Left);
}
Pos FindMax(Pos P) 
{ 
	if (NULL == P)
		return P;
	else if (NULL == P->Left)
		return P;
	else
		return FindMax(P->Right);
}
Pos Delete(Pos P, int n) 
{ 
	Pos tmp;
	if (P == NULL)
		return P;
	else if (P->El < n)
		P->Right = Delete(P->Right, n);
	else if (P->El > n)
		P->Left = Delete(P->Left, n);
	else {
		if (P->Right != NULL && P->Left != NULL) {
			tmp = FindMin(P->Right);
			P->El = tmp->El;
			P->Right = Delete(P->Right, tmp->El);
		}
		else {
			tmp = P;
			if (NULL == P->Left)
				P = P->Right;
			else
				P = P->Left;
			free(tmp);
		}
	}
	return P;
}
Pos Find(Pos P, int n) 
{
	if (P == NULL)
		return NULL;
	else
		if (P->El > n)
			return Find(P->Left, n);
		else if (P->El < n)
			return Find(P->Right, n);
		else
			return P;
}

