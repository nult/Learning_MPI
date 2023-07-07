#include <stdio.h>
#include <stdlib.h>
#define N 22
#define NUM 5
int multimerge(int *data,int *ind,int n,int *data1);
int merge(int *data1, int s1, int s2, int *data2);
int main(){
    int a[N]={1,4,7,10,2,5,8,11,12,3,6,9,13,14,15,5,7,20,1,10,17,50};
    int b[NUM]={4,5,6,3,4};
    int c[N],i;
    for(i=0;i<N;i++)printf("%d ",a[i]);
    multimerge(a,b,NUM,c);
    printf("\n");
    for(i=0;i<N;i++)printf("%d ",a[i]);
    return 0;
}

int multimerge(int *data,int *ind,int n,int *data1)
{
    int i;
    if(n==2){
        merge(data,ind[0],ind[1],data1);
        return 0;
    }
    merge(data,ind[0],ind[1],data1);
    ind[0]=ind[0]+ind[1];
    for(i=1;i<n-1;i++){
        ind[i]=ind[i+1];
    }
    printf("\n");
    printf("%d %d %d \n",ind[0],ind[1],n);
    multimerge(data,ind,n-1,data1);
}

int merge(int *data1, int s1, int s2, int *data2)
{
	int i, l, m;
	l = 0;
	m = s1;
	for (i = 0; i<s1 + s2; i++)
	{
		if (l == s1)
			data2[i] = data1[m++];
		else
			if (m == s2 + s1)
				data2[i] = data1[l++];
			else
				if (data1[l]>data1[m])
					data2[i] = data1[m++];
				else
					data2[i] = data1[l++];
	}
	for(i=0;i<s1+s2;i++){
        data1[i]=data2[i];
	}
	return 0;
}
