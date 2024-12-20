#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    int count;
    struct node *left,*right;
};
typedef struct node Node;

Node *root;
Node *lin;
int TOTALCOST;

FILE *fileRead;

Node* rightRotation(Node* x){
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    TOTALCOST++;
    return y;
}

Node* leftRotation(Node *x){
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    TOTALCOST++;
    return y;
}

Node* splayIt(Node *root,int key){
    if(root == NULL || root->data == key) return root;

    /*LEFT SUBTREE*/
    if(key < root->data){
        TOTALCOST++;

        if(root->left == NULL) return root; /*then key is not in here*/

        if(key < root->left->data){ /*LEFT-LEFT*/
            TOTALCOST++;
            root->left->left = splayIt(root->left->left,key);
            root = rightRotation(root); /*after everything has done, we rotate*/
            
        }
        else if(key > root->left->data){ /*LEFT-RIGHT*/
            TOTALCOST++;
            root->left->right = splayIt(root->left->right,key);
            if(root->left->right) root->left = leftRotation(root->left);
        }
        return root->left ? rightRotation(root) : root; /*root left is null then return the root*/ 
    }
    /*RIGHT SUBTREE*/
    else{
        if(root->right == NULL) return root; /*not in tree*/

        /*RIGHT-RIGHT*/
        if(key > root->right->data){
            TOTALCOST++;
            root->right->right = splayIt(root->right->right,key);
            root = leftRotation(root);
            
        }
        /*RIGHT-LEFT*/
        else if(key < root->right->data){
            TOTALCOST++;
            root->right->left = splayIt(root->right->left,key);
            if(root->right->left) /*not null*/
                root->right = rightRotation(root->right);
        }
        return root->right ? leftRotation(root) : root;
    }
}

Node* CreateANode(int data){
    Node *ptr = malloc(sizeof(Node));
    if(ptr==NULL) perror("Problem in allocation");
    ptr->data = data;
    ptr->count=0;    
    ptr->left = NULL, ptr->right = NULL;
    return ptr;
}

Node* insert(Node *root,int data){
    // if no root then make one
    // here we should first find the key, if exists no need to create a node.
    if(root == NULL){
        root = CreateANode(data);
    }

    else{
        if(root->data >= data){
            if(root->data == data){
                TOTALCOST++;
                return root;
            }
            if(root->left == NULL) root->left = CreateANode(data);
            else insert(root->left,data); 
        }
        else{
            TOTALCOST++;
            if(root->right == NULL) root->right = CreateANode(data);
            else insert(root->right,data);
        }
    }
    return root;
}

void preOrder(Node *ptr,FILE* output){
    if(ptr != NULL){
        fprintf(output,"%d ",ptr->data);
        preOrder(ptr->left, output);
        preOrder(ptr->right, output);
    }
}

void preOrderModSplay(Node *ptr,FILE* output){
    if(ptr != NULL){
        fprintf(output,"(%d,%d) ",ptr->data,ptr->count);
        preOrderModSplay(ptr->left, output);
        preOrderModSplay(ptr->right, output);
    }
}

Node* insertAndSplay(Node* root,int key){ /*merging 2 functions*/
    root = insert(root,key);

    return splayIt(root,key);
}

Node* insertAndModSplay(Node* root,int key){ /*merging 2 functions for mod splay*/
    root = insert(root,key);
    if(lin!=NULL && lin->count > root->count){
        return splayIt(root,key);
    }
    return root;
}

void freeTree(Node *ptr){
    if(ptr != NULL){
        freeTree(ptr->left);
        freeTree(ptr->right);
        free(ptr);
    }
}

int main(){
    FILE *output=fopen("output.txt","w");

    fileRead = fopen("input.txt", "r");
    if (fileRead == NULL) {
        printf("Error opening file.\n");
        return 1; /* Exit with error */
    }

    int input; 
    while(fscanf(fileRead, "%d,", &input)==1) root = insertAndSplay(root,input);
    fclose(fileRead);
    fprintf(output,"preOrder: ");    
    preOrder(root,output);
    fprintf(output,"\ntotal cost: %d\n\n",TOTALCOST);
    freeTree(root);
    

    fileRead = fopen("input.txt", "r");
    if (fileRead == NULL) {
        printf("Error opening file.\n");
        return 1; /* Exit with error */
    }
    root=NULL;
    lin=NULL;
    TOTALCOST=0;
    input=0;
    
    fprintf(output,"preOrderModSplay: ");


     
    while(fscanf(fileRead, "%d,", &input)==1) root = insertAndModSplay(root,input);
    
    preOrderModSplay(root,output);
    fprintf(output,"\ntotal cost: %d",TOTALCOST);
    fclose(output);
    return 0;
}
