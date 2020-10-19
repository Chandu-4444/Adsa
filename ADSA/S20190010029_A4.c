#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define COUNT 10

typedef struct TreeNode{
    int data;
    char color;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
}MultiSet;


struct TreeNode **Root; //Duplicate Root

struct TreeNode *Init(int data)
{
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->data = data;
    temp->color = 'R';
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

void LeftRotate(struct TreeNode **root,struct TreeNode *x)
{
    if (!x || !x->right)
        return ;
    struct TreeNode *y = x->right;

    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
        (*root) = y;

    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;

    y->left = x;

    x->parent = y;
}

void RightRotate(struct TreeNode **root,struct TreeNode *y)
{
    if (!y || !y->left)
        return ;
    struct TreeNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}



void FixUp(struct TreeNode **root, struct TreeNode *NewNode)
{
    while(NewNode!=*root && NewNode!=(*root)->left && NewNode!=(*root)->right && NewNode->parent->color == 'R' )
    {
        struct TreeNode *Uncle;


        //Finding Sibling Of Parent Node (Finding Uncle Node)
        if(NewNode->parent && NewNode->parent->parent && NewNode->parent == NewNode->parent->parent->left)
        {
            Uncle = NewNode->parent->parent->right;
        }
        else
        {
            Uncle = NewNode->parent->parent->left;
        }

        //If Uncle Is RED,
        //(i)  Change Color Of Parent And Uncle as BLACK
        //(ii) Change Color Of GrandParent as RED
        //(iii) Point NewNode to GrandParent For Repeating The Process Until The Tree Is Fixed
        if(!Uncle)
        {
            NewNode = NewNode->parent->parent;
        }
        else if(Uncle->color == 'R')
        {
            Uncle->color = 'B';
            NewNode->parent->color = 'B';
            NewNode->parent->parent->color = 'R';
            NewNode = NewNode->parent->parent;
        }
        //If Uncle Is BLACK Then, There Are Four Cases (LL, LR, RL, RR)
        else
        {
            //Left-Left (LL) case,
            // (i) Swap color Of Parent and GrandParent
            // (ii) Right Rotate GrandParent
            if(NewNode == NewNode->parent->left && NewNode->parent == NewNode->parent->parent->left && NewNode->parent && NewNode->parent->parent)
            {
                //Swapping Colors Of Parent And GrandParent
                char col = NewNode->parent->color;
                NewNode->parent->color = NewNode->parent->parent->color;
                NewNode->parent->parent->color = col;

                RightRotate(root ,NewNode->parent->parent);
            }
            //Right-Right (RR) Case,
            // (i) Swap color of Parent and GrandParent
            // (ii) Left Rotate GrandParent
            if( NewNode->parent == NewNode->parent->parent->right && NewNode == NewNode->parent->right && NewNode->parent && NewNode->parent->parent)
            {
                //Swapping Colors Of Parent And GrandParent
                char col = NewNode->parent->color;
                NewNode->parent->color = NewNode->parent->parent->color;
                NewNode->parent->parent->color = col;

                LeftRotate(root, NewNode->parent->parent);
            }

            //Right-Left (RL) case,
            //(i) Swap Colors of Current Node And GrandParent
            //(ii) Right Rotate Parent
            //(iii) Left-Rotate GrandParent
            if(NewNode->parent && NewNode->parent->parent && NewNode->parent == NewNode->parent->parent->right && NewNode == NewNode->parent->left)
            {
                char col = NewNode->color;
                NewNode->color = NewNode->parent->parent->color;
                NewNode->parent->parent->color = col;
                RightRotate(root, NewNode->parent);
                LeftRotate(root, NewNode->parent->parent);
            }

            //Left-Right (LR) Case,
            //(i) Swap Color Of Current Node And GrandParent
            //(ii) Left Rotate Parent
            //(iii)Right Rotate GrandParent
            if(NewNode->parent && NewNode->parent->parent && NewNode->parent == NewNode->parent->parent->left && NewNode == NewNode->parent->right)
            {
                char col = NewNode->color;
                NewNode->color = NewNode->parent->parent->color;
                NewNode->parent->parent->color = col;
                LeftRotate(root, NewNode->parent);
                RightRotate(root, NewNode->parent->parent);
            }
            
        }
    }
    (*root)->color = 'B'; //Setting Back Color Of Root To Black

}

void Insert(struct TreeNode **root, int data)
{
    struct TreeNode * NewNode;
    NewNode = Init(data);
    if(*root == NULL)
    {
        NewNode->color = 'B';
        (*root) = NewNode;
        Root = root;
    }
    else
    {
        struct TreeNode *NewNodeParent = NULL;
        struct TreeNode *CurrRoot =(*root);

        //Following Standard BST INSERTION Steps
        while (CurrRoot)
        {
            NewNodeParent = CurrRoot;
            if(NewNode->data < CurrRoot->data)
            {
                CurrRoot = CurrRoot->left;
            }
            else
            {
                CurrRoot = CurrRoot->right;
            }
        }
        //By The Time We Reach Here, We Have Found The Correct Place Of Element To Be Inserted.
        NewNode->parent = NewNodeParent;
        if(NewNode->data > NewNodeParent->data)
        {
            NewNodeParent->right = NewNode; 
        }
        else
        {
            NewNodeParent->left = NewNode; 
        }

        FixUp(root, NewNode);
        
    }

}


int main()
{
    MultiSet *root=NULL;
    printf("Start Entering Node : \n");
    while(1)
    {
        int val;
        scanf("%d",&val);
        Insert(&root, val);
        if(val==-1)
        {
            break;
        }
    }
    printf("\n");
   
}


