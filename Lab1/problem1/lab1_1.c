#include<stdio.h>

int main(){
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_1_input.txt","r");
    output_file = fopen("lab1_1_output.txt","wt");

    int num;
    int arr[100];
    int start_i,end_i;
    int result=0;

    fscanf(input_file,"%d",&num);

    for(int i=0; i<num; i++){
        fscanf(input_file,"%d",&arr[i]);
    }

    fscanf(input_file,"%d",&start_i);
    fscanf(input_file,"%d",&end_i);

    for(int i=start_i; i<=end_i; i++){
        result+=arr[i];
    }

    fprintf(output_file,"%d",result);

    return 0;
}
