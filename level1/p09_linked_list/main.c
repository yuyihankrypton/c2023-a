#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Link{
    int data;
    struct Link* next;
}Link;
Link* createList(){
    Link* head=(Link*)malloc(sizeof(Link));
    head->next=NULL;
    return head;
}
Link* createNode(int data){
    Link* newNode=(Link*)malloc(sizeof(Link));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}
void printList1(Link* head){
    Link* move=head->next;
    while(move!=NULL){
        printf("%d ",move->data);
        move=move->next;
    }
    printf("\n");
}
void printList2(Link* head){
    Link* move=head;
    while(move->next!=NULL){
        printf("%d ",move->data);
        move=move->next;
    }
    printf("\n");
}
void insertNode(Link* head,int data)
{
    Link* newNode=createNode(data);
    newNode->next=head->next;
    head->next=newNode;
}
Link* reverseList(Link* head){
    Link* new_head=NULL;
    Link* temp=NULL;
    if(head==NULL||head->next==NULL){
        return head;
    }
    while(head!=NULL){
        temp=head;
        //将 temp 从 head 中摘除
        head=head->next;
        //将 temp 插入到 new_head 的头部
        temp->next=new_head;
        new_head=temp;
    }
    return new_head;
}
void find_five(Link* head){
    int num=0,sum=0;
    while(head->next!=NULL){
        num++;
        if(head->data==5){
            if(sum==0||sum==1){
                printf("%d\n",num);
                sum++;
            }
            else{
                break;
            }
        }
    }
    if(sum==0){
        printf("-1\n-1\n");
    }
    else if(sum==1){
        printf("-1\n");
    }
}
int main()
{
    Link* list=createList();
    insertNode(list,3);
    insertNode(list,2);
    insertNode(list,6);
    insertNode(list,5);
    insertNode(list,4);
    insertNode(list,1);
    insertNode(list,5);
    printList1(list);
    Link* new_list=reverseList(list);
    printList2(new_list);
    find_five(new_list);
    return 0;
}