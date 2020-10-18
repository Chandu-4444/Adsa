#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100

typedef struct emp
{
    int Level;
    char Name[100];
    struct emp *Boss;
    struct emp *next;
    struct emp *Child;
} EmpNode;

EmpNode **Lev[MAX] = {NULL};

typedef struct QNode
{
    struct emp *node;
    struct QNode *next;
} QNode;

typedef struct Queue
{
    struct QNode *front;
    struct QNode *rear;
} Queue;

Queue *CreateQueue()
{
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    if (q)
    {
        q->front = q->rear = NULL;
        return q;
    }
    return NULL;
}

int IsQueueEmpty(Queue *Q)
{
    return (Q == NULL || Q->front);
}

int IsQueueFull(Queue *Q)
{
    return (Q == NULL);
}

void EnQueue(Queue **Q, EmpNode *root)
{
    if (*Q == NULL)
    {
        return;
    }
    QNode *tmp = (QNode *)malloc(sizeof(QNode));
    if (tmp == NULL)
    {
        return;
    }
    tmp->node = root;
    tmp->next = NULL;

    if ((*Q)->rear == NULL)
    {
        (*Q)->rear = tmp;
    }
    else
    {
        (*Q)->rear->next = tmp;
        (*Q)->rear = tmp;
    }
    if ((*Q)->front == NULL)
    {
        (*Q)->front = (*Q)->rear;
    }
}

QNode *Dequeue(Queue *q)
{

    if (IsQueueEmpty(q))
        return NULL;

    QNode *tmp;
    tmp = (QNode *)malloc(sizeof(QNode));

    tmp = (q)->front;
    (q)->front = (q)->front->next;

    return tmp;
}

EmpNode *NewNode(EmpNode *boss, char name[], int level)
{
    EmpNode *node = (EmpNode *)malloc(sizeof(EmpNode));
    node->Level = level;
    node->Boss = boss;
    strcpy(node->Name, name);
    node->next = NULL;
    node->Child = NULL;
    return node;
}

EmpNode *Add_Sibling(EmpNode *node, char *name, int level)
{
    EmpNode *tmp = node->Child;
    if (tmp == NULL)
    {
        return NULL;
    }
    while ((tmp)->next)
    {
        (tmp) = (tmp)->next;
    }

    ((tmp)->next = NewNode(node, name, level));
    return node->Child;
}

void *Add_Child(EmpNode **node, char *name, int level)
{
    if (*node == NULL)
    {
        return NULL;
    }
    if ((*node)->Child)
    {
        (*node)->Child = Add_Sibling((*node), name, level);
    }
    else
    {
        ((*node)->Child = NewNode(*node, name, level));
        (Lev[level]) = &(*node)->Child;
    }
}

void PrintAll(EmpNode *root)
{
    Queue *Q = CreateQueue();
    EnQueue(&Q, root);

    while (IsQueueEmpty(Q))
    {
        EmpNode *temp, *temp2;
        temp = Q->front->node;
        Q->front = Q->front->next;
        if (temp == NULL)
        {
            printf("temp is NULL!\n");
            break;
        }

        while (temp != NULL && 1)
        {
            if (strcmp(temp->Name, "NULL"))
            {
                printf("Name: %-7s Boss: %-7s Level: %d \n", temp->Name, temp->Boss->Name, temp->Level);
            }
            if (temp->Child != NULL)
            {
                EnQueue(&Q, temp->Child);
            }
            temp = temp->next;
        }
    }
}

EmpNode *FindLevel(char name[], EmpNode *root)
{
    Queue *Q = CreateQueue();
    EnQueue(&Q, root);

    while (IsQueueEmpty(Q))
    {
        EmpNode *temp, *temp2;
        temp = Q->front->node;
        Q->front = Q->front->next;
        if (temp == NULL)
        {
            printf("temp is NULL!\n");
            break;
        }

        while (temp != NULL)
        {
            if (strcmp(temp->Name, name) == 0)
            {
                return temp;
            }
            if (temp->Child != NULL)
            {
                EnQueue(&Q, temp->Child);
            }
            temp = temp->next;
        }
    }
    return NULL;
}

void LowestCommonBoss(char s[], char s1[], EmpNode *root)
{
    if (strcmp(s, "CEO") == 0 || strcmp(s1, "CEO") == 0)
    {
        printf("CANNOT FIND LOWEST COMMON BOSS FOR CEO!\n");
        return;
    }

    EmpNode *node1 = FindLevel(s, root);
    EmpNode *node2 = FindLevel(s1, root);
    if (!node1)
    {
        printf("CANNOT FIND EMPLOYEE: %s\n", s);
        return;
    }
    if (!node2)
    {
        printf("CANNOT FIND EMPLOYEE: %s\n", s1);
        return;
    }
    if (node1->Level > node2->Level)
    {
        while (1)
        {
            if (node2->Level == node1->Level)
            {
                break;
            }
            node1 = node1->Boss;
        }
    }
    if (node1->Level < node2->Level)
    {
        while (1)
        {
            if (node2->Level == node1->Level)
            {
                break;
            }
            node2 = node2->Boss;
        }
    }
    while (1)
    {
        if (strcmp(node1->Boss->Name, node2->Boss->Name) == 0)
        {
            printf("Lowest Common Boss Of %s and %s is: %s\n", s, s1, node1->Boss->Name);
            break;
        }
        else
        {
            node1 = node1->Boss;
            node2 = node2->Boss;
        }
    }
}

