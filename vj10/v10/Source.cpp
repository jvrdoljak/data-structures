#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ExpressionTree* Tree;
typedef struct ExpressionTree {
	char operacija; 
	char op[20];
	Tree L;
	Tree R;
}_TREE;

typedef struct _Stack* Stack;
typedef struct _Stack{
	Tree dat;
	Stack Next;
}_STACK;

Stack CreateStack();
Tree CreateTree();
Tree ReadFromFile(Tree, Stack);
Tree PopStack(Stack);
int PushStack(Tree, Stack);
Tree InorderPrint(Tree);


int main(int argc, char** argv)
{
	Tree root = NULL;
	Stack S = NULL;

	S = CreateStack();
	if (S == NULL) {
		printf("Main(): Greska pri alokaciji S.\n");
		return -1;
	}
	root = ReadFromFile(root, S);
	InorderPrint(root);


	return 0;
}

Stack CreateStack()
{
	Stack q = NULL;

	q = (Stack)malloc(sizeof(_STACK));
	if (NULL == q) {
		printf("CreateStack(): Greska pri alokaciji q.\n");
		return NULL;
	}
	q->dat = CreateTree();
	if (q->dat == NULL) {
		printf("CreateStack(): Greska pri alokaciji q->dat.\n");
		return NULL;
	}
	q->Next = NULL;
	return q;
}

Tree CreateTree()
{
	Tree q = NULL;

	q = (Tree)malloc(sizeof(_TREE));
	if (NULL == q) {
		printf("CreateTree(): Greska pri alokaciji q.\n");
		return NULL;
	}
	
	q->operacija = '\0';
	q->L = NULL;
	q->R = NULL;
}

Tree ReadFromFile(Tree T, Stack S)
{
	Tree q = NULL;
	char fname[30] = "postfix.txt";
	char buffer[1024] = "\0";
	FILE* fp = NULL;

	printf("Naziv datoteke? ");
	printf(" %s\n", fname);

	fp = fopen(fname, "r");
	if (NULL == fp) {
		printf("RFF(): Greska pri otvaranju datoteke.\n");
		return T;
	}

	while (!feof(fp)) {
		memset(buffer, '\0', 1024);
		fscanf(fp, " %s", buffer);
		if (strlen(buffer) > 0) {
			if (isdigit(buffer[0])) {
				q = CreateTree();
				if (q == NULL) {
					printf("RFF(): Greska pri alokaciji q.\n");
					return NULL;
				}
				q->operacija = '\0';
				strcpy(q->op, buffer);
				PushStack(q, S);
				q = NULL;
			}
			else {
				q = CreateTree();
				if (q == NULL) {
					printf("RFF(): Greska pri alokaciji q.\n");
					return NULL;
				}
				strcpy(q->op, "\0");
				q->operacija = buffer[0];
				q->R = PopStack(S);
				q->L = PopStack(S);
				PushStack(q, S);
			}
		}
	}
	T->R = PopStack(S);
	T->L = PopStack(S);
	fclose(fp);
	fp = NULL;
	return T;
}

int PushStack(Tree T, Stack S) 
{
	Stack temp = NULL;
	if (S == NULL) {
		printf("PushStack(): Stack nije primljen.\n");
		return -1;
	}
	if (T == NULL) {
		printf("PushStack(): T nije primljen.\n");
		return -1;
	}

	temp = CreateStack();
	if (temp == NULL) {
		printf("PushStack(): Greska pri alokaciji temp.\n");
		return -2;
	}
	temp->dat = T;
	temp->Next = S->Next;
	S->Next = temp;
	temp = NULL;

	return 0;
}

Tree PopStack(Stack S) 
{
	Tree q = NULL;
	Stack temp = NULL;

	if (S == NULL) {
		printf("PopStack(): Greska stog nije primljen.\n");
		return NULL;
	}
	if (S->Next == NULL) {
		printf("PopStack(): Greska prazan stog.\n");
		return NULL;
	}
	q = S->Next->dat;
	temp = S->Next;
	S->Next = temp->Next;
	free(temp);
	temp = NULL;

	return q;
}

Tree InorderPrint(Tree T) {
	if (T != NULL) {
		InorderPrint(T->L);
		printf("%s %s", T->op, T->operacija);
		InorderPrint(T->R);
	}
	return T;
}
