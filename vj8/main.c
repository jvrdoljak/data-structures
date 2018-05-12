#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node* Pos;

typedef struct _Node{
	char Name[1024];
	Pos Next;
	Pos Child;
}_NODE;

typedef struct _stackNode{
	Pos data;
	struct _stackNode* Next;
}_STACKNODE;

Pos CreateNode(int);
int Dir(Pos); //naredba dir
int Md(Pos); //naredba md
int InsertNodeData(Pos);
Pos Cd(Pos, struct _stackNode*); //naredba cd
int PushStog(struct _stackNode*, Pos);
Pos CdBack(struct _stackNode*); //naredba "cd..", prima stack->Next 
int PrikaziPutanju(struct _stackNode*); //prikaziva path direktorija, prima stack

int main(int argc, char *argv[]) {
	Pos root = NULL;
	Pos curr = NULL;
	struct _stackNode* stack = NULL;
	char* izbor = NULL;;
	
	root = CreateNode(1);
	if(NULL == root){
		printf("main(): greska pri alokaciji root-a\n");
	}
	curr = CreateNode(1);
	if(NULL == curr){
		printf("main(): greska pri alokacijij curr-a\n");
	}
	izbor = (char*)malloc(20*sizeof(char));
	if(NULL == izbor){
		printf("main(): greska pri alokaciji izbor-a\n");
	}

	stack = (struct _stackNode*)malloc(sizeof(_STACKNODE));
	if(NULL == stack){
		printf("main(): greska pri alokaciji stack-a\n");
	}
	stack->Next = NULL;
	
	memset(root->Name, '\0', 1024);
	root->Name[0] = 'C';
	root->Name[1] = ':';
	
	curr = root;
	PushStog(stack, root);
	
	while(*izbor != 'q' && *izbor != 'Q'){
		PrikaziPutanju(stack);
		scanf(" %s",izbor);
		if(!strcmp(izbor, "dir")){
			Dir(curr);
		}
		else if(!strcmp(izbor, "md")){
			Md(curr);	
		}
		else if(!strcmp(izbor, "cd")){
			curr = Cd(curr,stack);
		}
		else if(!strcmp(izbor, "cd..")){
			curr = CdBack(stack->Next);	
		}
		else if(*izbor == 'q' || *izbor == 'Q'){
			printf("Izasli ste iz programa\n");
		}
		else
			printf("\n\nNepostojeci odabir.\n\n");
	}

	return 0;
}

Pos CreateNode(int n){
	Pos q = NULL;
	q = (Pos)malloc(n*sizeof(_NODE));
	q->Next = NULL;
	q->Child = NULL;
	return q;
}

int Dir(Pos p)
{
	int nDirs = 0;
	if(NULL == p) return -1;
//	printf("\nDirectory of %s", p->Name);
	p = p->Child;
	if(NULL == p){
		printf("\n\nDirektorij je prazan.\n");
	}
	while(p != NULL)
	{
		printf("\n\t%s", p->Name);
		p = p->Next; 
		nDirs++;
	}
	printf("\n\t%d Dirs\n", nDirs);
	
	return 0;
}

int Md(Pos p)
{
	Pos q = NULL; 
	
	if(NULL == p) 
		return -1;
	q = CreateNode(1);
	if(NULL == q) return -2;
	
	InsertNodeData(q);
	
	if(NULL == p->Child){
		p->Child = q;
		return 0;
	}
	p = p->Child;
	while(p->Next != NULL){
		p = p->Next;
	}
	q->Next = p->Next;
	p->Next = q;
	 
	return 0;
}

int InsertNodeData(Pos p)
{
	if (NULL == p) return -1;
	printf("\t");
	scanf(" %s", p->Name);
	
	return 0;
}

Pos Cd(Pos p, struct _stackNode* stack)
{
	Pos temp = p;
	char* dirname = NULL; //ime direktorija kojem treba pristupiti
	
	if (NULL == temp){
		printf("cd(): greska pri primanju trenutne pozicije\n");
		return p;
	}
	
	dirname = (char *)malloc(1025 * sizeof(char));
	if(dirname == NULL){
		printf("cd(): greska pri alokaciji dirname.\n");
		return p;
	}
	printf("\t");
	scanf(" %s", dirname);
	
	temp = temp->Child;
	while(temp != NULL && strcmp(dirname, temp->Name)){
		temp = temp->Next;
	}
	if(NULL == temp){
		printf("Nepostojeci direktorij\n");
		return p;
	}
	else{
		PushStog(stack, temp);
		return temp;
	}
}

int PushStog(struct _stackNode* stack, Pos p)
{
	struct _stackNode* q = NULL;
	q = (struct _stackNode *)malloc(1*sizeof(_STACKNODE));
	if(NULL == q){
		printf("PushStog(): greska pri alokaciji q\n");
		return -1;
	}
	q->Next = NULL;
	
	q->data = p;
	while(stack->Next != NULL)
		stack = stack->Next;
		
	q->Next = stack->Next;
	stack->Next = q;
return 0;
}

Pos CdBack(struct _stackNode* stack)
{
	struct _stackNode* q = NULL;
	struct _stackNode* temp = NULL;
	
	q = (struct _stackNode *)malloc(sizeof(_STACKNODE));
	if(NULL == q){
		printf("PushStog(): greska pri alokaciji q\n");
		return stack->data;
	}
	q->Next = NULL;
	
	temp = (struct _stackNode *)malloc(sizeof(_STACKNODE));
	if(NULL == temp){
		printf("PushStog(): greska pri alokaciji temp-a\n");
		return stack->data;
	}
	temp = stack;
	
	if(stack->Next == NULL){
		//printf("Dosli ste do root file-a.\n");
		return stack->data;
	}
	while(stack->Next->Next != NULL)
		stack = stack->Next;
		
	q = stack->Next;
	stack->Next = q->Next;
	free(q);
	
	stack = temp;
	if(stack->Next == NULL){
		//printf("Dosli ste do root file-a.\n");
		return stack->data;
	}
	while(stack->Next->Next != NULL)
		stack = stack->Next;
	
	q = stack->Next;
	
	return q->data;;
}


int PrikaziPutanju(struct _stackNode* stack)
{
	struct _stackNode* q = stack;
	
	q = q->Next;
	printf("\n");
	
	while(q != NULL){
		printf("%s>", q->data->Name);	
		q = q->Next;
	}
return 0;
}


