#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define MAX 100

int *c;
char *b;

void LCS_Length(const char *X,const char *Y)
{
	int m,n,i,j;
	m=strlen(X);
	n=strlen(Y);
	// c = (int *)malloc(sizeof(int)*((m+1) * (n+1)));
	// b = (char *)malloc(sizeof(char)*((m+1) * (n+1)));
	for(i=0;i<=m;i++)
		c[i*MAX+0] = 0;
	for(j=1;j<=n;j++)
		c[0*MAX+j] = 0;

	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(X[i-1]==Y[j-1])
			{
				c[i*MAX+j]=c[(i-1)*MAX+j-1]+1;
				b[i*MAX+j]='D';
			}
			else 
			{
				if(c[(i-1)*MAX+j]>=c[i*MAX+j-1])
				{
					c[i*MAX+j]=c[(i-1)*MAX+j];
					b[i*MAX+j]='U';
				}
				else
				{
					c[i*MAX+j]=c[i*MAX+j-1];
					b[i*MAX+j]='L';
				}
			}
		}
	}
}


void find_LCS(const char *X,int m,int n)
{
	if(m ==0 || n ==0)
		return;
	if(b[m*MAX+n]=='D')
	{
		find_LCS(X,m-1,n-1);
		printf("%c",X[m-1]);
		//printf("%d\n",m-1);
	}
	if(b[m*MAX+n]=='U')
		find_LCS(X,m-1,n);
	if(b[m*MAX+n]=='L') 
		find_LCS(X,m,n-1);
}
int main(int argc, char const *argv[])
{
	const char *X,*Y;
	int m,n;
	//X = (char *)malloc(sizeof(char)*MAX);
	//Y = (char *)malloc(sizeof(char)*MAX);
	c = (int *)malloc(sizeof(int)*(MAX * MAX));
	b = (char *)malloc(sizeof(char)*(MAX * MAX));

	X=argv[1];
	Y=argv[2];
	m=strlen(X);
	n=strlen(Y);
	if(m>= 100 || n>= 100)
	{
		printf("length of string out of MAX 100,terminated\n");
		return 0;
	}
	printf("X:%s\n",X);
	printf("Y:%s\n",Y);
	LCS_Length(X,Y);
	printf("LCS:\n");
	find_LCS(X,m,n);

	printf("\n");

	free(c);
	free(b);
	//free(X);
	//free(Y);

	return 0;
}