#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 30
typedef struct node
{
    int coef;
    struct node *next;
}node;
//-----------------------------------------------------
node * init();
//-----------------------------------------------------
void  read(node *h)
{
int n,i,j,power,coef;
node *p;
p=init();
printf("Enter number of terms :\n");
scanf("%d",&n);
/* read n terms */
for (i=0;i<n;i++)
{ 
 printf("enter a term(coeff  power.)\n");
 scanf("%d%d",&coef,&power);
 for(p=h,j=0;j<power;j++)
   p=p->next;
   p->coef=coef;
}
}
//-----------------------------------------------------
void print(node *p)
{
   int i;
for(i=0;p!=NULL;i++,p=p->next)
if(p->coef!=0)
printf("%dX^%d   ",p->coef,i);
}
//-----------------------------------------------------
node * addition(node *h1, node *h2)
{
    node *h3,*p;
    h3=init();
    p=h3;
    while(h1!=NULL)
     {
      h3->coef=h1->coef+h2->coef;
      h1=h1->next;
      h2=h2->next;
      h3=h3->next;
     }
 return(p);
}
//-----------------------------------------------------
node * multiplication(node *h1, node *h2)
{
node *h3,*p,*q,*r;
int i,j,k,coef,power;
h3=init();
for(p=h1,i=0;p!=NULL;p=p->next,i++)
for(q=h2,j=0;q!=NULL;q=q->next,j++)
{
coef=p->coef * q->coef;
power=i+j;
for(r=h3,k=0;k<power;k++)
r=r->next;
r->coef=r->coef+coef;
}
  return(h3);
}
//-----------------------------------------------------
node * init()
{
    int i;
    node *h=NULL,*p;
    for(i=0;i<MAX;i++)
{
p=(node*)malloc(sizeof(node));
p->next=h;
p->coef=0;
h=p;
}
  return(h);
}
//-----------------------------------------------------
void main()
{
node *h1=NULL,*h2=NULL,*h3=NULL;
int op;
//clrscr();
do
{
 printf("\n1 : 1ST POLYNOMIAL \n");
 printf("2 : 2ND POLYNOMIAL \n");
 printf("3 : DISPLAY\n");
 printf("4 : ADDITION OF POLYNOMIALS\n");
 printf("5 : MULTIPLICATION OF POLYNOMIALS\n");
 printf("6 : QUIT\n");
 printf("ENTER YOUR CHOICE  :\n");
 scanf("%d",&op);
 switch(op)
  {
   case 1:
      h1=init();
      read(h1);
      break;
   case 2:
      h2=init();
      read(h2);
      break;
   case 3:
      printf("\n 1ST POLYNOMIAL:  \n");
      print(h1);
      printf("\n 2ND POLYNOMIAL: \n");
      print(h2);
      break;
  case 4:
      h3=addition(h1,h2);
      printf("\n 1ST POLYNOMIAL: \n");
      print(h1);
      printf("\n 2ND POLYNOMIAL: \n");
      print(h2);
      printf("\nSUM = \n");
      print(h3);
      break;
 case 5:
      h3=multiplication(h1,h2);
      printf("\n1ST POLYNOMIAL: \n");
      print(h1);
      printf("\n2ND POLYNOMIAL: \n");
      print(h2);
      printf("\nPRODUCT = \n");
      print(h3);
      break;
}
}
while(op!=6);
getch();
}