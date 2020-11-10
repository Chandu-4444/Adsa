#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY INT_MAX

typedef struct Edgenode {
  int key;
  int weight;
  char flight[20];
  int Departure;
  int Arrival;
  struct Edgenode *next;
} Edgenode;

Edgenode *NewEdgeNode(int x, int z, char name[], int Departure, int Arrival) {
  Edgenode *Node = (Edgenode *)malloc(sizeof(Edgenode));
  Node->key = x;
  Node->weight = z;
  strcpy(Node->flight, name);
  //strcpy(Node->departure, Arrival);
  Node->Departure = Departure;
  //strcpy(Node->arrival, Departure);
  Node->Arrival = Arrival;
  Node->next = NULL;
  return Node;
}


int FindMinimum(int NCities, int Price[], int visited[]) {
  int min = INFINITY;
  int index;
  for (int i = 0; i < NCities; i++) {
    if (visited[i] == 0 && Price[i] <= min) {
      min = Price[i];
      index = i;
    }
  }
  return index;
}

void InsertEdge(Edgenode *Graph[], int NCities, int x, int y, char name[],
            int Arrival, int Departure, int z) {
  if (x > NCities) {
    printf("Invalid Vertex! \n");
    return;
  }
  Edgenode *prev = Graph[x];
  Edgenode *p = Graph[x]->next;
  while (p != NULL) {
    prev = p;
    p = p->next;
  }
  prev->next = NewEdgeNode(y, z, name, Arrival, Departure);
}


int ChangeTime(int Arrival, int Departure) {
  int Minutes = Arrival % 100;
  int Hours = Arrival / 100;
  Minutes = Minutes + Departure;
  if (Minutes > 60) {
    Minutes = Minutes % 60;
    Hours += 1;
  }
  if (Hours > 23) {
    Hours = Hours % 23;
  }
  return (Hours * 100 + Minutes);
}

void CheapestTripPlanner(Edgenode *Graph[], int NCities, int s, int d, int dep,
                  int arr) {
  int visited[NCities];
  int Price[NCities];
  int time[NCities];
  for (int i = 0; i < NCities; i++) {
    visited[i] = 0;
    Price[i] = INFINITY;
    time[i] = 2400;
  }
  Price[s] = 0;
  time[s] = dep;

  for (int i = 0; i < NCities; i++) {
    int u = FindMinimum(NCities, Price, visited);
    Edgenode *p = Graph[u]->next;
    visited[u] = 1;
    while (p != NULL) {
      if (visited[p->key] == 0 && time[u] <= p->Departure &&
          p->Arrival <= (arr) &&
          Price[p->key] > Price[u] + p->weight) {
        Price[p->key] = Price[u] + p->weight;
        time[p->key] = ChangeTime(p->Arrival, 30);
      }
      p = p->next;
    }
  }

  if (Price[d] == INFINITY)
    printf("-1\n");
  else
    printf("%d\n", Price[d]);
}

int main() {
  FILE *fp;
  int NCities;
  char FName[100];
  printf("Enter The File: ");
  scanf("%s", FName);
  fp = fopen(FName, "r");
  fscanf(fp, "%d", &NCities);
  Edgenode *Graph[NCities];
  for (int i = 0; i < NCities; i++)
  {
    Graph[i] = NewEdgeNode(i + 1, 0, "", 0000, 0000);
  }
  int NE;
  char Name[10];
  fscanf(fp, "%d", &NE);
  int x, y, z;
  int Arrival, Departure;
  for (int i = 0; i < NE; i++) {
    fscanf(fp, "%d %d %d %d %s %d", &x, &y, &Arrival, &Departure, Name, &z);
    InsertEdge(Graph, NCities, x - 1, y - 1, Name, Arrival, Departure, z);
  }
  int NQ;//Number of Queries
  fscanf(fp, "%d", &NQ);
  for (int i = 0; i < NQ; i++) {
    fscanf(fp, "%d %d %d %d", &x, &y, &Arrival, &Departure);
    CheapestTripPlanner(Graph, NCities, x - 1, y - 1, Arrival, Departure);
  }

  fclose(fp);
  return 0;
}
