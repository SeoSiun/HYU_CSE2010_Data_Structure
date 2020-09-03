#include<stdio.h>

typedef struct{
    char name[30];
    int id;
}student;

int main(){
    
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_3_input.txt","r");
    output_file = fopen("lab1_3_output.txt","wt");

    student arr[10];
    int num;
    int min_index;
    student tmp;

    fscanf(input_file,"%d",&num);

    for(int i=0; i<num; i++){
        fscanf(input_file,"%s %d",arr[i].name, &arr[i].id);
    }

    for(int i=0; i<num-1; i++){
        min_index=i;
        for(int j=i+1; j<num; j++){
            if(arr[min_index].id>arr[j].id){
                min_index=j;
            }
        }
        tmp=arr[i];
        arr[i]=arr[min_index];
        arr[min_index]=tmp;        
    }
    
    for(int i=0; i<num; i++){
        fprintf(output_file,"%s %d\n",arr[i].name,arr[i].id);
    }

    return 0;
}
