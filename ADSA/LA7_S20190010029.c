#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXV 100
#define MAX 100
#define initial 1
#define visited 2

#define TREE 0
#define BACK 1
#define CROSS 2
#define FORWARD 3

int state[MAX] = {initial};

typedef struct edgenode
{
    int y;
    int weight;
    struct edgenode *next;
} edgenode;

typedef struct
{
    edgenode *edges[MAXV + 1];
    int degree[MAXV + 1];
    int nvertices;
    int nedges;
    bool directed;
} graph;

int stack[100] = {-1};
int matrix[100][100];
int top = 0;

void push(int v)
{
    if (top == (MAX - 1))
    {
        printf("\nStack Overflow\n");
        return;
    }
    
    stack[top] = v;
    top = top + 1;
}
int isEmpty_stack()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

int pop()
{
    int v;
    if (top == -1)
    {
        printf("\nStack Underflow\n");
        exit(1);
    }
    else
    {
        v = stack[top];
        top = top - 1;
        return v;
    }
}

void Initialize_Graph(graph *g, bool directed)
{
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (int i = 0; i <= MAXV; i++)
        g->degree[i] = 0;
    for (int i = 0; i <= MAXV; i++)
        g->edges[i] = NULL;
    for (int i = 0; i < MAXV; i++)
    {
        state[i]=initial;
        for (int j = 0; j < MAXV; j++)
        {
            matrix[i][j] = 0;
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
        matrix[x][y] = 1;
        if(directed==false)
        {
            matrix[y][x]=1;
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

bool processed[MAXV + 1];
bool discovered[MAXV + 1];

int parent[MAXV + 1];
int entry_time[MAXV + 1];
int exit_time[MAXV + 1];
int time;

int Edge_Classification(int x, int y)
{
    if (parent[y] == x)
        return (TREE);
    if (discovered[y] && (parent[y] != x))
        return (BACK);
    if (processed[y] && (entry_time[y] > entry_time[x]))
        return (CROSS);
    if (processed[y] && (entry_time[y] < entry_time[x]))
        return (FORWARD);
    printf("Warning: Self-Loop (%d, %d)\n", x, y);
}

void Process_Vertex_Early(int v)
{
    time = time + 1;
    entry_time[v] = time;
    printf("Entered Vertex %d at Time %d\n", v, entry_time[v]);
}

void Process_Vertex_Late(int v)
{
    time = time + 1;
    exit_time[v] = time;
    printf("Exit Vertex %d At Time %d\n", v, exit_time[v]);
}

void Process_Edge(int x, int y)
{
    int class = Edge_Classification(x, y);

    if (class == BACK)
        printf("Back Edge (%d, %d)\n", x, y);
    else if (class == TREE)
        printf("Tree Edge (%d, %d)\n", x, y);
    else if (class == FORWARD)
        printf("Forward Edge (%d, %d)\n", x, y);
    else if (class == CROSS)
        printf("Cross Edge (%d, %d)\n", x, y);
    else
        printf("Edge (%d, %d) Is Not A Valid Class !\n", x, y);
}

void Initialize_Search(graph *g)
{
    int i;
    time = 0;
    for (int i = 0; i <= g->nvertices; i++)
    {
        processed[i] = discovered[i] = false;
        parent[i] = -1;
    }
}

void dfs(graph *g, int v)
{
    edgenode *p;
    int y;
    discovered[v] = true;
    time = time + 1;
    entry_time[v] = time;

    Process_Vertex_Early(v);

    p = g->edges[v];
    while (p != NULL)
    {
        y = p->y;
        if (discovered[y] == false)
        {
            parent[y] = v;
            Process_Edge(v, y);
            dfs(g, y);
        }
        else if (!processed[y] || g->directed)
        {
            Process_Edge(v, y);
        }
        p = p->next;
    }
    Process_Vertex_Late(v);
    time = time + 1;
    exit_time[v] = time;
    processed[v] = true;
}

/*
void dfs_iter(int v)
{
    push(v);
    printf("push: %d\n",stack[top-1]);
    while (top!=-1)
    {
        //printf("Entered\n");
        v = pop();
        if (state[v] == initial)
        {
            printf("%d ", v);
            state[v] = visited;
        }
        for (int i = 0; i <= 100; i++)
        {
            //printf("Entered %d\n",i);
            if (matrix[v][i] == 1 && state[i] == initial)
            {
                push(i);
                printf("stack [%d] %d\n",i,top);
            }
        }
    }
    printf("\n");
}
*/


int main()
{
    graph *g;
    g = (graph *)malloc(sizeof(graph));
    printf("Is it Directed graph ? (Y/N) ");
    char d;
    scanf("%c", &d);
    Read_Graph(g, tolower(d) == 'y' ? true : false);
    Print_Graph(g);
    printf("Enter Vertex TO Start DFS: ");
    int n;
    scanf("%d", &n);
    Initialize_Search(g);
    dfs(g, n);
    for (int i = 0; i < g->nvertices; i++)
    {
        if (processed[i] == false)
        {
            printf("\nFound Disconnected Component !\n");
            time = 0;
            dfs(g, i);
        }
    }

    //Initialize_Search(g);
    //printf("\nPrinting Iterative DFS\n");
    //dfs_iter(n);
    printf("Printing Parents Of Nodes (As dfs From Entered Node Above)\n");
    for (int i = 0; i < g->nvertices; i++)
    {
        printf("|%-4d|", i);
    }
    printf("\n");
    for (int i = 0; i < g->nvertices; i++)
    {
        printf("|%-4d|", parent[i]);
    }
    printf("\n");
}
