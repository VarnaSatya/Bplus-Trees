#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"head.h"

node* create(int val,int t,int m)
{   
    node *temp=(node*)malloc(sizeof(node));
    temp->val=(int*)malloc(sizeof(int)*(m-1));
    int i;
    //t=1 -> internal node
    if(t==1)
        temp->child=(node**)malloc(sizeof(node*)*m);
    else
        temp->addi=(info**)malloc(sizeof(info*)*m);
    
    for(i=0;i<(m-1);i++)
    {
        temp->val[i]=__INT_MAX__;
        if(t==1)
            temp->child[i]=NULL;
        else
            temp->addi[i]=NULL;
    }
    if(t==1)
            temp->child[i]=NULL;
        else
            temp->addi[i]=NULL;

    temp->val[0]=val;
    temp->numVal=1;
    temp->leaf=!t;
    temp->next=NULL;
    return temp;
}

void disp(node *root)
{
    if(root->leaf==1)
    {
        int i;
        for(i=0;i<root->numVal;i++)
            printf("%d\t",root->val[i]);
        return;
    }

    int i;
    for(i=0;i<root->numVal;i++)
    {
        disp(root->child[i]);
        printf("%d\t",root->val[i]);
    }
    disp(root->child[i]);
}

node* retPar(node *root,node *cur)
{
    int i=0; 
    node *temp=root;
    int val=cur->val[0];
    while(i<temp->numVal)
    {
        if(val<temp->val[i])
        {
            if(temp->leaf==1)
                break;

            if(cur==temp->child[i])
                return temp;

            temp=temp->child[i];
            i=0;
        }
        else if(i+1<temp->numVal && val<temp->val[i+1])
        {
            if(temp->leaf==1)
            {
                i++;
                break;
            }

            if(cur==temp->child[i+1])
                return temp;

            temp=temp->child[i+1];
            i=0;  
        }
        else if(val<temp->val[i+1] && temp->leaf!=1)
        {
            if(cur==temp->child[i+1])
                return temp;

            temp=temp->child[i+1];
            i=0;
        }
        else
            i++;
    }
    return NULL;
}

void popN(node **dest,node *source,int beg,int end)     //beg included, end excluded
{
    int i;
    for(i=beg;i<end;i++)
    {
        (*dest)->val[i-beg]=source->val[i];
        if((*dest)->leaf==0)              //internal node
            (*dest)->child[i-beg]=source->child[i];
        else                        //leaf node
            (*dest)->addi[i-beg]=source->addi[i];
    }
    if((*dest)->leaf==0)              //internal node
        (*dest)->child[i-beg]=source->child[i];
    else                        //leaf node
        (*dest)->addi[i-beg]=source->addi[i];
    (*dest)->numVal=end-beg;
}

node* findPosInsert(node *root,int val)
{
    if(root==NULL)
        return NULL;

    node *temp=root;
    int i=0; 
    while(i<temp->numVal)
    {
        if(val<temp->val[i])
        {
            if(temp->leaf==1)
                break;
            temp=temp->child[i];
            i=0;
        }
        else if(i+1<temp->numVal && val<temp->val[i+1])
        {
            if(temp->leaf==1)
            {
                i++;
                break;
            }
            temp=temp->child[i+1];
            i=0;  
        }
        else if(val<temp->val[i+1] && temp->leaf!=1)
        {
            temp=temp->child[i+1];
            i=0;
        }
        else
            i++;
    }
    return temp;
    
}

void shiftR(int *a,int pos,int lim)
{
    for(int i=lim;i>pos;i--)
        a[i]=a[i-1];
}
void shiftRi(info **a,int pos,int lim)
{
    for(int i=lim;i>pos;i--)
        a[i]=a[i-1];
}
void shiftRig(node **a,int pos,int lim)
{
    for(int i=lim;i>pos;i--)
        a[i]=a[i-1];
}

