#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int *D,*P;
int n;
void floyd(int* A)
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            D[i*n+j] = A[i*n+j];
        }
    }
    free(A);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            P[i*n+j] = 0;
        }
    }
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(D[i*n+j]>D[i*n+k]+D[k*n+j])
                {
                    D[i*n+j]=D[i*n+k]+D[k*n+j];
                    P[i*n+j]=k;
                }
            }
        }
    }
    printf("======matrix D:======\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",D[i*n+j]);
        }
        printf("\n");
    }
    printf("======matrix P:======\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(P[i*n+j]!=0)
                printf("%d ",P[i*n+j]+1);
            else
                printf("%d ",P[i*n+j]);
        }
        printf("\n");
    }
}

void path(int q, int r)
{
    if(P[q*n+r]!=0)
    {
        path(q,P[q*n+r]);
        printf("v%d->",P[q*n+r]+1);
        path(P[q*n+r],r);
    }
}

int main(int argc, char const *argv[])
{
    int i,j;
    int *A;
    srand(time(NULL));
    n = (rand()%6)+5;//rang between 5-10
    //n=5;
    printf("start :n vertices rang between 5 to 10,n=%d \n",n);
    A = (int *)malloc(sizeof(int)*(n * n));//adjacency matrix A
    D = (int *)malloc(sizeof(int)*(n * n));
    P = (int *)malloc(sizeof(int)*(n * n));
    for(i=0;i<n;i++)
        for(j=0;j<=i;j++)
        {
            if(i==j)
            {
                A[i*n+j]=0;
            }
            else
            {
                A[i*n+j]=rand()%10+1;
                A[j*n+i]=A[i*n+j];//make A[i,j] = A[j,i]
            }
        }
    printf("======matrix A:======\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",A[i*n+j]);
        }
        printf("\n");
    }
    floyd(A);
    printf("=========All shortest paths==========\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j)
            {
                printf("v%d--v%d\n",i+1,j+1);
                printf("v%d->",i+1);
                path(i,j);
                printf("v%d---",j+1);
                printf("length %d\n\n",D[i*n+j]);   
            }
        }
        printf("================\n");
    }
    free(D);
    free(P);
    return 0;
}