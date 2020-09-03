#include<stdio.h>
#include<stdlib.h>

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
struct AVLNode{
    ElementType Element;
    AVLTree left;
    AVLTree right;
    int Height;
};

FILE *input;
FILE *output;


int getHeight(AVLTree T){
    if(T == NULL){
        return -1;
    }
    return T->Height;
}

int max(int x, int y){
    if(x > y) return x;
    return y;
}

Position SingleRotateWithLeft(Position node){
    Position L = node->left;
    node->left = L->right;
    L->right = node;

    node->Height = max(getHeight(node->left),getHeight(node->right)) + 1;
    L->Height = max(getHeight(L->left),getHeight(L->right)) + 1;

    return L;
}

Position SingleRotateWithRight(Position node){
    Position R = node->right;
    node->right = R->left;
    R->left = node;

    node->Height = max(getHeight(node->left),getHeight(node->right)) + 1;
    R->Height = max(getHeight(R->left),getHeight(R->right)) + 1;

    return R;
}

Position DoubleRotateWithLeft(Position node){
    node->left = SingleRotateWithRight(node->left);

    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
    node->right = SingleRotateWithLeft(node->right);

    return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T){
    if(T == NULL){
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Height = 0;
        T->left = NULL;
        T->right = NULL;
    }
    else if(X < T->Element){
        T->left = Insert(X, T->left);
        if(getHeight(T->left)-getHeight(T->right) >=2){
            if(X < T->left->Element){
                T = SingleRotateWithLeft(T);
            }
            else{
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else if(X > T->Element){
        T->right = Insert(X, T->right);
        if(getHeight(T->right)-getHeight(T->left) >=2){
            if(X > T->right->Element){
                T = SingleRotateWithRight(T);
            }
            else{
                T = DoubleRotateWithRight(T);
            }
        }
    }
    else{
        fprintf(output, "[Error] %d already in the tree!\n", X);
    }
    T->Height = max(getHeight(T->left), getHeight(T->right)) + 1;
    return T;
}

void printInorder(AVLTree T){
    if(T){
        printInorder(T->left);
        fprintf(output, "%d(%d) ", T->Element, T->Height);
        printInorder(T->right);
    }
}

void deleteTree(AVLTree T){
    if(T){
        deleteTree(T->left);
        deleteTree(T->right);
        free(T);
    }
}


int main(int argc, char* argv[]){
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"wt");

    AVLTree T = NULL;
    int num;

    while(1){        
        fscanf(input, "%d", &num);
        if(feof(input)) break;

        T = Insert(num, T);
        printInorder(T);
        fprintf(output,"\n");
    }

    deleteTree(T);
    fclose(input);
    fclose(output);
    return 0;
}
