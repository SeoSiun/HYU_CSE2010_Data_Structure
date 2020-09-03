#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct _Queue* Queue;

struct _Queue{
    int* key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

typedef struct _Graph* Graph;

struct _Graph{
    int* node;
    int size;
    int** matrix;
};

FILE* input;
FILE* output;


Graph CreateGraph(int* nodes){
    Graph G = (Graph)malloc(sizeof(struct _Graph));
    G->node = nodes;
    int cnt=0;
    for(int i=0; i<malloc_usable_size(nodes)/sizeof(int); i++){
        if(nodes[i] ==0) break;
        cnt++;
    }
    G->size = cnt;
    G->matrix = (int**)malloc(sizeof(int*) * G->size);

    for(int i=0; i<G->size; i++){
        G->matrix[i] = (int*)malloc(sizeof(int) * G->size);
        for(int j=0; j<G->size; j++){
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void InsertEdge(Graph G, int a, int b){
   int i=0, j=0;

   for(i=0; i<G->size; i++){
      if(G->node[i] == a) break;
   }
   for(j=0; j<G->size; j++){
       if(G->node[j] == b) break;
   }
   G->matrix[i][j]++;
}

Queue MakeNewQueue(int X){
    Queue Q = (Queue)malloc(sizeof(struct _Queue));
    Q->max_queue_size = X;
    Q->key = (int*)malloc(sizeof(int) * Q->max_queue_size);
    Q->first = 0;
    Q->rear = -1;
    Q->qsize = 0;
    return Q;
}

void Enqueue(Queue Q, int X){
    if(Q->rear == Q->max_queue_size-1){
        fprintf(output, "Queue is full\n");
        return;
    }
    Q->key[++Q->rear] = X;
    Q->qsize++;
}

int Dequeue(Queue Q){
    if(Q->first > Q->rear){
        fprintf(output, "Queue is empty\n");
        return 0;
    }
    Q->qsize--;
    return Q->key[Q->first++];
}

void TopSort(Graph G){
    Queue Q = MakeNewQueue(G->size);
    int* in_degree = (int*)malloc(sizeof(int)*G->size);
    int dequeueNum;
    int* toEnqueue = (int*)malloc(sizeof(int)*G->size);
    int cnt=0, FindMin;

    fprintf(output, "  ");
    for(int i=0; i<G->size; i++){
        fprintf(output, "%d ",G->node[i]);
    }
    fprintf(output,"\n");

    for(int i=0; i<G->size; i++){
        fprintf(output,"%d",G->node[i]);
        for(int j=0; j<G->size; j++){
            fprintf(output," %d",G->matrix[i][j]);
        }
        fprintf(output,"\n");
    }

    for(int i=0; i<G->size; i++){
        in_degree[i] = 0;
        for(int j=0; j<G->size; j++){
            in_degree[i] += G->matrix[j][i];
        }     
        if(in_degree[i] == 0){
            toEnqueue[cnt] = G->node[i];
            cnt++;
        }
    }
   
    for(int j=0; j<cnt; j++){
        FindMin = toEnqueue[j];
        for(int i=j+1; i<cnt; i++){
            if(FindMin > toEnqueue[i]){
                FindMin = toEnqueue[i];
            }
        }
    
        Enqueue(Q, FindMin);
    }


    fprintf(output,"\n");

    while(Q->qsize != 0){
        cnt=0;
        dequeueNum = Dequeue(Q);
        fprintf(output,"%d ",dequeueNum);
        for(int i=0; i<G->size; i++){
            if(G->node[i] == dequeueNum){
                for(int j=0; j<G->size; j++){
                    if(G->matrix[i][j] == 1 && --in_degree[j]==0){
                        toEnqueue[cnt] = G->node[j];
                        cnt++;
                    }
                }
            }
        }
        for(int j=0; j<cnt; j++){
            FindMin = toEnqueue[j];
            for(int i=j+1; i<cnt; i++){
                if(FindMin > toEnqueue[i]){
                    FindMin = toEnqueue[i];
                }
            }
            Enqueue(Q, FindMin);
        }

    }
    free(Q->key);
    free(Q);
}



int main(int argc, char* argv[]){
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");

    char line[100];
    Graph G;
    int a,b;

    fgets(line, sizeof(line), input);
    int nodeNum = strlen(line)/2;
    int* nodes = (int*)malloc(sizeof(int) * nodeNum);

    for(int i=0; i<nodeNum*2; i++){
        if(i%2 == 0){
            const char* tmp = &line[i];
            nodes[i/2] = atoi(tmp);
        }
    }
    G = CreateGraph(nodes);

    fgets(line, sizeof(line), input);
    for(int i=0; i<strlen(line); i++){
        if(i%4 == 0){
            const char* tmp1 = &line[i];
            a = atoi(tmp1);
        }
        if(i%4 == 2){
            const char* tmp2 = &line[i];
            b = atoi(tmp2);
            InsertEdge(G, a, b);
        }
    }
    TopSort(G);

    for(int i=0; i<G->size; i++){
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G->node);
    free(G);

    fclose(input);
    fclose(output);
}
