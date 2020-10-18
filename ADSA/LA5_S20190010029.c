#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 26

struct Trie
{
    int Is_Leaf;                        // To Mark Leaf Node In Trie
    int Count;                          //Stores Count Of The Word in Trie
    struct Trie *Alphabet[MAX_SIZE];
};

struct Trie *CreateNode()
{
    struct Trie *NewNode = (struct Trie *)malloc(sizeof(struct Trie));
    NewNode->Is_Leaf = 0;
    NewNode->Count = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        NewNode->Alphabet[i] = NULL;
    }
    return NewNode;
}

int Insert(struct Trie *head, char *str)
{
    char str_cpy[101];
    strcpy(str_cpy, str);
    struct Trie *curr = head;
    while (*str)
    {
        if (*str == '\n') // To Solve Insertion Of \n When Reading From File !
        {
            str++;
            continue;
        }
        if (curr->Alphabet[*str - 'a'] == NULL)
        {
            curr->Alphabet[*str - 'a'] = CreateNode();
        }
        curr = curr->Alphabet[*str - 'a'];
        str++;
    }
    curr->Is_Leaf = 1;
    curr->Count = curr->Count + 1;
    return curr->Count;
}

int Search(struct Trie *head, char *str)
{
    if (head == NULL)
    {
        return 0;
    }
    struct Trie *curr = head;
    while (*str)
    {
        curr = curr->Alphabet[*str - 'a'];

        if (curr == NULL)
        {
            return 0;
        }
        str++;
    }

    return curr->Count;
}

int CheckChildren(struct Trie *curr)    //Function To Check Whether Or Not Node Has Children
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (curr->Alphabet[i])
        {
            return 1;
        }
    }
    return 0;
}

int Deletion(struct Trie **curr, char *str)
{
    if (Search(*curr, str) > 1)//When The Word To Be Deleted Occurs More Than Once, We Don't Really Need To Delete It But We Need To Decrement It's Count
    {
        struct Trie *Curr_Copy = *curr;
        while (*str)
        {
            Curr_Copy = Curr_Copy->Alphabet[*str - 'a'];

            if (Curr_Copy == NULL)
            {
                return 0;
            }
            str++;
        }
        (Curr_Copy)->Count = (Curr_Copy)->Count - 1;
        return (Curr_Copy)->Count;
    }

if (*curr == NULL)
{
    return 0;
}
if (*str)
{
    if (*curr != NULL && (*curr)->Alphabet[*str - 'a'] != NULL && Deletion(&(*curr)->Alphabet[*str - 'a'], str + 1) && (*curr)->Is_Leaf == 0)
    {
        if (!CheckChildren(*curr))
        {
            free(*curr);
            (*curr) = NULL;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
if (*str == '\0' && (*curr)->Is_Leaf)
{
    if (!CheckChildren(*curr))
    {
        free(*curr);
        *curr = NULL;
        return 1;
    }
    else
    {
        (*curr)->Is_Leaf = 0;
        return 0;
    }
}
return 0;
}

int main()
{
    struct Trie *Head = CreateNode();
    FILE *fptr;
    int cou;
    char str[100];
    fptr = fopen("Input.txt", "r");
    while (fgets(str, 101, fptr))
    {
        printf("Inserted :%s", str);
        cou = Insert(Head, str);
    }
    printf("\n");
    while (1)
    {
        printf("*******************************************\n");
        printf("\t1.Insertion\n\t2.Deletion\n\t3.Searching\n\t4.Quit\nEnter Your Choice :");
        int ch;
        scanf("%d", &ch);
        if (ch == 4)
        {
            break;
        }
        switch (ch)
        {
        case 1:
            printf("Enter String To Insert :");
            scanf("%s", str);
            cou = Insert(Head, str);
            printf("Insertion Successful. Count Of %s : %d\n", str, cou);
            break;
        case 2:
            printf("Enter String To Delete :");
            scanf("%s", str);
            if (Search(Head, str) == 0)
            {
                printf("Can't be deleted Unless It Belongs To Trie!\n");
                break;
            }
            cou = Deletion(&Head, str);
            printf("Deletion Successful. Count of Word %s Is Now : %d\n", str, cou);
            break;
        case 3:
            printf("Enter String To Search : ");
            scanf("%s", str);
            cou = Search(Head, str);
            printf("Word \"%s\" Found %d Times\n", str, cou);
            break;
        default:
            printf("Please Enter Correct Choice!\n");
            break;
        }
    }
}
