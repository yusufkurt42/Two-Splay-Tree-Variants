#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    struct node *left,*right;
};
typedef struct node Node;

Node *root;

FILE *fileRead;
// *fileWrite; in case we need

Node* rightRotation(Node* x){
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    return y;
}
Node* leftRotation(Node *x){
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}


Node* splayIt(Node *root,int key){
    if(root == NULL || root->data == key) return root;

    // Key lies in the left subTree
    if(key < root->data){
        if(root->left == NULL)
            return root; // then key is not in here

        if(key < root->left->data){ // LEFT-LEFT
            root->left->left = splayIt(root->left->left,key);
            root = rightRotation(root); // after everything has done, we rotate
        }

        else if(key > root->left->data){ //LEFT-RIGHT
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
            root->right->right = splayIt(root->right->right,key);
            root = leftRotation(root);
        }
        // RIGHT-LEFT
        else if(key < root->right->data){
            root->right->left = splayIt(root->right->left,key);
            if(root->right->left) // not null
                root->right = rightRotation(root->right);
        }

        return root->right ? leftRotation(root) : root;
    }
}


void add(Node *ptr,Node *newPtr){
    if(ptr!=NULL){
        if(newPtr->data < ptr->data){
           if(ptr->left == NULL) ptr->left=newPtr;
           else add(ptr->left,newPtr); 
        }
        else{
           if(ptr->right == NULL) ptr->right=newPtr;
           else add(ptr->right,newPtr);
        }
    }
}

Node* insert(Node *root,int data){
    // if no root then make one
    Node *ptr = malloc(sizeof(Node)), *temp;
    if(ptr==NULL) perror("Problem in allocation");
    ptr->data = data;
    ptr->left = NULL, ptr->right = NULL;

    if(root == NULL) root = ptr; // if there is no root

    else add(root,ptr); // after the root solve it by recursion

    return root;
}

void traverse(Node *ptr){
    if(ptr != NULL){
        traverse(ptr->left);
        printf("%d ",ptr->data);
        traverse(ptr->right);
    }
}

Node* insertAndSplay(Node* root,int key){ // merging 2 functions
    root = insert(root,key);

    return splayIt(root,key);
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
    // fileWrite = fopen("output.txt", "w");
    // || fileWrite == NULL
    if (fileRead == NULL) {
        printf("Error opening file.\n");
        return 1; /* Exit with error */
    }
    puts("Bismillah\nSplay Tree");
    // now lets make a menu:
    int input; //&input cause we need pointer, remember.
    while(fscanf(fileRead, "%d", &input)==1){
        // puts("Yeap");
        root = insertAndSplay(root,input);
    }
    traverse(root);
    printf("\nAnd the root is: %d",root->data);
    return 0;
}

// Alhamdulillah, now we have a splay tree.
