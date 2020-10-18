
// C program to search an element in row-wise 
// and column-wise sorted matrix 
#include <stdio.h> 
  
/* Searches the element x in mat[][]. If the  
element is found, then prints its position  
and returns true, otherwise prints "not found" 
and returns false */
int search(int mat[4][4], int n) 
{ 
    if (n == 0) 
        return -1; 
    int i = 0, j = n - 1; // set indexes for top right element 
    while (i < n && j >= 0) { 
        if (mat[i][j]<mat[i+1][j] && mat[i-1][j]>mat[i][j] && mat[i][j-1]>mat[i][j] && mat[i][j]<mat[i][j+1]) { 
            printf("\nFound  %d\n", mat[i][j]); 
            return 1; 
        } 
        else if (mat[i][j] > mat[i][j-1]) 
            j--; 
        else // if mat[i][j] < x 
            i++; 
    } 
  
    return 0; 
} 
  
// driver program to test above function 
int main() 
{ 
    int mat[4][4] = { 
        { 100, -2, 30, 40 }, 
        { 15, -1, 1, -3 }, 
        { 27, 29, 37, 48 }, 
        { 32, 33, 39, 50 }, 
    }; 
    search(mat, 4); 
    return 0; 
}