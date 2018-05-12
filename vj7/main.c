#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stog* Pos;

typedef struct stog{
	float el;
	Pos Next;
}_STOG;

int PushStog(Pos, float); //prima head i broj koji ce se spremiti na stog 
int PopStog(Pos);  //prima head
int Calculate(float,float,float*,char*);
Pos CreateNode(int); 
int ReadFromFile(Pos, float*); //prima head

int main(int argc, char *argv[]) {
	Pos head = NULL;
	
	head = CreateNode(1);
	if(NULL == head)
		return -1;
	
	
	
	
	return 0;
}


Pos CreateNode(int n)
{
	Pos q = NULL;
	q = (Pos)malloc(n*sizeof(_STOG));
	q->Next = NULL;
	return q;
}

int PushStog(Pos p, float br)
{
	Pos q = NULL;
	
	q = CreateNode(1);
	if(NULL == q){
		return -1;
	}
	q->el = br;
	
	q->Next = p->Next;
	p->Next = q;
	
	q = NULL;
	
	return 0;
}

int PopStog(Pos p)
{
	Pos temp = p->Next;
	float pov = 0.0;
	if(NULL == p){
		return -1;
	}	
	if(NULL == temp){
		return -1;
	}
	pov = temp->el;
	
	p->Next = temp->Next; 
	
	free(temp);
	temp = NULL;
	return pov;
}

int Calculate(float a, float b, float* res, char* operacija)
{	
	if(NULL == res){
		return -1;
	}
	if(NULL == operacija){
		return -1;
	}
	
	switch(*operacija){
		case '+': 
			*res = a+b;	
		break;
		case '-':
			*res = a-b;
		break;
		case '*':
			*res = a*b;
		break;
		case '/':
			if(0 == b){
				return -1;
			}
			*res = a/b;
		break;
		default: 
			printf("Operacija ne postoji\n");
			return -1;
		break;
	}
return 0;
}

int ReadFromFile(Pos p,float* result)
{
	Pos q = NULL;
	Pos temp = p;
	char* buffer = NULL;
	char* fName = NULL;
	FILE* fp = NULL;
	float x = 0.0, y = 0.0, res = 0.0, broj = 0.0;
	
	if(NULL == temp){
		return -1;
	}	
	buffer = (char*)malloc(8*sizeof(char));
	if(NULL == buffer){
		return -1;
	}
	fName = (char *)malloc(25);
	if(NULL == fName){
		return -1;
	}
	
	fp = fopen(fName, "r");
	if(NULL == fp){
		return -1;
	}
	
	while(!feof(fp)){
		memset(buffer, '\0', 8);
		fscanf(fp, " %s", buffer);
		if(isdigit(*buffer)){
			sscanf(buffer, " %d", &broj);
			Push(p, broj);
		}
		else{
			y = Pop(p);
			x = Pop(p);
			if(!Calculate(x,y,&res,buffer))
				Push(p,res);
		}
	}
	*result = p->Next->el;
	
	return 0;
}









