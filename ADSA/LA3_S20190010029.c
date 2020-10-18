#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<math.h>
#define MAX 10000

struct treeNode
{
    int data;
    struct treeNode *left, *right;
};

/* create a new node with the given data */
struct treeNode *CreateNode(int data)
{
    struct treeNode *newNode;
    newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return (newNode);
}

/* insertion in binary search tree */
void Insertion(struct treeNode **node, int data)
{
    if (*node == NULL)
    {
        *node = CreateNode(data);
    }
    else if (data < (*node)->data)
    {
        Insertion(&(*node)->left, data);
    }
    else if (data > (*node)->data)
    {
        Insertion(&(*node)->right, data);
    }
}

struct treeNode *MinValueNode(struct treeNode *node)
{
    struct treeNode *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

/* deletion in binary search tree */
struct treeNode *Deletion(struct treeNode *root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->data)
    {
        root->left = Deletion(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = Deletion(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            struct treeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct treeNode *temp = root->left;
            free(root);
            return temp;
        }
        struct treeNode *temp = MinValueNode(root->right);
        root->data = temp->data;
        root->right = Deletion(root->right, temp->data);
    }
    return root;
}

/* search the given element in binary search tree */
void SearchElement(struct treeNode *node, int data)
{
    if (!node)
        return;
    else if (data < node->data)
    {
        SearchElement(node->left, data);
    }
    else if (data > node->data)
    {
        SearchElement(node->right, data);
    }
    else
        printf("data found: %d\n", node->data);
    return;
}

void Traverse(struct treeNode *node)
{
    if (node != NULL)
    {
        Traverse(node->left);
        printf("%3d", node->data);
        Traverse(node->right);
    }
    return;
}

void GenRandomArray(int arr[], int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (rand() % (n - 0 + 1)) + 0;
    }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    int i;
    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp, int base)
{
    int output[n]; // output array
    int i, count[base];
    for (int i = 0; i < base; i++)
    {
        count[i] = 0;
    }

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % base]++;

    for (i = 1; i < base; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using Radix Sort
void radixsort(int arr[], int n, int base)
{
    int m = getMax(arr, n);

    int exp;
    for (exp = 1; m / exp > 0; exp *= base)
        countSort(arr, n, exp, base);
}

double StandardDev(double tim[], double avg)
{
    double ans=0.0;
    for(int i=0;i<100;i++)
    {
        ans=(ans+(tim[i]-avg)*(tim[i]-avg))/CLOCKS_PER_SEC;
    }
    ans=ans/10000;
    ans=sqrt(ans);
    return ans;

}

void print(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main()
{
    
    printf("********RADIX SORT*********\n");
    int base, n;
    printf("Enter The Preferred radix or base for RadixSort (Must be a positive number): ");
    scanf("%d", &base);
    printf("Enter Size of Array to be Generated :\n");
    scanf("%d", &n);
    printf("Generating a random array from 0 to %d of size %d ...\n", n, n);
    int arr[n];
    GenRandomArray(arr, n);
    radixsort(arr, n, base);
    print(arr, n);
    printf("\n");
    printf("\n");
    
    
    /*
    clock_t t;
    int arr[MAX];
    int base;
    printf("Enter Base :");
    scanf("%d",&base);
    double tim1[100],avg1=0.0;
    for (int i = 0; i < 1000; i++)
    {
        t = clock();
        GenRandomArray(arr, MAX);
        radixsort(arr, MAX, base);
        t = clock() - t;
        tim1[i]=t;
        avg1=avg1+tim1[i];
    }
    avg1=(avg1/100);
    avg1=avg1/(CLOCKS_PER_SEC);//Converting to seconds
    printf("Average time taken to sort %d elements 100 times is : %f sec with standard deviation : %f\n", MAX, avg1,StandardDev(tim1,avg1));
    */
    
        printf("*********BINARY TREE*********\n");
        int data, ch;
        struct treeNode *root;
        root=NULL;
        while (1) {
                printf("1. Insertion in Binary Search Tree\n");
                printf("2. Deletion in Binary Search Tree\n");
                printf("3. Search Element in Binary Search Tree\n");
                printf("4. Inorder traversal\n5. Exit\n");
                printf("Enter your choice:");
                scanf("%d", &ch);
                getchar();
                if(ch==5) break;
                switch (ch) {
                        case 1:
                                while (1) {
                                printf("Enter your data:");
                                scanf("%d", &data);
                                Insertion(&root, data);
                                printf("Continue Insertion(0/1):");
                                scanf("%d", &ch);
                                if (!ch)
                                        break;
                                }
                                break;
                        case 2:
                                printf("Enter your data:");
                                scanf("%d", &data);
                                root=Deletion(root, data);
                                break;
                        case 3:
                                printf("Enter value for data:");
                                scanf("%d", &data);
                                SearchElement(root, data);
                                break;
                        case 4:
                                printf("Inorder Traversal:\n");
                                Traverse(root);
                                printf("\n");
                                printf("\n");
                                break;
                        default:
                                printf("u've entered wrong option\n");
                                break;
                }
        }
        
        
    return 0;
}