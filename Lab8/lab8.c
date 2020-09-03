#include<stdio.h>
#include<stdlib.h>


typedef struct HeapStruct{
    int Capacity;
    int Size;
    int *Element;
}Heap;

FILE *input;
FILE *output;

Heap* CreateHeap(int heapSize){
    Heap* tmp = (Heap*)malloc(sizeof(Heap));
    tmp->Capacity = heapSize+1;
    tmp->Size = 0;
    tmp->Element = (int*)malloc(sizeof(int) * tmp->Capacity);
    return tmp;
}

void Insert(Heap *heap, int value){
    int i;
    if(heap->Size == heap->Capacity-1){
        fprintf(output, "Insert Error : heap is full\n");
        return;
    }
    for(i = 1; i <= heap->Size; i++){
        if(heap->Element[i] == value){
            fprintf(output, "%d is already in the heap\n", value);
            return;
        }
    }

    heap->Size++;
    if(heap->Size == 1){
        heap->Element[1] = value;
        fprintf(output, "insert %d\n", value);
        return;
    }
    for(i = heap->Size; heap->Element[i/2] < value && i/2 != 0; i /= 2){
        heap->Element[i] = heap->Element[i/2];
    }
    heap->Element[i] = value;
    fprintf(output, "insert %d\n", value);
}

int Find(Heap *heap, int value){
    for(int i = 1; i <= heap->Size; i++){
        if(heap->Element[i] == value){
            fprintf(output, "%d is in the heap\n", value);
            return i;
        }
    }
    fprintf(output, "%d is not in the heap\n", value);
    return 0;
}

int DeleteMax(Heap *heap){
    if(heap->Size == 0){
        fprintf(output, "Delete Error : heap is empty\n");
        return -1;
    }

    int i, child;
    int max_element = heap->Element[1];
    int last_element = heap->Element[heap->Size--];

    for(i =1; i * 2 <= heap->Size; i = child){
        child = i * 2;
        if(child < heap->Size && heap->Element[child + 1] > heap->Element[child]){
            child++;
        }
        if(last_element < heap->Element[child]){
            heap->Element[i] = heap->Element[child];
        }
        else{
            break;
        }
    }
    heap->Element[i] = last_element;
    return max_element;        
}   

void PrintHeap(Heap *heap){
    if(heap->Size == 0){
        fprintf(output, "Print Error : heap is empty\n");
        return;
    }
    for(int i=1; i <= heap->Size; i++){
        fprintf(output, "%d ", heap->Element[i]);
    }
    fprintf(output, "\n");
}


int main(int argc, char* argv[]){
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");
    char command;
    int x, r;
    Heap* heap;

    while(1){   
        if(feof(input)) break;
        fscanf(input, "%c", &command);
        switch(command){
            case 'n':
                fscanf(input, "%d", &x);
                heap = CreateHeap(x);
                break;

            case 'i':
                fscanf(input, "%d", &x);
                Insert(heap, x);
                break;

            case 'f':
                fscanf(input, "%d", &x);
                Find(heap, x);
                break;

            case 'd':
                r = DeleteMax(heap);
                if(r != -1){
                    fprintf(output, "Max Element : %d deleted\n", r);
                }
                break;

            case 'p':
                PrintHeap(heap);
                break;
        }
    }
    
    fclose(input);
    fclose(output);
    free(heap->Element);
    free(heap);
}

