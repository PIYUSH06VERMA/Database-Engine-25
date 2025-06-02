#include "structure.c"
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
const int T=4;
Node* create_node(bool leaf)
{
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(new_node==NULL)
    {
        printf("Failed to allocate memory");
    }
    new_node->numofvals=0;
    for(int i=0;i<T;i++)
    {
        new_node->data[i].key=-1;
        new_node->data[i].value=NULL;
        new_node->ptrs[i]=NULL;
    }
    new_node->is_leaf=leaf;
    return new_node;
}
void insertnotfull(Node* node,int key,char* val)
{
    if(node->is_leaf)
    {
        int i=node->numofvals-1;
        while(i>=0 && key<node->data[i].key){
            node->data[i+1].key=node->data[i].key;
            strcpy(node->data[i+1].value,node->data[i].value);
            i--;
        }
        node->data[i+1].key=key;
        node->data[i+1].value=val;
        node->numofvals++;
    }
    else{
        int i=node->numofvals-1;
        while(i>=0 && key<node->data[i].key){
            i--;
        }
        i++;


    }
}
void splitchild(Node* parent,int ind)
{
    Node* child=parent->ptrs[ind];
    Node* new_node=create_node(child->is_leaf);// i have created a new node now in this ill shift the elements greater than median

    //as  child is full
    for(int i=0;i<2;i++)
    {
        new_node->data[i].key=child->data[i+2].key;
        strcpy(child->data[i+2].value,new_node->data[i].value);
    }

    if(!child->is_leaf){
        for(int i=0;i<T/2;i++)
        {
            new_node->ptrs[i]=child->ptrs[i+T/2+1];
        }
    }

    child->numofvals=T/2;

    for(int i=parent->numofvals-1;i>=ind+1;i--)
    {
        parent->ptrs[i+1]=parent->ptrs[i];
    }
    parent->ptrs[ind+1]=new_node;

    for(int j=parent->numofvals-1;j>=ind;j--)
    {
        parent->data[j+1].key=parent->data[j].key;
        strcpy(parent->data[j+1].value,parent->data[j].value);
    }
    parent->data[ind].key=child->data[T/2].key;
    strcpy(child->data[T/2].value,parent->data[ind].value);
    parent->numofvals++;
}
void insert(Node** root, int key, char* val) {
    Node* r = *root;
    if (r->numofvals == T) {
        Node* new_root = create_node(false);
        new_root->ptrs[0] = r;
        *root = new_root;
        splitChild(new_root, 0);
        insertNonFull(new_root, key, val);
    } else {
        insertNonFull(r, key, val);
    }
}

bool search(int k,Node* head)
{
    if(head==NULL)
    {
 
        return false;
    }
    for(int i=0;i<4;i++)
    {
        if(head->data[i].key==k)
        {
            return true;
        }
        else if(head->data[i].key>k)
        {
            return search(k,head->ptrs[i]);
        }
    }
    return search(k,head->ptrs[4]);
}