EmpNode *Add_Employee(char Employee[], char boss[], EmpNode *root)
{
    if (!FindLevel(boss, root))
    {
        printf("CANNOT FIND BOSS: %s\n", boss);
        return root;
    }
    EmpNode *New;
    New = (EmpNode *)malloc(sizeof(EmpNode));
    strcpy(New->Name, Employee);
    New->Child = New->next = New->Boss = NULL;
    Queue *Q = CreateQueue();
    EnQueue(&Q, root);
    EmpNode *temp, *temp2;
    temp = root;

    while (IsQueueEmpty(Q))
    {
        temp = Q->front->node;
        Q->front = Q->front->next;
        if ((temp) == NULL)
        {
            printf("temp is NULL!\n");
            break;
        }
        while (temp != NULL)
        {
            if (strcmp((temp)->Name, boss) == 0)
            {
                New->next = (temp)->Child;
                (temp)->Child = New;
                New->Boss = temp;
                New->Level = (temp)->Level + 1;
            }
            if ((temp)->Child != NULL)
            {
                EnQueue(&Q, (temp)->Child);
            }
            temp = (temp)->next;
        }
    }
    return root;
}

EmpNode *Delete_Employee(char s[], char s1[], EmpNode *root)
{
    if (FindLevel(s, root)->Level != FindLevel(s1, root)->Level)
    {
        printf("EMPLOYEES ARE FROM DIFFERENT LEVELS!\n");
        return root;
    }
    if (!FindLevel(s, root))
    {
        printf("CANNOT FIND EMPLOYEE: %s\n", s);
        return root;
    }
    if (!FindLevel(s1, root))
    {
        printf("CANNOT FIND EMPLOYEE: %s\n", s1);
        return root;
    }

    int flag = 0;
    Queue *Q = CreateQueue();
    EnQueue(&Q, root);
    EmpNode *temp, *temp2 = NULL, *ref = NULL, *boss_ref = NULL, *ref_copy = NULL;
    temp = root;

    while (IsQueueEmpty(Q))
    {
        temp = Q->front->node;
        Q->front = Q->front->next;
        if ((temp) == NULL)
        {
            printf("temp is NULL!\n");
            break;
        }
        while (temp != NULL)
        {
            if (strcmp(temp->Name, s1) == 0)
            {
                boss_ref = temp;
            }
            if (temp->next && strcmp(temp->next->Name, s) == 0 && flag == 0)
            {
                EmpNode *cop;
                printf("Entered if : %s\n", temp->next->Name);
                ref = temp->next->Child;
                cop = temp->next;
                temp->next = temp->next->next;
                flag = 1;
                free(cop);
            }
            if ((temp)->Child != NULL)
            {

                if (strcmp(temp->Child->Name, s) == 0 && flag == 0)
                {
                    ref = temp->Child->Child;
                    EmpNode *cop = temp->Child;
                    temp->Child = temp->Child->next;
                    flag = 1;
                    free(cop);
                }

                EnQueue(&Q, (temp)->Child);
            }
            temp = (temp)->next;
        }
    }

    if (ref)
    {
        ref_copy = ref;

        while (ref->next)
        {
            ref->Boss = boss_ref;
            ref = ref->next;
        }
        ref->Boss = boss_ref;
        ref->next = boss_ref->Child;
        boss_ref->Child = ref_copy;
    }

    return root;
}

int main()
{
    EmpNode *root = (EmpNode *)malloc(sizeof(EmpNode));
    root = NewNode(root, "CEO", 1);
    Lev[1] = &root;

    Add_Child(&root, "EMP1", 2);
    Add_Child(&root, "EMP2", 2);
    Add_Child(&root, "EMP3", 2);
    Add_Child(&root, "EMP4", 2);
    Add_Child(&root, "EMP5", 2);
    Add_Child(&root, "EMP6", 2);
    Add_Child(&root, "EMP7", 2);
    Add_Child(&root, "EMP8", 2);
    Add_Child(&root, "EMP9", 2);
    Add_Child(&root->Child, "EMP11", 3);
    Add_Child(&root->Child, "EMP12", 3);
    Add_Child(&root->Child->Child, "EMP111", 4);
    Add_Child(&root->Child->next, "EMP21", 3);
    Add_Child(&root->Child->next, "EMP22", 3);
    Add_Child(&root->Child->next->Child, "EMP211", 4);
    PrintAll(root);
    int Choice;
    char emp[100], boss[100];
    printf("*******************************");
    printf("\n0. Stop Execution\n1. Add_Employee\n2. Delete_Employee\n3. Lowest_Common_Boss\n4. Print_Employees\n");
    printf("*******************************\n");
    printf("--> ");
    scanf("%d", &Choice);
    while (Choice != 0)
    {
        switch (Choice)
        {
        case 1:
            printf("Enter Employee and Boss: ");
            scanf("%s %s", emp, boss);
            root = Add_Employee(emp, boss, root);
            break;
        case 2:
            printf("Enter Employee to be Deleted and Employee to take over: ");
            scanf("%s %s", emp, boss);
            root = Delete_Employee(emp, boss, root);
            break;
        case 3:
            printf("Enter Employee  Names: ");
            scanf("%s %s", emp, boss);
            LowestCommonBoss(emp, boss, root);
            break;
        case 4:
            PrintAll(root);
            break;

        default:
            printf("You've Entered Wrong Choice!\n");
            break;
        }
        printf("*******************************");
        printf("\n0. Stop Execution\n1. Add_Employee\n2. Delete_Employee\n3. Lowest_Common_Boss\n4. Print_Employees\n");
        printf("*******************************\n");
        printf("--> ");
        scanf("%d", &Choice);
    }
    return 0;
}