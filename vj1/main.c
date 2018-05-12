#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char ime[20];
	char prez[20];
	int bod;
}_student;

int Brojanje(char*);
void Citanje(char*, _student*, int);
void Ispisivanje(_student*, int);

int main() 
{
	_student* studenti = NULL; 
	int br=0;
	char filename[40] = {"studenti.txt"};

	br = Brojanje(filename);
	
	studenti = (_student *)malloc(br*sizeof(_student));
	
	Citanje(filename, studenti, br);
	
	Ispisivanje(studenti, br);
	
	return 0;
}

int Brojanje(char* name)
{
	int br=0, i=0;
	FILE* f = NULL;
	
	f = fopen(name, "r");
	
	if(f == NULL)
		printf("GRESKA!\n"); 
		
	while(!feof(f))
		if(fgetc(f) == '\n') 
			br++;
	rewind(f);
	fclose(f);
return br;
}

void Citanje(char* name, _student* s, int br) 
{
 	int i=0, max=0; 
	FILE* f = NULL; 
	f = fopen(name, "r");
	
	if(f == NULL)
		printf("GRESKA!\n"); 
		
	for(i;i<br;i++){
		fscanf(f, "%s %s %d", s[i].ime, s[i].prez, &s[i].bod);
	}
	fclose(f);	
}

void Ispisivanje(_student* s, int br)
{
	int i=0,max=0;
	
	for(i=0;i<br;i++){
		if(s[i].bod > max )
			max = s[i].bod;
	}
	for(i=0;i<br;i++){
		printf("%s\t %s\t %d\t %.2f \n", s[i].ime,s[i].prez,s[i].bod,(float)s[i].bod/max*100);
	}	
}

