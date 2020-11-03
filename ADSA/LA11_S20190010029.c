#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXV 100
#define MAX 100
#define INFINITY INT_MAX

typedef struct edgenode {
  int x, y;
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
  p->x = x;
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

void Print_Graph(Graph *g) {
  edgenode *p;
  printf("Printing Adjacency List\n");
  for (int i = 0; i < g->nvertices; i++) {
    printf("%d: ", i);
    p = g->edges[i];
    while (p != NULL) {
      printf(" %d(%d)", p->y, p->weight);
      p = p->next;
    }
    printf("\n");
  }
}

void Bellman_Ford(Graph *g, int start, int D[]) {
  edgenode *p;
  for (int i = 0; i < g->nvertices; i++) {
    D[i] = INFINITY; 
    // Initializing distance of all vertices to INFINITY
  }
  // Set Distance of start vertex to 0
  D[start] = 0;
  for (int i = 0; i < g->nvertices - 1; i++) {
    for (int j = 0; j < g->nvertices; j++) {
      p = g->edges[j];
      while (p) {
        int u = j; // Can also write int u  = p->x;
        int v = p->y;
        if (D[u] + p->weight < D[v]) {
          D[v] = D[u] + p->weight;
        }
        p = p->next;
      }
    }
  }

  //Check for negative cycles!!
  int flag = 0;
  for (int i = 0; i < g->nvertices; i++) {
    p = g->edges[i];
    while (p) {
      int u = p->x;
      int v = p->y;
      if (D[u] + p->weight < D[v]) {
        printf("*****Graph Contains Negative Cycle!******\n");
        flag = 1;
        break;
      }
      p = p->next;
    }
    if (flag) {
      break;
    }
  }
  if (!flag) {
    printf("Vertex    Distance from Source\n");
    for (int i = 0; i < g->nvertices; i++) {
      printf("%d \t\t %d\n", i, D[i]);
    }
  }
}

int main() {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  printf("Is it Directed Graph ? (Y/N) ");
  char d;
  scanf("%c", &d);
  Read_Graph(g, tolower(d) == 'y' ? true : false);
  Print_Graph(g);
  int n;
  int D[g->nvertices];
  printf("Enter Vertex To Start Bellman-Ford: ");
  scanf("%d", &n);
  Bellman_Ford(g, 0, D);

  return 0;
}