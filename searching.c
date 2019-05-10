#include<stdio.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include <time.h>

int main()
{
	int pipeid[2], pid, i, size, choice, search;
	srand(time(NULL));

	if(pipe(pipeid) < 0)
		printf("Error creating pipes\n");

	printf("Enter the size of the array: ");
	scanf("%d", &size);

	int array[size];

	printf("\nYou want to enter data or use random data ?\n1. Enter data\n2. Random data\n");
	scanf("%d", &choice);

	if (choice==1)
	{
		for (i = 0; i < size; i++)
		{
			scanf("%d",&array[i]);
		}
	}

	else
	{
		for (i = 0; i < size; i++)
		{
			array[i]=rand()%100;
		}
	}

	printf("\nDisplaying array\n");
	for(i=0; i<size; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	pid=fork();

	if(pid>0)
	{
		printf("\nEnter the number you want to search: ");
		scanf("%d",&search);

		fflush(stdin);
		write(pipeid[1], &search, sizeof(search));
		wait(NULL);
	}

	if(pid==0)
	{
		fflush(stdin);
		read(pipeid[0], &search, sizeof(search));

		for(i=0;i<size;i++)
		{
			if(search==array[i])
			{
				printf("\nFound\n");
				exit(0);
			}
		}

		printf("\nNot found\n");
	}
}