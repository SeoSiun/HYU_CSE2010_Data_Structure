#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
}Stack;

FILE* fi;
FILE* fo;

void Push(Stack *S,int X){
    if(S->top==9){
        fprintf(fo,"ERROR: Full Stack\n");
    }
    else{
        S->top++;
        S->key[S->top] = X;
    }
}

int Pop(Stack *S){
    if(S->top==-1){
        fprintf(fo,"ERROR: Empty Stack\n");
        return 0;
    }
    else{
        int r = S->key[S->top];
        S->top--;
        return r;
    }
}

int Postfix(Stack* S, char input_str){
    int a = 0, b = 0, r = 0;

    if(isdigit(input_str)){
        const char *str = &input_str;
        r = atoi(str);
    }
    else{
        a = Pop(S);
        b = Pop(S);
        switch(input_str){
            case '+':
                r = b+a;
                break;
            case '-':
                r = b-a;
                break;
            case '*':
                r = b*a;
                break;
            case '/':
                r = b/a;
                break;
            case '%':
                r = b%a;
                break;
        }
    }
    Push(S,r);
    fprintf(fo,"%d ",r);
    return r;
}

void DeleteStack(Stack *S){
    S->top=-1;
    free(S->key);
    free(S);
}

Stack* CreateStack(int max){
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(struct Stack));
    S->key = (int*)malloc(sizeof(int)*max);
    S->max_stack_size = max;
    S->top = -1;
    return S;
}

int main(int argc, char* argv[]){
    fi = fopen(argv[1],"r");
    fo = fopen(argv[2],"wt");
    Stack *stack;
    char input_str[101];
    int max, a, b, result;

    fgets(input_str, 101, fi);
    max = 10;
    stack = CreateStack(max);

    fprintf(fo, "Top numbers :");

    for(int i=0; i<strlen(input_str) && input_str[i]!='#' ; i++){
        result = Postfix(stack, input_str[i]);
    }

    fprintf(fo, "\nevaluation result : %d\n",result);
//    fclose(fi);
//    fclose(fo);
//    DeleteStack(stack);
}
