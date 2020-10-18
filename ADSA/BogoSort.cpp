
// C++ implementation of Bogo Sort 
#include<bits/stdc++.h> 
#define MAX 10
using namespace std; 
  
// To check if array is sorted or not 
bool isSorted(int a[], int n) 
{ 
    while ( --n > 1 ) 
        if (a[n] < a[n-1]) 
            return false; 
    return true; 
} 
  
// To generate permuatation of the array 
void shuffle(int a[], int n) 
{ 
    for (int i=0; i < n; i++) 
        swap(a[i], a[rand()%(i+1)]); 
} 
  
// Sorts array a[0..n-1] using Bogo sort 
void bogosort(int a[], int n) 
{ 
    // if array is not sorted then shuffle 
    // the array again 
    while ( !isSorted(a, n) ) 
        shuffle(a, n); 
} 
  
// prints the array 
void printArray(int a[], int n) 
{ 
    for (int i=0; i<n; i++) 
        printf("%d ", a[i]); 
    printf("\n"); 
} 


void GenRandomArray(int arr[])
{
    srand(time(0));
    for (int i=0;i<MAX;i++)
    {
        arr[i]=(rand()%(1000-0+1))+0;
    }
}


// Driver code 
int main() 
{ 
    int a[MAX]; 
    GenRandomArray(a);
    //int n = sizeof a/sizeof a[0]; 
    bogosort(a, MAX); 
    printf("Sorted array :\n"); 
    printArray(a,MAX); 
    return 0; 
} 