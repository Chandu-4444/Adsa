#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node
{
    int key;
    int weight;
    char flight[20];
    char departure[5];
    char arrival[5];
    struct node *next;
}Node;

Node *newNode(int x, int z, char name[], char str1[], char str2[])
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->key=x;
    temp->weight=z;
    strcpy(temp->flight,name);
    strcpy(temp->departure,str1);
    strcpy(temp->arrival,str2);
    temp->next=NULL;
    return temp;
}

void Insert(Node *Graph[],int size,int x,int y,char name[],char str1[],char str2[],int z)
{
    if(x > size)
    {
        printf("Given vertex not present\n");
        return;
    }
    Node *prev=Graph[x];
    Node *curr=Graph[x]->next;
    while(curr!=NULL)
    {
        prev=curr;
        curr=curr->next;
    }
    prev->next=newNode(y,z,name,str1,str2);
}

int minimum(int size,int cost[],int visited[])
{
    int min=100000,index;
    for(int i=0;i<size;i++)
    {
        if(visited[i]==0 && cost[i]<=min)
        {
            min=cost[i];
            index = i;
        }
    }
    return index;
}

int addTime(int str1,int str2)
{
    int mm = str1%100;
    int hh = str1/100;
    mm = mm+str2;
    if(mm>60)
    {
        mm = mm%60;
        hh+=1;
    }
    if(hh>23)
    {
        hh=hh%23;
    }
    return (hh*100+mm);
}

void cheapestTrip(Node*Graph[],int size,int s,int d,char dep[],char arr[])
{
    int visited[size];
    int cost[size];
    int time[size];
    for(int i=0;i<size;i++)
    {
        visited[i]=0;
        cost[i]=100000;
        time[i]=2400;
    }
    cost[s]=0;
    time[s]=atoi(dep);

    for(int i=0;i<size;i++)
    {
        int u = minimum(size,cost,visited);
        Node *curr = Graph[u]->next;
        visited[u]=1;
        while(curr!=NULL)
        {
            if(visited[curr->key]==0 && time[u] <= atoi(curr->departure) && atoi(curr->arrival) <= atoi(arr) && cost[curr->key] > cost[u]+curr->weight)
            {
                cost[curr->key] = cost[u] + curr->weight;
                time[curr->key] = addTime(atoi(curr->arrival),30);
            }
            curr=curr->next;   
        }
    }

	if(cost[d]==100000) printf("-1\n");
	else printf("%d\n",cost[d]);
}

int main()
{
    FILE* fp;
    char s[100];

    printf("Enter the name of the file: ");
    scanf("%s",s);

    fp=fopen(s,"r");

    int size;
    fscanf(fp, "%d", &size);

    Node *Graph[size];
    for(int i=0;i<size;i++)
        Graph[i]=newNode(i+1,0,"","0000","0000");

    int E;
    fscanf(fp,"%d", &E);
    int x,y,z;
    char str1[5],str2[5];
    for(int i=0;i<E;i++)
    {
        fscanf(fp,"%d %d %s %s %s %d",&x,&y,str1,str2,s,&z);
        Insert(Graph,size,x-1,y-1,s,str1,str2,z);
    }

    int Q;
    fscanf(fp, "%d", &Q);
    
    for(int i=0;i<Q;i++)
    {
       fscanf(fp,"%d %d %s %s",&x,&y,str1,str2);
       cheapestTrip(Graph,size,x-1,y-1,str1,str2); 
    }

    fclose(fp);

    return 0;
}
