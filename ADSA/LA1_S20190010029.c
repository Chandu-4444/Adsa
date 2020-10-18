#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10

void Swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void GenRandomArray(int arr[])
{
    srand(time(0));
    for (int i=0;i<MAX;i++)
    {
        arr[i]=(rand()%(1000-0+1))+0;
    }
}

void PrintArray(int arr[])
{
    for (int i=0;i<MAX;i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");
}


void InsertionSort(int arr[])
{
    int curr;
    for (int i=0;i<MAX;i++)
    {
        curr=arr[i];
        int j=i-1;
        while (j>=0 && arr[j]>curr)
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=curr;
    }

    printf("After Insertion Sort:\n");
    PrintArray(arr);
}

void Merge(int arr[], int left, int middle, int right)
{
    int l=middle-left+1;
    int r=right-middle;
    int LArr[l], RArr[r];

    for (int i=0;i<l;i++)
    {
        LArr[i]=arr[left+i];
    }
    for (int i=0;i<r;i++)
    {
        RArr[i]=arr[middle+1+i];
    }

    int i=0, j=0, k=left;

    while (i<l && j<r)
    {
        if (LArr[i]<=RArr[j])
        {
            arr[k++]=LArr[i++];
        }
        else
        {
            arr[k++]=RArr[j++];
        }

    }

    while (i<l)
    {
        arr[k++]=LArr[i++];
    }
    while (j<r)
    {
        arr[k++]=RArr[j++];
    }
}


void MergeSort(int arr[], int left, int right)
{
    if (left<right)
    {
        int middle=(left+right)/2;
        MergeSort(arr, left, middle);
        MergeSort(arr, middle+1, right);
        Merge(arr, left, middle, right);
    }

}
//
//
//int Partition(int arr[], int left, int right)
//{
//   int Pivot=arr[right];
//
//   int i=left-1;
//
//   for (int j=left;j<=right-1;j++)
//   {
//       if (arr[j]<Pivot)
//       {
//           i++;
//           Swap(&arr[i], &arr[j]);
//           /*
//           int temp=arr[i];
//           arr[i]=arr[j];
//           arr[j]=temp;
//           */
//       }
//   }
//   Swap(&arr[i+1], &arr[right]);
//   /*
//   int temp=arr[i+1];
//   arr[i+1]=arr[right];
//   arr[right]=temp;
//   */
//   return (i+1);
//
//}
//
//


int Partition(int arr[], int left, int right)
{
    int Pivot=arr[left];

    int i=right+1;

    for (int j=right;j>=left+1;j--)
    {
        if (arr[j]>Pivot)
        {
            i--;
            Swap(&arr[i], &arr[j]);
            /*
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            */
        }
    }
    Swap(&arr[i-1], &arr[left]);
    /*
    int temp=arr[i+1];
    arr[i+1]=arr[right];
    arr[right]=temp;
    */
    return (i-1);

}


void QuickSort(int arr[], int left, int right)
{
    if (left<right)
    {
        int middle=Partition(arr, left, right);

        QuickSort(arr, left, middle-1);
        QuickSort(arr, middle+1, right);
    }

}

void Heapify(int arr[], int size, int i)
{
    int max=i, left=2*i+1, right=2*i+2;

    if (left<size && arr[left]>arr[max])
    {
        max=left;
    }
    if (right<size && arr[right]>arr[max])
    {
        max=right;
    }

    if (max!=i)
    {
        Swap(&arr[i], &arr[max]);
        Heapify(arr, size, max);
    }
}


void HeapSort(int arr[], int n)
{
    for (int i=n/2-1;i>=0;i--)
    {
        Heapify(arr, n, i);
    }

    for (int i=n-1;i>0;i--)
    {
        Swap(&arr[0], &arr[i]);
        Heapify(arr, i, 0);
    }

}



int main()
{
    int arr[MAX];

    printf("*********INSERTION SORT*********\n");
    GenRandomArray(arr);
    printf("Orininal Array :\n");
    PrintArray(arr);
    InsertionSort(arr);



    printf("**********MERGE SORT***********\n");
    GenRandomArray(arr);
    printf("Original Array:\n");
    PrintArray(arr);
    MergeSort(arr, 0, MAX-1);
    printf("After Merge Sort:\n");
    PrintArray(arr);



    printf("**********QUICK SORT**************\n");
    //Using First Element As Pivot
    GenRandomArray(arr);
    printf("Original Array:\n");
    PrintArray(arr);
    QuickSort(arr, 0, MAX-1);
    printf("After Quick Sort:\n");
    PrintArray(arr);


    printf("**********HEAP SORT****************\n");
    GenRandomArray(arr);
    printf("Original Array:\n");
    PrintArray(arr);
    HeapSort(arr, MAX);
    printf("After Heap Sort:\n");
    PrintArray(arr);






    return 0;



}