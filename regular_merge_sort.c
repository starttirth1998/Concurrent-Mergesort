#include<stdio.h>
#include<stdlib.h>

int *L;
int *R;

void merge(int arr[],int l,int mid,int r)
{
	int i,j,k;
	int n1=mid-l+1;
	int n2=r-mid;
	for(i=0;i<n1;i++)
	{
		L[i] = arr[l+i];
	}
	for(i=0;i<n2;i++)
	{
		R[i] = arr[mid+i+1];
	}
	i=0;
	j=0;
	k=l;
	while(i<n1 && j<n2)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			k++;
			i++;
		}
		else if(R[j] < L[i])
		{
			arr[k] = R[j];
			k++;
			j++;
		}
	}
	while(i<n1)
	{
		arr[k] = L[i];
		k++;
		i++;
	}
	while(j<n2)
	{
		arr[k] = R[j];
		k++;
		j++;
	}
return;
}
void sort(int arr[],int l,int r)
{
	int mid = l + (r-l)/2;
	if(l<r)
	{
		sort(arr,l,mid);
		sort(arr,mid+1,r);
		merge(arr,l,mid,r);
	}
return;
}
int main()
{
	int n,i;
	int *a;
	scanf("%d",&n);
	a = (int *)malloc((n+5)*sizeof(int));
	L = (int *)malloc((n+5)*sizeof(int));
	R = (int *)malloc((n+5)*sizeof(int));
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a,0,n-1);
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
return 0;
}
