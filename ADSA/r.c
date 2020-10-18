#include<stdio.h>
#include<math.h>
#define MAX 1000
int max=0;


int findMax(int arr[][MAX], int rows, int mid) 
{ 
    int max_index = 0; 
    for (int i = 0; i < rows; i++) { 
        if ((max) < arr[i][mid]) { 
            // Saving global maximum and its index 
            // to check its neighbours 
            (max) = arr[i][mid]; 
            max_index = i; 
        } 
    } 
    return max_index; 
} 





int findPeakRec(int arr[][MAX], int rows, int columns, 
                int mid) 
{ 
    // Evaluating maximum of mid column. Note max is 
    // passed by reference. 
    int max_index = findMax(arr, rows, mid); 
  
    // If we are on the first or last column, 
    // max is a peak 
    if (mid == 0 || mid == columns - 1) 
        return max; 
  
    // If mid column maximum is also peak 
    if (max >= arr[max_index][mid - 1] && max >= arr[max_index][mid + 1]) 
        return max; 
  
    // If max is less than its left 
    if (max < arr[max_index][mid - 1]) 
        return findPeakRec(arr, rows, columns, mid - ceil((double)mid / 2)); 
  
    // If max is less than its left 
    // if (max < arr[max_index][mid+1]) 
    return findPeakRec(arr, rows, columns, mid + ceil((double)mid / 2)); 
} 
  
// A wrapper over findPeakRec() 
int MinimumArray(int arr[][MAX], int rows, int columns) 
{ 
    return findPeakRec(arr, rows, columns, columns / 2); 
} 
  


int main()
{
    int n;
    printf("Enter Size Of Matrix: ");
   scanf("%d",&n);
   int G[n][n];
   printf("Enter Matrix: \n");
   for(int i=0;i<n;i++)
   {
       for(int j=0;j<n;j++)
       {
           scanf("%d",&G[i][j]);
       }
   }

   for(int i=0;i<n;i++)
   {
       for(int j=0;j<n;j++)
       {
           printf("%d ",G[i][j]);
       }
       printf("\n");
   }

  
   printf("Local Max Of Array Is: %d\n",n==1?G[0][0]:MinimumArray(G, n, n));
}  