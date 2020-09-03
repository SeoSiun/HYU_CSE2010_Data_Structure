#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 999999

typedef struct Node{
    int vertex;
    int dist;
    int prev;
}Node;

typedef struct Graph{
    int size;
    int** vertices;
    Node* nodes;
}Graph;

typedef struct Heap{
    int Capacity;
    int Size;
    Node* Element;
}Heap;

FILE* fi;
FILE* fo;

Graph* CreateGraph(int size){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->size = size;
    g->vertices = (int**)malloc(sizeof(int*) * g->size);
    for(int i=0; i<g->size; i++){
        g->vertices[i] = (int*)malloc(sizeof(int) * g->size);
    }
    for(int i=0; i<g->size; i++){
        for(int j=0; j<g->size; j++){
            g->vertices[i][j] = INF;
        }
    }
    g->nodes = (Node*)malloc(sizeof(Node) * g->size);
    g->nodes[1].dist = 0;
    for(int i=2; i<g->size; i++){
        g->nodes[i].dist = INF;
    }
    for(int i=1; i<g->size; i++){
        g->nodes[i].vertex = i;
    }
    return g;
}

Heap* createMinHeap(int heapSize){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->Capacity = heapSize+1;
    h->Size = 0;
    h->Element = (Node*)malloc(sizeof(Node) * h->Capacity);
    return h;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance){
    int i;
    if(minHeap->Size == minHeap->Capacity-1){
        fprintf(fo, "Insert Error : heap is full\n");
        return;
    }
    for(i=1; i<minHeap->Size; i++){
        if(minHeap->Element[i].vertex == vertex){
            fprintf(fo, "%d is already in the heap\n", vertex);
            return;
        }
    }

    minHeap->Size++;
    if(minHeap->Size == 1){
        minHeap->Element[1].vertex = vertex;
        minHeap->Element[1].dist = distance;
        return;
    }
    for(i = minHeap->Size; minHeap->Element[i/2].dist < distance && i/2!=0; i/=2){
        minHeap->Element[i] = minHeap->Element[i/2];
    }
    minHeap->Element[i].vertex = vertex;
    minHeap->Element[i].dist = distance;
}

Node deleteMin(Heap* minHeap){
    if(minHeap->Size == 0){
        fprintf(fo, "Delete Error : heap is empty\n");
        Node tmp;
        tmp.vertex = 0;
        tmp.dist = INF;
        return tmp;
    }

    int i, child;
    Node min_element = minHeap->Element[1];
    Node last_element = minHeap->Element[minHeap->Size--];

    for(i=1; i*2 <= minHeap->Size; i=child){
        child = i*2;
        if(child < minHeap->Size && minHeap->Element[child+1].dist < minHeap->Element[child].dist){
            child++;
        }
        if(last_element.dist > minHeap->Element[child].dist){
            minHeap->Element[i] = minHeap->Element[child];
        }
        else{ 
            break;
        }
    }
    minHeap->Element[i] = last_element;
    return min_element;
}

void printShortestPath(Graph* g){
    Heap* minHeap = createMinHeap(g->size);
    Node min;
    int* isMin = (int*)malloc(sizeof(int) * g->size);
    int cnt, tmp;
    int toPrint[100];

    for(int i=1; i<g->size; i++){
        if(g->vertices[1][i] != INF){
            g->nodes[i].dist = g->vertices[1][i];
            g->nodes[i].prev = 1;
            isMin[i] = 1;
            insertToMinHeap(minHeap, i, g->vertices[1][i]);
        }
        else isMin[i] = 0;
    }
    while(minHeap->Size != 0){
        min = deleteMin(minHeap);
        for(int i=1; i<g->size; i++){
            if(g->vertices[min.vertex][i] != INF){
                if(g->nodes[i].dist > g->vertices[min.vertex][i] + min.dist){
                    g->nodes[i].dist = g->vertices[min.vertex][i] + min.dist;
                    g->nodes[i].prev = min.vertex;
                }
            }
        }
    }
    for(int i=1; i<g->size; i++){
        if(isMin[i] == 0){
            for(int j=1; j<g->size; j++){
                if(g->vertices[i][j] != INF){
                    if(g->nodes[j].dist > g->vertices[i][j] + g->nodes[i].dist){
                        g->nodes[j].dist = g->vertices[i][j] + g->nodes[i].dist;
                        g->nodes[j].prev = i;
                    }
                }
            }
        }
    }
    for(int i=2; i<g->size; i++){
        if(g->nodes[i].dist == INF){
            fprintf(fo,"Cannot reach to node %d.\n",g->nodes[i].vertex);
        }
        else{
            cnt = 0;
            tmp = i;
            while(g->nodes[tmp].vertex != 1){
                cnt++;
                tmp = g->nodes[tmp].prev;
            }
            fprintf(fo,"1");
            tmp=i;
            cnt=0;
            while(g->nodes[tmp].vertex != 1){
                toPrint[cnt] = g->nodes[tmp].vertex;
                cnt++;
                tmp = g->nodes[tmp].prev;
            }
            for(int j =cnt-1; j>=0; j--){
                fprintf(fo,"->%d",toPrint[j]);
            }
            fprintf(fo," (cost: %d)\n", g->nodes[i].dist);
        }
    }
    free(isMin);
    free(minHeap->Element);
    free(minHeap);
}


void main(int argc, char* argv[]){
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    Graph* g;
    int size;

    fscanf(fi, "%d\n", &size);
    g = CreateGraph(size+1);
    char temp = 0;
    while(temp != EOF){
        int node1, node2, weight;
        fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
        g->vertices[node1][node2] = weight;
        temp = fgetc(fi);
    }
    printShortestPath(g);

    for(int i=0; i<g->size; i++){
        free(g->vertices[i]);
    }
    free(g->vertices);
    free(g->nodes);
    free(g);
    fclose(fi);
    fclose(fo);
}
