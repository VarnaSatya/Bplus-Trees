#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"head.h"

int main()
{
    m=4;
    //int a[]={1,4,7,10,17,21,31,25,19,20,28,42},x=12; info in[12]; //hardcoded data
    
    // /*        randomly generated data
    int *a,x,y,j;
    printf("Enter number of numbers\n");
    scanf("%d",&x);
    a=(int*)malloc(sizeof(int)*x);
    info *in=(info*)malloc(sizeof(info)*x);
    for(int i=0;i<x;i++)
    {
        y=rand();
        for(j=0;j<i;j++)    //to not have duplicates
            if(a[j]==y)
            {
                i--;
                break;
            }
        if(j==i)
        {
            a[i]=y;
            in->val=y;
        }
    }
     // */

    node *root=NULL;
    for(int i=0;i<x;i++)
    {
        in[i].val=a[i];
        root=insert(root,a[i],&in[i]);
        disp(root);
        printf("\n");
    }  
    node *temp=root;
    while(temp->leaf==0)
        temp=temp->child[0];

    printf("value\trecord\n");
    while(temp!=NULL)
    {
        for(int i=0;i<temp->numVal;i++)
        {
            printf("%d\t%d\n",temp->val[i],temp->addi[i]->val);
        }
        temp=temp->next;
    }
}