#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 1000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct Graph {
    int numVertices;
    Node** adjLists; 
    int* inDegree;   
} Graph;


typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void topologicalSort(Graph* graph);
Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int isEmpty(Queue* q);

int main() {
    int vertices, src, dest;
    FILE *file = fopen("kahnsc.txt", "r");

    if (!file) {
        printf("Error opening file\n");
        return -1;
    }

    fscanf(file, "%d", &vertices);
    Graph* graph = createGraph(vertices);

    
    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    fclose(file);

    
    topologicalSort(graph);

    return 0;
}

Graph* createGraph(int vertices) {
	int i;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node*)malloc(vertices * sizeof(Node));
    graph->inDegree = (int*)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->inDegree[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    
    graph->inDegree[dest]++;
}

void topologicalSort(Graph* graph) {
	int i;
    Queue* queue = createQueue();
    for (i = 0; i < graph->numVertices; i++) {
        if (graph->inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }

    int countVisited = 0;
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            graph->inDegree[adjVertex]--;
            if (graph->inDegree[adjVertex] == 0) {
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
        countVisited++;
    }

    if (countVisited != graph->numVertices) {
        printf("\nCycle detected in the graph\n");
    }
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

int isEmpty(Queue* q) {
    return q->rear == -1;
}
