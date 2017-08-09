#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>

int *L;
int *R;
int level;

void sort(int *arr,int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void merge(int *arr,int l,int m,int r)
{
	int i,j,k,n1,n2;
	n1 = m-l+1;
	n2 = r-m;
	for(i=0;i<n1;i++)
	{
		L[i] = arr[l+i];
	}
	for(i=0;i<n2;i++)
	{
		R[i] = arr[m+i+1];
	}
	i=0;j=0;k=l;
	while(i<n1 && j<n2)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
			k++;
		}
		else
		{
			arr[k] = R[j];
			j++;
			k++;
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

void mergesort(int *arr,int l,int r)
{
	if(r-l+1 <= 5)
	{
		sort(arr+l,r-l+1);
		return;
	}
	int m;
	int status;
	pid_t lchild,rchild;
	m = l + (r-l)/2;
	//printf("%d\n\n",m);
	//printf("::%d ::%d\n",l,r);
	if(level >= 10)
	{
		mergesort(arr,l,m);
		mergesort(arr,m+1,r);
		merge(arr,l,m,r);
	}
	else
	{
		level++;
		lchild = fork();
		//printf("%d %d\n",l,r);
		if(lchild < 0)
		{
			perror("fork:left");
			exit(1);
		}
		else if(lchild == 0)
		{
			mergesort(arr,l,m);
			exit(0);
		}
		else
		{
			rchild = fork();
			if(rchild < 0)
			{
				perror("fork:right");
				exit(1);
			}
			else if(rchild == 0)
			{
				mergesort(arr,m+1,r);
				exit(0);
			}
		}
		waitpid(lchild,&status,0);
		waitpid(rchild,&status,0);
		merge(arr,l,m,r);
	}
return;
}

int main()
{
	level = 0;
	int n,i;
	int *shm_array;
	int shm_id;
	key_t key;
	size_t segsize;
	scanf("%d",&n);
	int *a = (int *)malloc((n+5)*sizeof(int));
	L = (int *)malloc((n+5)*sizeof(int));
	R = (int *)malloc((n+5)*sizeof(int));
	for(i=0;i<n;i++)
	{
		//printf("%d\n",i);
		scanf("%d",&a[i]);
	}
	key = IPC_PRIVATE;
	segsize = n*sizeof(int);
	if((shm_id = shmget(key, segsize, IPC_CREAT | 0666)) == -1)
	{
		perror("shmget");
		exit(1);
	}
	if((shm_array = shmat(shm_id, NULL, 0)) == (int *) -1)
	{
		perror("shmat");
		exit(1);
	}
	//printf("Hello\n");
	for(i=0;i<n;i++)
	{
		shm_array[i] = a[i];
	}
	mergesort(shm_array,0,n-1);
	for(i=0;i<n;i++)
	{
		printf("%d ",shm_array[i]);
	}
	if(shmdt(shm_array) == -1)
	{
		perror("shmdt");
		exit(1);
	}
	if(shmctl(shm_id, IPC_RMID, NULL) == -1)
	{
		perror("shmctl");
		exit(1);
	}
	printf("\n");
return 0;
}
