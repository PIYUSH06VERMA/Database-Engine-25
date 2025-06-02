#include<stdbool.h>
#include<stdio.h>
typedef struct keyValuePair{
    int key;
    char* value;
} pair;

typedef struct node{
    int numofvals;
    pair data[4];
    struct node* ptrs[5];
    bool is_leaf;
} Node;

typedef struct queuenode{
    Node* data;
    struct queue* next;
} queueNode;

typedef struct queue{
    queueNode* front,*rear; 
}queue;

queue* createqueue(){
    queue* q=(queue*)malloc(sizeof(queue));
    q->front=NULL;
    q->rear=NULL;
    return q;
}

void enqueue(queue* q,Node* node)
{
    queueNode* temp=(queueNode*)malloc(sizeof(queueNode));
    temp->data=node;
    temp->next=NULL;

    if(q->rear==NULL)
    {
        q->front=q->rear=temp;
        return;
    }
    q->rear->next=temp;
    q->rear=temp;
}
Node* dequeue(queue* q)
{
    if(q->front==NULL) return NULL;
    queueNode* temp=q->front;
    q->front=q->front->next;
    if(q->front==NULL) q->rear=NULL;
    Node* node=temp->data;
    free(temp);
    return node;
}
bool isempty(queue* q)
{
    return q->front==NULL;
}

void print(Node* root)
{
    if(root==NULL) return;
    queue* q=createqueue();
    enqueue(q,root);
    while(!isempty(q))
    {
        Node* curr=dequeue(q);
        printf("[");
        for(int i=0;i<curr->numofvals;i++){
            printf("[%d %s]",curr->data[i].key,curr->data[i].value);
        }
        printf("]\n");
        for(int i=0;i<=curr->numofvals;i++)
        {
            if(curr->ptrs[i]!=NULL) enqueue(q,curr->ptrs[i]);       
        }
    }
}

