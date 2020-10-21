#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct EdgeNode {
  int src;
  int des;
  int weight;
} EdgeNode;
EdgeNode *EdgeArray[200]; // To store input graph
EdgeNode *mst[200];       // To store mst

typedef struct Heapnode // Structure for Heapnode
{
  int src;
  int des;
  int weight;
} Heapnode;


typedef struct Heap // Heap structure
{
  int currentsize;                 
  int maxsize;                     
  struct Heapnode **edgeHeaparray; 
} Heap;

int V; // no. of vertices
int E; // no. of edges
int start;
int parent[200];
int rank[200];

void Swap(Heapnode **p, Heapnode **q) {
  Heapnode *temp = *p;
  *p = *q;
  *q = temp;
}

Heapnode *NewHeapNode(EdgeNode *q) {
  Heapnode *p;
  p = (Heapnode *)malloc(sizeof(Heapnode));
  p->src = q->src;
  p->des = q->des;
  p->weight = q->weight;
  return (p);
}

void MinHeapify(Heap *h, int Curr) {
  int child; // child node position

  while ((Curr * 2 + 2) <= (h->currentsize)) 
  {
    child = Curr * 2 + 1;
    if (child != h->currentsize && (h->edgeHeaparray[child + 1])->weight < (h->edgeHeaparray[child])->weight) // Gives the minimum child of Curr
    {
      child++;
    }

    if ((h->edgeHeaparray[Curr])->weight > (h->edgeHeaparray[child])->weight) // If Heap[Curr] is greater(i.e unfit) than minimum child
    {
      Swap(&h->edgeHeaparray[Curr], &h->edgeHeaparray[child]);
    } else {
      return;
    }
    Curr = child;
  }
}

Heap *BuildHeap(int maxsize) {
  Heap *h = (Heap *)malloc(sizeof(Heap));
  h->currentsize = 0;
  h->maxsize = maxsize;
  h->edgeHeaparray = (Heapnode **)malloc(maxsize * sizeof(Heapnode *));
  for (int i = 0; i < E; i++) {
    h->edgeHeaparray[i] = NewHeapNode(EdgeArray[i]);
    h->currentsize++;
  }

  for (int i = (E - 1) / 2; i >= 0; i--) {
    MinHeapify(h, i); // MinHeapify at all node having child staring form bottom
  }

  return (h);
}

EdgeNode *NewEdgeNode(int src, int des, int weight)
{
EdgeNode *p;
p = (EdgeNode *)malloc(sizeof(EdgeNode));
p->src = src;
p->des = des;
p->weight = weight;
// p->next = NULL;
return (p);
}

void MakeSet(int u) {
  parent[u] = u;
  rank[u] = 0;
}

int Find(int u) {
  if (parent[u] != u) {
    u = parent[u];
    parent[u] = Find(u);
  }
  return (u);
}

int Union(int u, int v) {
  int x, y;
  x = Find(u);
  y = Find(v);
  // printf("x = %d,y = %d\n", x, y);
  if (x == y) {
    return (0);
  }
  if (rank[x] > rank[y]) {
    parent[y] = x;
  } else if (rank[x] < rank[y]) {
    parent[x] = y;
  } else // when both rank equal
  {
    parent[y] = x;
    rank[x]++;
  }
  return (1);
}

Heapnode *ExtractMin(Heap *h) {
  Heapnode *minHeapnode, *lastHeapnode;
  minHeapnode = h->edgeHeaparray[0]; // Topmost node is the minimum
  lastHeapnode =
      h->edgeHeaparray[h->currentsize - 1]; // Last node i.e currentsize-1(since
                                            // Heap starting with 0)
  h->edgeHeaparray[0] = lastHeapnode;
  h->currentsize--; // Reducing the currentsize

  MinHeapify(h, 0);
  return (minHeapnode);
}

void kruskal() {
  int i, u;
  Heap *h = BuildHeap(E); // Building Heap with 0 element adding then node 1 by
                          // 1 by copying form EdgeNode
  for (i = 0; i < V; i++) // MakeSet for all vertices
    MakeSet(i);
  int e = 1;
  while (e < V) // ExtractMin AND Union until we didn't get V-1 edges in MST
  {
    Heapnode *p = ExtractMin(h);

    if (Union(p->src, p->des) == 1) {
      mst[e - 1] = NewEdgeNode(p->src, p->des, p->weight);
      e++;
    }
  }
}

void Init() {
  int i;
  for (i = 0; i < V; i++) {
    EdgeArray[i] = NULL;
  }
}

void AddEdge(int i, int src, int des, int weight) {
  EdgeArray[i] = NewEdgeNode(src, des, weight);
}

void ReadGraph() {
  int u, v, weight;
  int success, r, w;
  int i = 0;
  printf("\nEnter Number Of Vertices And Edges: ");
  scanf("%d %d", &V, &E);
  printf("Start Entering Edges And Edge Weight: \n");
  for (i = 0; i < E; i++) {
    scanf("%d", &u);
    scanf("%d", &v);
    scanf("%d", &weight);
    // printf("%d %d %d\n",u,v,weight);
    AddEdge(i, u, v, weight);
  }
}



int main() {
  Init();
  ReadGraph();
  kruskal();

  printf("\n\nMST IS: \n");
  int weightsum = 0;
  for (int i = 0; i < V - 1; i++) {
    weightsum = weightsum + mst[i]->weight;
    printf("Edge = (%d,%d)->Edge Weight = %d \n", mst[i]->src, mst[i]->des,mst[i]->weight);
  }
  printf("\nTotal Weight is: %d\n", weightsum);
  return 0;
}
