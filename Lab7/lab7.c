#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct _DisjointSet{
    int size_maze;
    int* ptr_arr;
}DisjointSets;


FILE* input;
FILE* output;


void init(DisjointSets *sets, DisjointSets *maze_print, int num){
    sets->size_maze = num * num;
    sets->ptr_arr = (int*)malloc(sizeof(int) * (sets->size_maze+1));
    for(int i = 0; i < sets->size_maze + 1; i++){
        sets->ptr_arr[i] = 0;
    }

    maze_print->size_maze = 2 * num * (num-1);
    maze_print->ptr_arr = (int*)malloc(sizeof(int) * (maze_print->size_maze+1));
    for(int i = 0; i < maze_print->size_maze + 1; i++){
        maze_print->ptr_arr[i] = -1;
    }
}

void union_(DisjointSets *sets, int i, int j){
    if(sets->ptr_arr[j] < sets->ptr_arr[i]){
        sets->ptr_arr[i] = j;
    }
    else{
        if(sets->ptr_arr[j] == sets->ptr_arr[i]){
            sets->ptr_arr[i]--;
        }
        sets->ptr_arr[j] = i;
    }
}

int find(DisjointSets *sets, int i){
    while(1){
        if(sets->ptr_arr[i] <= 0){
            break;
        }
        i = sets->ptr_arr[i];
    }
    return i;
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
    srand((unsigned int)time(NULL));
    int x, tmp1, tmp2, i, j;

    while(1){
        if(find(sets, 1) == find(sets, sets->size_maze)){
            break;
        }
        x = rand() % maze_print->size_maze + 1;

        tmp1 = x / (2*num-1);
        tmp2 = x % (2*num-1);

        if(tmp2 < num && tmp2 > 0){
            i = tmp2 + (tmp1) * num;
            j = i + 1;
        }
        else{
            if(tmp2 == 0){
                i = num * tmp1;
            }
            else{
                i = tmp2 + 1 + num * (tmp1-1);
            }
            j = i + num;            
        }

        i = find(sets, i);
        j = find(sets, j);
        if(i != j){
            union_(sets, i, j);
            maze_print->ptr_arr[x] = 0;
        }
    }
}

void printMaze(DisjointSets *sets, int num){
    int cnt = 1;
    fprintf(output, "+");
    for(int i = 0; i < num; i++){
        fprintf(output, "-+");
    }
    fprintf(output, "\n");

    for(int i = 0; i < (2*num)-1; i++){
        if(cnt == sets->size_maze)
            break;
        if(i % 2 == 0){
            if(i == 0){
                fprintf(output, " ");
            }
            else{
                fprintf(output, "|");
            }
            for(int j = 0; j < num; j++){
                if(j == num-1){
                    if(i != (2*num)-2){
                        fprintf(output, " |");
                    }
                    else{
                        fprintf(output, "  ");
                    }
                }
                else if(sets->ptr_arr[cnt] == -1){
                    fprintf(output, " |");
                    cnt++;
                }
                else{
                    fprintf(output, "  ");
                    cnt++;
                }
            }
        }
        else{
            fprintf(output,"+");
            for(int j = 0; j< num; j++){
                if(sets->ptr_arr[cnt] == -1){
                    fprintf(output, "-+");
                }
                else{
                    fprintf(output, " +");
                }
                cnt++;
            }
        }
        fprintf(output, "\n");
    }
    fprintf(output, "+");
    for(int i = 0; i < num; i++){
        fprintf(output, "-+");
    }
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
    free(sets->ptr_arr);
    free(maze_print->ptr_arr);
    free(sets);
    free(maze_print);
}


int main(int argc, char* argv[]){
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");
    
    DisjointSets *sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    DisjointSets *maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
    int num;

    fscanf(input, "%d", &num);

    init(sets, maze_print, num);
    createMaze(sets, maze_print, num);
    printMaze(maze_print,num);
    freeMaze(sets, maze_print);
}
