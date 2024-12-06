#include <stdio.h>
#include <math.h>

typedef struct bbstnode bbstnode;

struct bbstnode{
    int data;
    bbstnode* rchild;
    bbstnode* lchild;
};

//method that does both functions of searching and inserting
bbstnode* insearch(int key, bbstnode* node){
    //create new node if current node does not exist
    if(!(node)){
        bbstnode* new=malloc(sizeof(bbstnode));
        if(!(new))return NULL;
        new->data=key;
        new->lchild=NULL;
        new->rchild=NULL;
        return new;
    }

    else if(key=node->data)return node;
    else if(key<node->data)return insearch(key,node->lchild);
    else return insearch(key,node->rchild);     
}

void read(bbstnode* root){
    int i, depth=0;
    while(1){
        for(i=0;i<pow(2,depth);i++){
        





        }
    }
}

int main(){
    double x=pow(2,5);
    printf("%f",x);
}