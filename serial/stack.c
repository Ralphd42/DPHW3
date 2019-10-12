 
#include "stackHw.h"
  

int main(int argc, char*argv[])
{
    int retval =0;
    return retval;
}   


long long GetStackCount(){
    long long retval=0;
    return retval;
} 

void Push(stNode *head,int number)
{
    stNode* newHead = (stNode*)malloc(sizeof(stNode));
    if(newHead == NULL)
    {
        exit(0);
    }
    newHead->data =number;
    newHead->next = head;
    head = newHead;
    }
 int Pop( stNode *head)
 {
    int retval =-99;
    if(head)
    {
        stNode * oldHead = head;
        retval = head->data;
        head =oldHead->next;
        free(oldHead);


    }    
    return retval;

 }



