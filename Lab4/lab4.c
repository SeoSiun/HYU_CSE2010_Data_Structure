#include<stdio.h>
#include<stdlib.h>

FILE* input;
FILE* output;

struct CompleteTree{
    int Size;
    int nodeNum;
    int* Element;
};

typedef struct CompleteTree* Tree;

void Insert(Tree tree, int value){
    tree->nodeNum++;
    tree->Element[tree->nodeNum] = value;
}

void printPreorder(Tree tree, int index){
    if(index<=tree->nodeNum){
        fprintf(output,"%d ",tree->Element[index]);
        printPreorder(tree, index*2);
        printPreorder(tree, index*2+1);
    }
}

void printInorder(Tree tree, int index){
    if(index<=tree->nodeNum){
        printInorder(tree,index*2);
        fprintf(output,"%d ",tree->Element[index]);
        printInorder(tree,index*2+1);
    } 
}

void printPostorder(Tree tree, int index){
    if(index<=tree->nodeNum){
        printPostorder(tree, index*2);
        printPostorder(tree, index*2+1);
        fprintf(output,"%d ",tree->Element[index]);
    }
}

void FreeTree(Tree tree){
    free(tree->Element);
    tree->Size=0;
    tree->nodeNum=0;
}


int main(int argc, char* argv[]){
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");
    Tree tree;
    int max, num;

    fscanf(input,"%d",&max);
    tree = (Tree)malloc(sizeof(struct CompleteTree));
    tree->Size = max;
    tree->nodeNum = 0;
    tree->Element = (int*)malloc(sizeof(int)*(max+1));

    while(1){
        fscanf(input, "%d", &num);
        if(feof(input)) break;    
        if(tree->nodeNum>=tree->Size){
        fprintf(output,"Error! Tree is FULL.\n");
        break;
        }
        Insert(tree,num);
    }
    
    fprintf(output,"Preorder : ");
    printPreorder(tree,1);

    fprintf(output,"\nInorder : ");
    printInorder(tree,1);
    
    fprintf(output,"\nPostorder : ");
    printPostorder(tree,1);

    FreeTree(tree);
}
