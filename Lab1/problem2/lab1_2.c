#include<stdio.h>
 
int main(){
    
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_2_input.txt","r");
    output_file = fopen("lab1_2_output.txt","wt");
    
    int num;
    int arr[100];
    int max_index=0;
    int tmp=0;
 
    fscanf(input_file,"%d",&num);

    for(int i=0; i<num; i++){
        fscanf(input_file,"%d",&arr[i]);
    }

    for(int i=0; i<num-1; i++){
        max_index=i;
        for(int j=i+1; j<num; j++){
            if(arr[max_index]<arr[j]){
                max_index=j;
            }
        }
        tmp=arr[i];
        arr[i]=arr[max_index];
        arr[max_index]=tmp;
    }

    for(int i=0; i<num; i++){ 
        fprintf(output_file,"%d ",arr[i]);
    }

    return 0;
}
