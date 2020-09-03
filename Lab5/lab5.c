#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
    int value;
    Tree left;
    Tree right;
};

FILE* input;
FILE* output;

Tree findMin(Tree root){
    if(root == NULL){
        return NULL;
    }
    if(root->left == NULL){
        return root;
    }
    return findMin(root->left);
}

Tree insertNode(Tree root, int key){
    if(root == NULL){
        root = (Tree)malloc(sizeof(struct BinarySearchTree));
        root->value = key;
        root->left = NULL;
        root->right = NULL;
    }
    else if(root->value > key){
        root->left = insertNode(root->left, key);
    }
    else if(root->value < key){
        root->right = insertNode(root->right, key);
    }
    else{
        fprintf(output,"Insertion Error: %d already exists\n",key);
    }
    return root;
}

void findNode(Tree root, int key){
    if(root == NULL){
        fprintf(output, "%d is not in the tree\n", key);
    }
    else if(root->value > key){
        findNode(root->left, key);
    }
    else if(root->value < key){
        findNode(root->right, key);
    }
    else{
        fprintf(output, "%d is in the tree\n",key);
    }
}

void printInorder(Tree root){
    if(root){
        printInorder(root->left);
        fprintf(output,"%d ",root->value);
        printInorder(root->right);
    }
}

Tree deleteNode(Tree root,int key){
    Tree tmp;

    if(root == NULL){
        fprintf(output, "Deletion Error: %d does not exist\n",key);
    }
    else if(root->value > key){
        root->left = deleteNode(root->left, key);
    }
    else if(root->value < key){
        root->right = deleteNode(root->right,key);
    }
    else if(root->left && root->right){
        tmp = findMin(root->right);
        root->value = tmp->value;
        root->right = deleteNode(root->right, tmp->value);
    }
    else{
        tmp = root;
        if(root->left == NULL){
            root = root->right;
        }
        else{
            root = root->left;
        }
        free(tmp);
    }
    return root;
}

void deleteTree(Tree root){
    if(root){
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}


int main(int argc, char* argv[]){
    char command;
    int key;
    
    Tree root = NULL;

    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");

    while(1){
        if(feof(input)) break;

        fscanf(input, "%c", &command);

        switch(command){
            case 'i':
                fscanf(input, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'd':
                fscanf(input, "%d", &key);
                root = deleteNode(root,key);
                break;
            case 'f':
                fscanf(input, "%d", &key);
                findNode(root,key);
                break;
            case 'p':
                fscanf(input,"%c",&command);
                if(command=='i'){
                    printInorder(root);
                    fprintf(output,"\n");
                }
                break;
        }
    }
    deleteTree(root);
    return 0;
}
