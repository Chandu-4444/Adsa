#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TABLE_SIZE 10//For Normal Hashing
#define p 67//A Prime p>=m
#define m 64//Table Size For Universal Hashing


struct node
{
    int data;
    struct node *next;
};


struct node *head[TABLE_SIZE] = {NULL}, *c;
struct node *Uhead[m] = {NULL}, *Uc;

void InsertU(int key, int a, int b)
{
    int index;
    index = ((a * key + b)%p)%m;
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = key;
    newnode->next = NULL;
    if (Uhead[index] == NULL)
        Uhead[index] = newnode;
    else
    {
        Uc = Uhead[index];
        while (Uc->next != NULL)
        {
            Uc = Uc->next;
        }
        Uc->next = newnode;
    }
}

void SearchU(int key, int a, int b)
{
    int index;
    index = ((a * key + b)%p)%m;
    if (Uhead[index] == NULL)
    {
        return;
    }
    else
    {
        for (Uc = Uhead[index]; Uc != NULL; Uc = Uc->next)
        {
            if (Uc->data == key)
            {
                break;
            }
        }
        if (Uc == NULL)
        {
            return ;
        }
    }
}

void Insert(int key)
{
    int index;
    index = key % TABLE_SIZE;
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = key;
    newnode->next = NULL;
    if (head[index] == NULL)
        head[index] = newnode;
    else
    {
        c = head[index];
        while (c->next != NULL)
        {
            c = c->next;
        }
        c->next = newnode;
    }
}
void Search(int key)
{
    int index;
    index = key % TABLE_SIZE;
    if (head[index] == NULL)
    {
        return;
    }
    else
    {
        for (c = head[index]; c != NULL; c = c->next)
        {
            if (c->data == key)
            {
                break;
            }
        }
        if (c == NULL)
        {
            return;
        }
    }
}
void Display()
{

    int i;
    for (i = 0; i < TABLE_SIZE; i++)
    {
        printf("[%d]->", i);
        for (c = head[i]; c != NULL; c = c->next)
            printf("%lld->", c->data);
        printf("\n");
    }
}
int main()
{
    srand(time(0));
    int n, val;
    printf("Please Enter The Input Size: ");
    scanf("%lld", &n);
    clock_t t;
    t = clock();
    //printf("%f\n",t);
    for (int j = 0; j < 100; j++)
    {
        for (int i = 0; i < n; i++)
        {
            Insert(rand() % (n - 0 + 1) + 0);
        }
        
        Search((rand() % n - 0 + 1) + 1);//To search A Random Number As User Can't Input a Number 100 times!
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            head[i] = NULL;//Freeing up The List For Each Outer Iteration
        }
    }
    t = clock() - t;
    printf("Average Time Taken For 100 Iterations on input size %lld and for searching a random elements 100 time is: %f Sec\n", n, ((double)(t) / CLOCKS_PER_SEC)/100);

  
    //Universal Hashing Method 

    clock_t t2 = clock();
    srand(time(NULL));
    //printf("%f\n",t2);

    for (int j = 0; j < 100; j++)
    {
        int a = rand()%(100000)+1;
        int b = rand()%(100000)+1;
        for (int i = 0; i < n; i++)
        {

            InsertU(rand() % (n - 0 + 1) + 0, a, b);
        }
        SearchU(rand() % (n - 0 + 1) + 1, a, b);
        for (int i = 0; i < 64; i++)
        {
            Uhead[i] = NULL;
        }
    }
    t2 = clock() - t2;
    printf("Average Time Taken For Universal Hashing Of 100 Iterations on input size %lld and for searching a random elements 100 time is: %f Sec\n", n, ((double)(t-t2) / CLOCKS_PER_SEC)/100);

    return 0;
}