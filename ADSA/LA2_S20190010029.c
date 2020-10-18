#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 5
#define MAX2 10

void GenRandomArray(int arr[])
{
    srand(time(0));
    for (int i = 0; i < MAX; i++)
    {
        arr[i] = (rand() % (MAX - 0 + 1)) + 0;
    }
}

void GenRandomArray2(int arr[])
{
    srand(time(0));
    for (int i = 0; i < MAX2; i++)
    {
        arr[i] = (rand() % (MAX2 - 0 + 1)) + 0;
    }
}

void PrintArray(int arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        printf("\t\t\t%d\n", arr[i]);
    }
    printf("\n");
}

void PrintArray2(int arr[])
{
    for (int i = 0; i < MAX2; i++)
    {
        printf("\t\t\t%d\n", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int IsSorted(int arr[])
{
    int len = MAX;
    while (--len > 0)
    {
        if (arr[len] < arr[len - 1])
        {
            return 0;
        }
    }
    return 1;
}

void Shuffle(int arr[])
{
    srand(time(NULL));
    for (int i = MAX - 1; i > 0; i--)
    {
        int j = rand() % (MAX);
        swap(&arr[i], &arr[j]);
    }
}

void BogoSort(int arr[])
{
    while (IsSorted(arr) == 0)
    {
        Shuffle(arr);
    }
}

int Partition(int arr[], int low, int high)
{
    int Pivot = arr[high]; //Right most as pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= Pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int Partition_Random(int arr[], int low, int high)
{
    srand(time(NULL));
    int RandomPivot = low + rand() % (high - low);
    swap(&arr[RandomPivot], &arr[high]);

    return Partition(arr, low, high);
}

void RandomizedQSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = Partition_Random(arr, low, high);
        RandomizedQSort(arr, low, pivot - 1);
        RandomizedQSort(arr, pivot + 1, high);
    }
}



double StandardDev(double tim[], double avg)
{
    double ans=0.0;
    for(int i=0;i<100;i++)
    {
        ans=(ans+(tim[i]-avg)*(tim[i]-avg))/CLOCKS_PER_SEC;
    }
    ans=ans/100;
    ans=sqrt(ans);
    return ans;

}

int main()
{
    int arr[MAX];
    
    printf("\n********************Bogosort*********************\n");

    GenRandomArray(arr);
    printf("\t\tOriginal Array :\n");
    PrintArray(arr);
    BogoSort(arr);
    
   
    /*
    clock_t t;
    double tim1[100],avg1=0.0;
    for (int i = 0; i < 100; i++)
    {
        t = clock();
        GenRandomArray(arr);
        BogoSort(arr);
        t = clock() - t;
        tim1[i]=t;
        avg1=avg1+tim1[i];
    }
    avg1=(avg1/100);
    avg1=avg1/(CLOCKS_PER_SEC);//Converting to seconds
    printf("Average time taken to sort %d elements 100 times is : %f sec with standard deviation : %f\n", MAX, avg1,StandardDev(tim1,avg1));
    */
    
    printf("\t\tAfter Sorting :\n");
    PrintArray(arr);
    
    printf("\n**************Randomized Quick Sort******************\n");
    int arr2[MAX2];
    
    GenRandomArray2(arr2);
    printf("\t\tOriginal Array :\n");
    PrintArray2(arr2);
    RandomizedQSort(arr2, 0,MAX2-1);

    
    /*
    clock_t t2;
    double tim2[100],avg2=0.0;
    for (int i = 0; i < 5; i++)
    {
        t2 = clock();
        RandomizedQSort(arr2, 0, MAX2 - 1);
        GenRandomArray2(arr2);
        t2 = clock() - t2;
        tim2[i]=t2;
        avg2=avg2+tim2[i];
    }
    avg2=avg2/100;
    avg2=avg2/CLOCKS_PER_SEC;

    double std2=0.0;
    std2=StandardDev(tim2,avg2);
    printf("Average time taken to RandomizedQSort %d elements 100 times is : %f sec with standard deviation : %f sec\n", MAX2, avg2,std2);
    */
    
    printf("\t\tAfter Sorting :\n");
    PrintArray2(arr2);
    
}