#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>


#define MAXV 100
#define MAX 100


typedef struct edgenode {
  int y;
  int weight;
  struct edgenode *next;
} edgenode;

typedef struct {
  edgenode *edges[MAXV + 1];
  int degree[MAXV + 1];
  int nvertices;
  int nedges;
  bool directed;
} Graph;


void Initialize_Graph(Graph *g, bool directed) {
  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;

  for (int i = 0; i <= MAXV; i++)
    g->degree[i] = 0;
  for (int i = 0; i <= MAXV; i++)
    g->edges[i] = NULL;
}

void Insert_Edge(Graph *g, int x, int y, int w, bool directed) {
  edgenode *p;
  p = (edgenode *)malloc(sizeof(edgenode));
  p->weight = w;
  p->y = y;
  p->next = g->edges[x];
  g->edges[x] = p;
  g->degree[x]++;

  if (directed == false) {
    Insert_Edge(g, y, x, w, true);
  } else {
    g->nedges++;
  }
}

void Read_Graph(Graph *g, bool directed) {
  int m;
  int x, y, w;
  Initialize_Graph(g, directed);

  printf("Enter Number Of Vertices ANd Number Of Edges: ");
  scanf("%d %d", &(g->nvertices), &m);
  printf("Start Entering Edges and Weight\n");
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &x, &y, &w);

    Insert_Edge(g, x, y, w, directed);
  }
}
 


 
typedef struct HeapNode
{
    int  v;
    int Weight;
}HeapNode;
 
typedef struct Heap
{
     
    int size;     
   
    int capacity;  
   
    int *pos;    
    struct HeapNode **array;
}Heap;

HeapNode* NewHeapNode(int v, 
                                 int Weight)
{
    struct HeapNode* HeapNode =
           (struct HeapNode*) 
      malloc(sizeof(struct HeapNode));
    HeapNode->v = v;
    HeapNode->Weight = Weight;
    return HeapNode;
}
 
Heap* CreateNode(int capacity)
{
    struct Heap* Heap =
         (struct Heap*) 
      malloc(sizeof(struct Heap));
    Heap->pos = (int *)malloc(
            capacity * sizeof(int));
    Heap->size = 0;
    Heap->capacity = capacity;
    Heap->array =
         (struct HeapNode**) 
                 malloc(capacity * 
       sizeof(struct HeapNode*));
    return Heap;
}

void SwapNode(struct HeapNode** a, 
                     struct HeapNode** b)
{
    struct HeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void Heapify(struct Heap* Heap, 
                                  int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < Heap->size &&
        Heap->array[left]->Weight < 
         Heap->array[smallest]->Weight )
      smallest = left;
 
    if (right < Heap->size &&
        Heap->array[right]->Weight <
         Heap->array[smallest]->Weight )
      smallest = right;
 
    if (smallest != idx)
    {
        HeapNode *smallestNode = 
             Heap->array[smallest];
        HeapNode *idxNode = 
                 Heap->array[idx];
 
        Heap->pos[smallestNode->v] = idx;
        Heap->pos[idxNode->v] = smallest;
 
        SwapNode(&Heap->array[smallest], 
                         &Heap->array[idx]);
 
        Heapify(Heap, smallest);
    }
}
 

int IsEmpty(struct Heap* Heap)
{
    return Heap->size == 0;
}
 
struct HeapNode* ExtractMin(struct Heap* 
                                   Heap)
{
    if (IsEmpty(Heap))
        return NULL;
 
    struct HeapNode* root = 
                   Heap->array[0];
 
    struct HeapNode* lastNode = 
         Heap->array[Heap->size - 1];
    Heap->array[0] = lastNode;
 
    Heap->pos[root->v] = Heap->size-1;
    Heap->pos[lastNode->v] = 0;
 
    --Heap->size;
    Heapify(Heap, 0);
 
    return root;
}
 
void ReduceKey(struct Heap* Heap, 
                         int v, int Weight)
{
    int i = Heap->pos[v];
 
    Heap->array[i]->Weight = Weight;

    while (i && Heap->array[i]->Weight < 
           Heap->array[(i - 1) / 2]->Weight)
    {
        Heap->pos[Heap->array[i]->v] = 
                                      (i-1)/2;
        Heap->pos[Heap->array[
                             (i-1)/2]->v] = i;
        SwapNode(&Heap->array[i],  
                 &Heap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
bool IsInHeap(struct Heap *Heap, int v)
{
   if (Heap->pos[v] < Heap->size)
     return true;
   return false;
}
 

 
void Dijkstra(Graph* Graph, int start)
{
    int Weight[Graph->nvertices];     
    struct Heap* Heap = CreateNode(Graph->nvertices);
    for (int i = 0; i < Graph->nvertices; i++)
    {
        Weight[i] = INT_MAX;
        Heap->array[i] = NewHeapNode(i, Weight[i]);
        Heap->pos[i] = i;
    }
 
    Heap->array[start] = NewHeapNode(start, Weight[start]);
    Heap->pos[start]   = start;
    Weight[start] = 0;
    ReduceKey(Heap, start, Weight[start]);
    Heap->size = Graph->nvertices;
    while (!IsEmpty(Heap))
    {
        HeapNode* HeapNode = ExtractMin(Heap);
        int u = HeapNode->v; 
        edgenode* p = Graph->edges[u];
        while (p)
        {
            int v = p->y;
            if (IsInHeap(Heap, v) && Weight[u] != INT_MAX && p->weight + Weight[u] < Weight[v])
            {
                Weight[v] = Weight[u] + p->weight;
                ReduceKey(Heap, v, Weight[v]);
            }
            p = p->next;
        }
    }
    printf("From -> To --- Weight\n");
    for(int i=0;i<Graph->nvertices;i++)
    {
        printf("|%4d -> %2d --- %-4d|\n",start,i, Weight[i]);
    }
 
 
    
    
}
 
 

int main()
{
  Graph *g = (Graph *)malloc(sizeof(Graph));
  printf("Is it Directed Graph ? (Y/N) ");
  char d;
  scanf("%c", &d);
  Read_Graph(g, tolower(d) == 'y' ? true : false);
 printf("Enter Vertex TO Start Dijkstra: ");
  int n;
  scanf("%d", &n);
    Dijkstra(g, 0);
 
    return 0;
}