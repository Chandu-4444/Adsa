#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n,m;
    scanf("%lld %lld",&n,&m);
    long long *arr=new long long[n+1]();
    long long a,b,k;
    for(long long i=1;i<=m;i++)
    {
        scanf("%lld %lld %lld",&a,&b,&k);
        for(long long j=a;j<=b;j++)
        {
            arr[j]=arr[j]+k;
        }
    }
    /*
    for(int i=1;i<=n;i++)
    {
        printf("%ld ",arr[i]);
    }
    printf("\n");
    */
    long long max=-1;
    for(long long i=1;i<=n;i++)
    {
        if(max< arr[i])
        {
            max=arr[i];
        }
    }
    printf("%lld\n",max);
    return 0;

}