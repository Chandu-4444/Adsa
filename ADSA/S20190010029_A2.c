#include <stdio.h>
#include <math.h>
#define min(a, b) a > b ? b : a
#define MAX 10000

struct Interval
{
    int start;
    int end;
};

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Sort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        Swap(&arr[i], &arr[minIndex]);
    }
}

int findMinimum(int arr[], int l, int r)
{
    if (l == r)
    {
        return arr[l];
    }
    return min(findMinimum(arr, l, (l + r) / 2), findMinimum(arr, (l + r) / 2 + 1, r));
}

void Merge(struct Interval arr[], int left, int middle, int right)
{
    int l = middle - left + 1;
    int r = right - middle;
    struct Interval LArr[l], RArr[r];

    for (int i = 0; i < l; i++)
    {
        LArr[i] = arr[left + i];
    }
    for (int i = 0; i < r; i++)
    {
        RArr[i] = arr[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < l && j < r)
    {
        if (LArr[i].end <= RArr[j].end)
        {
            arr[k++] = LArr[i++];
        }
        else
        {
            arr[k++] = RArr[j++];
        }
    }

    while (i < l)
    {
        arr[k++] = LArr[i++];
    }
    while (j < r)
    {
        arr[k++] = RArr[j++];
    }
}

void MergeSort(struct Interval arr[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        MergeSort(arr, left, middle);
        MergeSort(arr, middle + 1, right);
        Merge(arr, left, middle, right);
    }
}

int MinUtility(int arr[], int low, int high, int n)
{
    int mid = (low + high) / 2;
    if ((mid == 0 || arr[mid - 1] > arr[mid]) && (mid == n - 1 || arr[mid + 1] > arr[mid]))
        return mid;
    else if (mid > 0 && arr[mid - 1] < arr[mid])
        return MinUtility(arr, low, (mid - 1), n);
    return MinUtility(arr, (mid + 1), high, n);
}

int LocalMin(int arr[], int n)
{
    return MinUtility(arr, 0, n - 1, n);
}

int LocMin2D(int n, int mat[n][n])
{
    if (n == 0)
    {
        //printf("\nLocal Minimum Found : %d\n", mat[0][0]);
        return mat[0][0];
    }
    int i = 0, j = n - 1;
    while (i < n && j >= 0)
    {
        if (mat[i][j] < mat[i + 1][j] && mat[i - 1][j] > mat[i][j] && mat[i][j - 1] > mat[i][j] && mat[i][j] < mat[i][j + 1])
        {
            //printf("\nLocal Minimum Found : %d\n", mat[i][j]);
            return mat[i][j];
        }
        else if (mat[i][j] > mat[i][j - 1])
            j--;
        else
            i++;
    }
}

int LocMin2dUti(int n, int arr[n][n])
{
    return LocMin2D(n, arr);
}

int main()
{

    //PROOF OF CORRECTNESS
    int n;
    /*

    printf("Enter The Size Of Array : ");
    scanf("%d", &n);
    int arr1[n];
    printf("Start Entering Elements :\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }
    Sort(arr1, n);
    printf("Array After Sorting :\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arr1[i]);
    }
    */

    //NEW FRIENDS
    //(a)

    printf("\nEnter Number Of Intervals : ");
    scanf("%d", &n);
    struct Interval arr[n];
    int cou = 0;
    printf("Start Entering Start And End Times :\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }
    //printf("Pair of Conflicting Events Are :\n");
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (arr[i].start <= arr[j].start && arr[j].start <= arr[i].end && i != j)
            {
                ++cou;
            }
        }
    }
    printf("Total Conflicts Are: %d\n", cou);

    //(b)
    cou = 0;
    MergeSort(arr, 0, n - 1);
    printf("After Sorting :\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", arr[i].start, arr[i].end);
    }
    //printf("Pair Of Conflicting Events are: \n");
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i].start <= arr[i + 1].start && arr[i + 1].start <= arr[i].end )
        {
            cou = cou + (i + 1);
        }
    }
    printf("Total conflicts In Sorted Sequence is: %d\n", cou);
    /*

    //NEEDLESSLY COMPLICATING THE ISSUE
    //(c)
    printf("Enter Size Of Array: ");
    scanf("%d", &n);
    printf("Start entering elements in array: \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }
    int min = 100000;
    for (int i = 0; i < n; i++)
    {
        if (arr1[i] < min)
        {
            min = arr1[i];
        }
    }
    printf("Minimun Is: %d\n", min);
    //(d)
    printf("Minimum of Array is: %d\n", findMinimum(arr1, 0, n));

    //4
    //(a) (iv)
    printf("Enter total values: ");
    scanf("%d", &n);
    printf("Enter Array :\n");
    int locminarr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &locminarr[i]);
    }
    printf("Local Minimum is %d\n", locminarr[LocalMin(locminarr, n)]);

    printf("Enter Size Of Matrix: ");
    scanf("%d", &n);
    int G[n][n];
    printf("Enter Matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &G[i][j]);
        }
    }

    printf("The Local Minimum Of Array Is: %d\n", LocMin2D(n, G));
    */
}