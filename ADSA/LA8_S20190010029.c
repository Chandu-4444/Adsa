#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

#define MAXV 100
#define QUEUESIZE 100



int Queue[QUEUESIZE]={-1};
int first=-1;
int last=QUEUESIZE-1;

int AdjMat[MAXV][MAXV];


typedef struct edgenode
{
    int y;
    int weight;
    struct edgenode *next;
}edgenode;

typedef struct 
{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
}graph;

void Initialize_Graph(graph *g, bool directed)
{
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (int i = 0; i <= MAXV; i++)
        g->degree[i] = 0;
    for (int i = 0; i <= MAXV; i++)
        g->edges[i] = NULL;
    for(int i=0;i<=MAXV;i++)
    {
        for(int j=0;j<=MAXV;j++)
        {
            AdjMat[i][j] = 0;
        }
    }
}

void Insert_Edge(graph *g, int x, int y, bool directed)
{
    edgenode *p;
    p = (edgenode *)malloc(sizeof(edgenode));
    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];
    g->edges[x] = p;
    g->degree[x]++;
    

    if (directed == false)
    {
        Insert_Edge(g, y, x, true);
    }
    else
    {
        g->nedges++;
    }
}

void Read_Graph(graph *g, bool directed)
{
    int m;
    int x, y;
    Initialize_Graph(g, directed);

    printf("Enter Number Of Vertices ANd Number Of Edges: ");
    scanf("%d %d", &(g->nvertices), &m);
    printf("Start Entering Edges\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        AdjMat[x][y]=1;
        if(directed ==false)
        {
            AdjMat[y][x]=1;
        }
        Insert_Edge(g, x, y, directed);
    }
}

void Print_Graph(graph *g)
{
    edgenode *p;
    printf("Printing Adjacency List\n");
    for (int i = 0; i < g->nvertices; i++)
    {
        printf("%d: ", i);
        p = g->edges[i];
        while (p != NULL)
        {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}

bool processed[MAXV+1];
bool discovered[MAXV+1];
int parent[MAXV];



void Initialize_Search(graph *g)
{
    int i;
    for (int i = 0; i <= g->nvertices; i++)
    {
        processed[i] = discovered[i] = false;
        parent[i] = -1;
    }
}

void BFS(graph *g, int start)
{			
	int v;				
	int y;				
	edgenode *p;			

    Queue[++first] = start;
	discovered[start] = true;
    printf("Entered: %d\n",start);

	while (first>= 0) {
		v = Queue[first--];
        //printf("Dequeue: %d\n",v);
		//processed[v] = true;
		p = g->edges[v];
		while (p) 
        {
		    y = p->y;
		    if (discovered[y] == false) {
			Queue[++first] = y;
			discovered[y] = true;
            printf("Entered: %d\n",y);
			parent[y] = v;
		    }
		    p = p->next;
		}
		
	}
}

void BFSMat(graph *g, int start)
{
    int v;
    Initialize_Search(g);
    Queue[++first] = start;
    discovered[start] = true;
    printf("Entered: %d\n",start);
    while(first>=0)
    {
        v = Queue[first--];
        for(int i=0;i<g->nvertices;i++)
        {
            if(AdjMat[v][i]==1 && discovered[i]==false)
            {
                printf("Entered: %d\n",i);
                Queue[++first] = i;
                discovered[i]=true;
            }
        }
    }

}








int main()
{
    graph *g;
    g = (graph *)malloc(sizeof(graph));
    //printf("Is it Directed graph ? (Y/N) ");
    //char d;
    //scanf("%c", &d);
    //Read_Graph(g, tolower(d) == 'y' ? true : false);
    Read_Graph(g, false);
    Print_Graph(g);
    int n;
    printf("Enter Vertex To Start BFS: ");
    scanf("%d", &n);
    Initialize_Search(g);
    BFS(g, n);
    /*
    for(int i=0;i<g->nvertices;i++)
    {
        printf(" %d",parent[i]);
    }
    */
    printf("BFS For ADJ Matrix: \n");
    BFSMat(g,n);
    printf("\n");
    return 0;
}

