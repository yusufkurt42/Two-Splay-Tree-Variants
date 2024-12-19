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

    // Key lies in the left subTree
    if(key < root->data){
        TOTALCOST++;
        if(root->left == NULL)
            return root; // then key is not in here

        if(key < root->left->data){ // LEFT-LEFT
            TOTALCOST++;
            root->left->left = splayIt(root->left->left,key);
            root = rightRotation(root); // after everything has done, we rotate
            TOTALCOST++;
        }

        else if(key > root->left->data){ //LEFT-RIGHT
            TOTALCOST++;
            root->left->right = splayIt(root->left->right,key);
            if(root->left->right) // Not NULL
                root->left = leftRotation(root->left);
                
        }

        return root->left ? rightRotation(root) : root; // root left is null then return the root
    }
    // RIGHT SUBTREE
    else{
        if(root->right == NULL) return root; // not in tree

        // RIGHT-RIGHT
        if(key > root->right->data){
            TOTALCOST++;
            root->right->right = splayIt(root->right->right,key);
            root = leftRotation(root);
            TOTALCOST++;
        }
        // RIGHT-LEFT
        else if(key < root->right->data){
            TOTALCOST++;
            root->right->left = splayIt(root->right->left,key);
            if(root->right->left) // not null
                root->right = rightRotation(root->right);
        }

        return root->right ? leftRotation(root) : root;
    }
}

Node* CreateANode(int data){
    Node *ptr = malloc(sizeof(Node));
    if(ptr==NULL) perror("Problem in allocation");
    ptr->data = data;
    ptr->count = 0;    
    ptr->left = NULL, ptr->right = NULL;
    return ptr;
}

Node* insert(Node *node,int data){
    // if no root then make one
    // here we should first find the key, if exists no need to create a node.
    if(node == NULL){
        node = CreateANode(data);
    }

    else{
        if(node->data >= data){
            TOTALCOST++;
            if(node->data == data){
                node->count++;
                lin=node;
                return node;
            }
            if(node->left == NULL) node->left = CreateANode(data);
            else insert(node->left,data); 
        }
        else{
            TOTALCOST++;
            if(node->right == NULL) node->right = CreateANode(data);
            else insert(node->right,data);
        }
    }
    return node;
}

void preOrder(Node *ptr){
    if(ptr != NULL){
        printf("%d ",ptr->data);
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

Node* insertAndSplay(Node* root,int key){ // merging 2 functions
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
    fileRead = fopen("input.txt", "r");
    if (fileRead == NULL) {
        printf("Error opening file.\n");
        return 1; /* Exit with error */
    }
    puts("Bismillah\nSplay Tree");

    int input; //&input cause we need pointer, remember.
    while(fscanf(fileRead, "%d,", &input)==1) root = insertAndSplay(root,input);
    
    preOrder(root);
    printf("\nAnd the root is: %d",root->data);
    printf("\nTotal Cost is: %d",TOTALCOST);
    return 0;
}