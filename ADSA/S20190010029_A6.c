#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#define MAX 100000

int DP[MAX+1];
int Denominations[MAX+1];
int DCounter = 0;

void Denomination(int Coins[], int Value, int TotalCoins)
{
    if(Value ==0)
    {
        for(int i=0;i<DCounter ; i++)
        {
            if(Denominations[i]!=-1)
            {
                printf("%d ",Denominations[i]);
            }
        }
        printf("\n");
        return;
    }

    for(int i=0;i<TotalCoins; i++)
    {
        if(Value - Coins[i] >=0 && DP[Value-Coins[i]]+1 ==DP[Value])
        {
            Denominations[DCounter++] = Coins[i];
            Denomination(Coins, Value-Coins[i], TotalCoins);
            break;
        }

    }
}

int CountMin(int Coins[], int Value, int TotalCoins)
{
    if(Value==0)
    {
        DP[0] = 0;
        return 0;
    }

    if(DP[Value]!=-1)
    {
        return DP[Value];
    }

    int Ret = INT_MAX;

    for(int i=0; i<TotalCoins;i++)
    {
        if(Coins[i]<=Value)
        {
            int p = CountMin(Coins, Value-Coins[i], TotalCoins);
            if(p!=INT_MAX)
            {
                Ret = Ret< 1+p ? Ret:(1+p); //Optimal Substructure
            }
        }
    }
    DP[Value] = Ret;
    return DP[Value];

}

void PrintPath(int Path[], int i)
{
    if(i==0)
    {
        return;
    }
    PrintPath(Path, Path[i]);
    printf("%d ",i);
}


void HotelPaths(int Hotels[], int n)
{
   
    int Penalty[n];
    int Path[n];
    memset(Penalty, -1, n);
    memset(Path, -1, n);
    Penalty[0] = 0;
    for(int i=1;i<n;i++)
    {
        Penalty[i] = (200-Hotels[i])*(200-Hotels[i]);
        Path[i] = 0;
        for(int j=0;j<i;j++)
        {
            if(Penalty[i]==-1 || Penalty[j] + pow(200-(Hotels[i]-Hotels[j]), 2) < Penalty[i])
            {
                Penalty[i] = Penalty[j] +pow(200 - (Hotels[i]-Hotels[j]), 2);
                Path[i] = j;
            }
        }

    }
    printf("Minimum Penalty: %d\n", Penalty[n-1]);
    int index = n-1;
    int FinalPath[n];
    for(int i=1;i<n;i++)
    {
        printf("Hotel: %d, Penalty: %d, Path: ", Hotels[i], Penalty[i]);
        PrintPath(Path, i);
        printf("\n");
    }
    


}


int main()
{
    // Question 1
    printf("Coin Denomination\n");
    FILE *fp;
    fp = fopen("Input.txt", "r");
    int n;
    fscanf(fp, "%d",&n);
    int Coins[n];
    for(int i=0;i<n;i++)
    {
        fscanf(fp, "%d", &Coins[i]);
    }
    int t;
    fscanf(fp, "%d", &t);
    while(t--)
    {
        int V;
        fscanf(fp, "%d",&V);
        memset(DP, -1, sizeof(DP));
        memset(Denominations, -1, sizeof(Denominations));
        int IsValid = CountMin(Coins, V, n);
        if(IsValid == INT_MAX)
        {
            printf("The Entered Value Cannot Be Obtained With The Given Coins!\n");
        }
        else 
        {
            Denomination(Coins, V, n);
        }

    }
    fclose(fp);

    // Question 2
    printf("\nHotel Stay Problem\n");
    fp = fopen("Input2.txt", "r");
    fscanf(fp, "%d", &n);
    int Hotels[n];
    for(int i=0;i<n;i++)
    {
        fscanf(fp,"%d", &Hotels[i]);
    }

    HotelPaths(Hotels, n);
    return 0;

        
}