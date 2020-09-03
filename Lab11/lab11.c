#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEL -1

typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode{
    int Element;
};

struct HashTbl{
    int TableSize;
    List* TheLists;
};

FILE *input;
FILE *output;
int Find(HashTable H, int value, int solution);

int Hash(int value, int Size, int i, int solution){
    if(solution == 1){
        return (value + i) % Size;
    }
    else{
        return (value + (i * i)) % Size;
    }
}

void Insert(HashTable H, int value, int solution){
    int index, i = 0;
    index = Hash(value, H->TableSize, 0, solution);
    while(H->TheLists[index]->Element != 0 && H->TheLists[index]->Element != value && H->TheLists[index]->Element != DEL){
        i++;
        index = Hash(value, H->TableSize, i, solution);
    }
    
    if(H->TheLists[index]->Element == value) fprintf(output, "Already exists\n");
    else{
        H->TheLists[index]->Element = value;
        fprintf(output, "Inserted %d\n", value);
    }
}

void Delete(HashTable H, int value, int solution){
    int index = Find(H,value, solution);

    if(index == -2) fprintf(output, "%d not exists\n", value);
    else{
        H->TheLists[index]->Element = DEL;
        fprintf(output, "Deleted %d\n", value);
    }
}

int Find(HashTable H, int value, int solution){
    int index, i=0;
    index = Hash(value, H->TableSize, 0, solution);
    while(H->TheLists[index]->Element != 0 && H->TheLists[index]->Element != value){
        i++;
        index = Hash(value, H->TableSize, i, solution);
    }
    if(H->TheLists[index]->Element == 0){
        return -2;
    }
    else{ 
        return index;
    }
}

void printTable(HashTable H){
    for(int i=0; i<H->TableSize; i++){
        if(H->TheLists[i]->Element == DEL){
            fprintf(output, "0 ");
        }
        else{
            fprintf(output, "%d ", H->TheLists[i]->Element);
        }
    }
}


int main(int argc, char* argv[]){
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "wt");

    char solution[10], command;
    int size, value, sol, find, end =0;
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));

    fscanf(input, "%s", solution);
    if(!strcmp(solution, "Linear")) sol = 1;
    else sol = 2;
    
    fscanf(input, "%d", &size);
    H->TableSize = size;
    H->TheLists = (List*)malloc(sizeof(List) * H->TableSize);
    for(int i=0; i<H->TableSize; i++){
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        H->TheLists[i]->Element = 0;
    }

    while(end == 0){
        fscanf(input,"%c", &command);
        if(feof(input)) break;

        switch(command){
            case 'i':
                fscanf(input, "%d", &value);
                Insert(H, value, sol);
                break;

            case 'd':
                fscanf(input, "%d", &value);
                Delete(H, value, sol);
                break;

            case 'f':
                fscanf(input, "%d", &value);
                find = Find(H, value, sol);
                if(find == -2) fprintf(output, "Not found\n");
                else fprintf(output, "index: %d\n", find);
                break;

            case 'p':
                printTable(H);
                break;
        }
    }
    for(int i=0; i<H->TableSize; i++){
        free(H->TheLists[i]);
    }
    free(H->TheLists);
    free(H);
    fclose(input);
    fclose(output);
}
