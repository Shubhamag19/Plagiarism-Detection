#include<stdio.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdlib.h>
#include "kmp.h"
#include "rabin_karp.h"
#include "winnowing.h"
int len;
int match=0;

void printString(char* string, int size)
{
	for(int i = 0; i < size; ++i)
    {
        printf("%c", *(string + i));
    }
    printf("\n");
}
float calc(int match, int buffersize, float totalsize)
{
  float per = ((match*buffersize)/totalsize)*100;
  return per;

}
float calcsize(char *pat)
{
  int i = 0;
  float patsize = 0.0;
  while(pat[i]!='\0')
  {
    if(pat[i]==' ')
    {
      patsize++;
    }
    i++;
  }
  patsize+=1;
  return patsize;
}
long long int length(FILE* file)
{
	char ch = fgetc ( file );
	long long int len = 0;
	while ( ch!=EOF )
	{
		++len;
		ch = fgetc ( file );
		
	}
	return len;
}
void storeInArray(char* string, char *filename){
	long long int	i=0;
	char ch;
	FILE* file;
	file = fopen(filename, "r");
	ch = fgetc ( file );
	while ( ch != EOF )
	{
		if(ch>=65 && ch<=90)
		{
			ch+=32;
		}
		else if(ch>32 && ch<48 || ch>57 && ch<65 || ch>90 && ch<97 || ch>122 && ch<127)
		{
			ch = ' ';
		}
		if(ch==' ')
		{
		    ++spaceCount;
		}
		*(string+i) = ch;
		ch = fgetc ( file );
		//printf("%c", *(string+i));
		++i;
	}
	fclose(file);
}

int main(int argc, char** argv)
{
    FILE *pattern, *text;
    char *pat, *txt,*buffer;

	if(argc == 3)
	{
		pattern = fopen(argv[1], "r");
		text = fopen(argv[2], "r");
	}
	else
	{
		printf("Number of parameter exceeded\n");
	}
	
	if(pattern == NULL || text == NULL)
	{
		printf("File does not exists\n");
		return 0;
	}
	
	P = length(pattern)-1;
	T = length(text)-1;
	pat = (char*) calloc(P, sizeof(char));
	txt = (char*) calloc(T, sizeof(char));
	buffer = (char*) calloc(P, sizeof(char));
	
	storeInArray(pat, argv[1]);
	storeInArray(txt, argv[2]);
        
    len = P;
    float totalsize = calcsize(pat);
    int count=0;
    int i=0, k=0, s=0;
    int point = 0;
    int tobeadded;
    int check;
   // buffer = (char*)calloc(strlen(pat), sizeof(char));
    printf("Enter the size of the buffer window: ");
    scanf("%d",&s);
    printf(" \n");
    
    //Rabin Karp Algorithm Driver Code
    while(point<len)
    {
        count = 0;
        while(count<s)
        {
            buffer[k] = *(pat+i);
            if(*(pat+i) ==' ')
            {
                count++;
                if(count==s)
                {
                    buffer[k] = '\0';
	                P = strlen(buffer);
                    tobeadded = k;
		            match += RabinKarp(buffer, txt, 101);
                    k=-1;
                }
            }
            k++;
            i++;
        }
        point+= tobeadded;
    }
    calc(match, s, totalsize);
    printf("Percentage from Rabin Karp algorithm=%f%\n",calc(match, s, totalsize));
    free(buffer);
    
    //Knuth Morris Pratt Algorithm Driver Code
    buffer = (char*)calloc(strlen(pat), sizeof(char));
    i=k=0;
    point = 0;
    match = 0;
    while(point<len)
    {
        count = 0;
        while(count<s)
        {
            buffer[k] = *(pat+i);
            if(*(pat+i) ==' ')
            {
                count++;
                if(count==s)
                {
                    buffer[k] = '\0';
	            P = strlen(buffer);
                    tobeadded = k;
		    match += KMPSearch(buffer, txt);
                    k=-1;
                }
            }
            k++;
            i++;
        }
        point+= tobeadded;
    }
    printf("Percentage from KMP algorithm=%f%\n",calc(match, s, totalsize));
   
    //Winnowing Driver Code
    count=0;
    preprocess(pat, count,s);
    count++;
    preprocess(txt, count,s);
   
    free(pat);
    free(txt);
    fclose(pattern);
    fclose(text);
    return  0;
}
