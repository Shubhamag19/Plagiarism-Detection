#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define d 256

long long int T,P;
long long int spaceCount=0;
int RabinKarp(char* pattern, char*text, int q)
{
	long long int i,j;
	long long int hashP = 0;
	long long int hashT = 0;
	long long int h=1;

	for(i=0; i<P-1; i++)
	{
		h = (h * d) % q;
	}

	for(i=0; i<P; i++)
	{
		hashP = (d * hashP + *(pattern+i)) % q;
		hashT = (d * hashT + *(text + i)) % q;

	}

	for(i=0; i <= T-P; i++)
	{
		if(hashP == hashT)
		{
			for(j=0; j < P; j++)
			{
				if(*(text+i+j) != *(pattern+j))
				{
					break;
				}
			}

			if(j == P)
			{
				return 1;
			}
		}

		if(i < T-P)
		{
			hashT = (d*(hashT - (*(text+i))*h) + *(text+i+P))%q;
			if(hashT < 0)
			{
				hashT = (hashT + q);
			}
		}
	}
	return 0;
}

