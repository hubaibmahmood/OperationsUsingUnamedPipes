#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
int main()
{  
   int array[5],flag,i,j,key;
   int childparentfd[2],parentchildfd[2];

   if((pipe(childparentfd)||pipe(parentchildfd))<0)
   {
     exit(1);
   }

   pid_t childprocess=fork();
   
   assert(childprocess>=0);	
   
   if(childprocess==0)
  {
    close(childparentfd[0]);// We need to close unwanted ends as child reads and then writes on parent
    close(parentchildfd[1]);
    
    read(parentchildfd[0],array,sizeof(array));

    printf("Child recieves unsorted array\n");

for(i=0;i<5;i++)
{
  printf(" %d",array[i]);
}     

for (i = 1; i < 5; i++)
{  
  key = array[i]; 
  j = i - 1;

  while (j >= 0 && array[j] > key) 
  { 
    array[j + 1] = array[j]; 
    j = j - 1; 
  } 
  array[j + 1] = key; 
   } 
 printf("\n");
 printf("Child sending sorted array\n");

for(i=0;i<5;i++)
{
  printf(" %d",array[i]);
}    

printf("\n");  

write(childparentfd[1],array,sizeof(array));	

exit(0);	  

}


close(childparentfd[1]); //We need to close unwanted ends as parent reads and then writes on child
close(parentchildfd[0]);

printf("Enter values:");
for(i=0;i<5;i++)
{
  scanf("%d",&array[i]);
}

printf("Parent is sending the unsorted array\n");
for(i=0;i<5;i++)
{
  printf(" %d",array[i]);
}

printf("\n");

write(parentchildfd[1],array,sizeof(array));

read(childparentfd[0],array,sizeof(array));

printf("Parent has recieved the sorted array:\n");

for(i=0;i<5;i++)
{
  printf(" %d",array[i]);
}

}
