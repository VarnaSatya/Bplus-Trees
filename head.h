int m; //order of B+ trees

typedef struct info
{
    int val;
}info;

typedef struct node
{
    int *val;
    union{
    struct node **child;    //in case of internal node
    info **addi; };           //in case if leaf node
    int numVal;             //number of values in the node
    int leaf;               //leaf=1 -> is a leaf node
    struct node *next;      //used instead of last child pointer as leaf nodes have info* type and not child* type
}node;





void disp(node *root);
node* insert(node *root,int val,void *p);
