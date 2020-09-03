#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
    ElementType element;
    Position next;
};


void Insert(ElementType X, List L, Position P){
   PtrToNode newNode=(PtrToNode)malloc(sizeof(struct Node));
   newNode->element=X;
   
   if(P->next==NULL || P==L){
       newNode->next=P->next;
       P->next=newNode;
   }
   else{
       Position tmp = P->next;
       newNode->next = tmp->next;
       tmp->next = newNode;
   }
}

void PrintList(List L,FILE *output){
    while(L->next!=NULL){
        L=L->next;
        fprintf(output,"key: %d\t",L->element);
    }
}

void Delete(ElementType X, List L,Position P){
    PtrToNode tmp=P->next;
    P->next=tmp->next;
    free(tmp);
}

Position Find(ElementType X, List L){
    while(L->next!=NULL && L->next->element!=X){
        L=L->next;
    }
    if(L->next==NULL){
        return NULL;
    }
    else{
        return L;
    }
}

void DeleteList(List L){
    Position p1;
    Position p2;
    p1=L->next;

    while(p1->next!=NULL){
        p2=p1;
        p1=p1->next;
        free(p2);
    }
    free(p1);
}


int main(int argc, char *argv[]){
    char command;
    int key1, key2;
    FILE *input;
    FILE *output;
    input=fopen(argv[1],"r");
    output=fopen(argv[2],"wt");

    Position header;
    Position tmp;
    header=(PtrToNode)malloc(sizeof(struct Node));
    header->next=NULL;

    while(1){
        command=fgetc(input);
        if(feof(input)) break;
       
        switch(command){
            case 'i':
                fscanf(input,"%d %d",&key1,&key2);
                if(key2 == -1){
                    Insert(key1,header,header);
                }
                else{
                    tmp=Find(key2,header);
                    if(tmp==NULL){
                        fprintf(output,"Insertion(%d) Failed: cannot find the location to be inserted\n",key1);
                    }
                    else{
                        Insert(key1,header,tmp);
                    }
                }
                break;
            case 'd':
                fscanf(input,"%d",&key1);
                tmp=Find(key1,header);
                if(tmp==NULL){
                    fprintf(output,"Dletion(%d) Failed: Element %d is not in the list\n",key1,key1);
                }
                else{
                    Delete(key1,header,tmp);
                }
                break;
            case 'f':
                fscanf(input,"%d",&key1);
                tmp=Find(key1,header);
                if(tmp==NULL){
                    fprintf(output,"Finding(%d) Failed: Element %d is not in the list\n",key1,key1);
                }
                else{
                    if(tmp->element>0){
                        fprintf(output,"Key of the previous node of %d is %d\n",key1,tmp->element);
                    }
                    else{
                        fprintf(output,"Key of the previous node of %d is header\n",key1);
                    }
                }
                break;
            case 'p':
                PrintList(header,output);
                break;
            default:
                break;
        }
    }
    DeleteList(header);
    fclose(input);
    fclose(output);
    return 0;
}
