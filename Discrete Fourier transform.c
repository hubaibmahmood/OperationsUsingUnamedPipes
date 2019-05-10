#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#define PI 3.14159265
struct DFT_Coefficient {

    double real, img;

};


int main()
{  
    int array[5],flag,i,j,N=10,k=20;
    float a,b,c;
    double sine[N],cosine[N];
    
    struct DFT_Coefficient dft_val[k];
    
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
    read(parentchildfd[0],&a,sizeof(a));
    read(parentchildfd[0],&b,sizeof(b));
    read(parentchildfd[0],&c,sizeof(c));
    double function[N];

for (i = 0; i < N; i++) 
{
function[i] = (((a * (double) i) + (b * (double) i)) - c);
}
for (i = 0; i < N; i++) 
{
cosine[i] = cos((2 * i * k * PI) / N);
sine[i] = sin((2 * i * k * PI) / N);
}
for (j = 0; j < k; j++) 
{
for (i = 0; i < N; i++)
{
  dft_val[j].real += function[i] * cosine[i];
  dft_val[j].img += function[i] * sine[i];
}

write(childparentfd[1],dft_val,sizeof(dft_val));
  exit(0);	  
}
}
close(childparentfd[1]); //We need to close unwanted ends as parent reads and then writes on child
close(parentchildfd[0]);
 printf("Discrete Fourier Transform using naive method\n");
 printf("Enter the coefficient of simple linear function:\n");
printf("ax + by = c\n");
 scanf("%f", &a);
 scanf("%f", &b);
scanf("%f", &c);
write(parentchildfd[1],&a,sizeof(a));
write(parentchildfd[1],&b,sizeof(b));
write(parentchildfd[1],&c,sizeof(c));
read(childparentfd[0],dft_val,sizeof(dft_val));
    for (j = 0; j < k; j++) 
{
   for (i = 0; i < N; i++) 
{  printf("( %e ) - ( %e i)\n", dft_val[j].real, dft_val[j].img);

}

  }
}