void insert_in_leaf(node *l,int k,void *p)
{
    if(l==NULL)
        return;
    int i;
    //printf("Hello\n");
    for(i=0;i<l->numVal;i++)
        if(k<l->val[i])
            break;
    shiftR(l->val,i,l->numVal);
    if(l->leaf==1)
    {
        shiftRi(l->addi,i,l->numVal+1);
        l->addi[i]=(info*)p;
    }
    else
    {
        shiftRig(l->child,i+1,l->numVal+1);
        l->child[i+1]=(node*)p;
    }
    l->val[i]=k;
    l->numVal++;
}

node* insert_in_parent(node *root,node *n,int k,void *nd)
{
    if(n==root)
    {
        node *r=create(k,1,m);
        r->child[0]=n;
        r->child[1]=(node*)nd;
        r->numVal=1;
        r->leaf=0;
        root=r;
        return r;
    }
    node *p=retPar(root,n);
    if(p->numVal<m-1)
    {
        insert_in_leaf(p,k,nd);
    }
    else
    {
        node *t=create(k,1,m+1);

        //populating t
        int i;
        if(p->leaf==0)              //internal node
            t->child[0]=p->child[0];
        else                        //leaf node
            t->addi[0]=p->addi[0];
        
        for(i=0;i<m-1;i++)
        {
            if(k<p->val[i])
                break;
            t->val[i]=p->val[i];
            if(p->leaf==0)              //internal node
                t->child[i+1]=p->child[i+1];
            else                        //leaf node
                t->addi[i+1]=p->addi[i+1];
        }
        
        t->val[i]=k;
        if(p->leaf==0)
            t->child[i+1]=(node*)nd;
        else
            t->addi[i+1]=(info*)nd;
              
        for(;i<m;i++)
        {
            t->val[i+1]=p->val[i];
            if(p->leaf==0)
                t->child[i+2]=p->child[i+1];
            else
                t->addi[i+2]=p->addi[i+1];
        }
        
        t->numVal=m;

        //populate l
            popN(&p,t,0,(int)ceil(m/2));

        //populate l'
        node *pd=create(0,1,m);
        if(p->leaf==1)
            popN(&pd,t,(int)ceil(m/2),m);
        else
            popN(&pd,t,(int)ceil(m/2)+1,m);


        root=insert_in_parent(root,p,t->val[(int)ceil(m/2)],pd);
    }
    return root;   
}

node* insert(node *root,int val,void *p)
{
    if(root==NULL)
    {
        node *temp=create(val,0,m);
        temp->addi[0]=(info*)p;
        return temp;
    }
    else
    {
        node *l=findPosInsert(root,val);
        
        if(l->numVal < m-1)
        {    
            insert_in_leaf(l,val,p);
        }
        else
        {
            node *t=create(0,!l->leaf,5);
            int i;
            //populating t
            for(i=0;i<m-1;i++)
            {
                if(val<l->val[i])
                    break;
                t->val[i]=l->val[i];
                if(l->leaf==0)              //internal node
                    t->child[i]=l->child[i];
                else                        //leaf node
                    t->addi[i]=l->addi[i];
            }
            t->val[i]=val;
            if(l->leaf==0)
                t->child[i]=(node*)p;
            else
                t->addi[i]=(info*)p;
                
            for(;i<m-1;i++)
            {
                t->val[i+1]=l->val[i];
                if(l->leaf==0)
                    t->child[i+1]=l->child[i];
                else
                    t->addi[i+1]=l->addi[i];
            }
            if(l->leaf==0)
                    t->child[i+1]=l->child[i];
                else
                    t->addi[i+1]=l->addi[i];
            t->numVal=m;

            //populate l
            popN(&l,t,0,(int)ceil(m/2));

            //populate l'
            node *ld=create(0,!l->leaf,m);
            if(l->leaf==1)
                popN(&ld,t,(int)ceil(m/2),m);
            else
                popN(&ld,t,(int)ceil(m/2)+1,m);

            ld->next=l->next;
            l->next=ld;

            root=insert_in_parent(root,l,t->val[(int)ceil(m/2)],ld);
        }
    }
    return root;
}



