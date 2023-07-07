#include <stdio.h>
#include <stdlib.h>
// C merge sort code
// new comment 20220518
int merge(int *data1, int s1, int s2, int *data2);
int main()
{
    int i;
    int a[10]={1,3,5,7,9,2,4,6,8,10},b[10];
    merge(a,5,5,b);
    for(i=0;i<10;i++)printf("%d ",b[i]);
    return 0;
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
	return 0;
}
