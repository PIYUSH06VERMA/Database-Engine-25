#include<stdio.h>
#include "structure.c"
#include "operations.c"

int main()
{
    int q;
    printf("WELCOME, press 1 for insertion,2 for deletion, 3 for serch, 4 for print, 5 for exit\n");
    Node* head=create_node(true);
    while(1)
    {
        scanf("%d",&q);
        if(q==1){
            int k;scanf("%d",&k);
            char* val; scanf("%s",val);
            insert(&head,k,val);
        }
        else if(q==2)
        {

        }
        else if(q==3)
        {
            int k;scanf("%d",&k);
            if(search(k,head)) printf("FOUND\n");
            else printf("NOT FOUND");
        }
        else if(q==4){
            print(head);
        }
        else if(q==5) break;
    }
}