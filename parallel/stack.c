 #include "stackHw.h"

 //void Push(stNode *head,int number);




 

extern tsllSTACK* CreateStack(){
    tsllSTACK* newStack = (tsllSTACK* )malloc(sizeof(tsllSTACK ));
    newStack->head=NULL;
     newStack->stackCount=0;
    pthread_mutex_init(&(newStack->stMutex),NULL);
    return newStack;
}





long long GetStackCount(tsllSTACK *stack){
    long long retval=0;
    pthread_mutex_lock(&(stack->stMutex));
    stNode * start =stack->head;
    while (start)
    {
        retval ++;    
        start = start->next;
    }
    pthread_mutex_unlock(&(stack->stMutex));
    return retval;
} 

void Push(tsllSTACK *stack,int number)
{
    stNode* newHead = (stNode*)malloc(sizeof(stNode));
    if(newHead == NULL)
    {
        printf("Failed to create new Node");
        exit(0);
    }
    pthread_mutex_lock(&(stack->stMutex));

    newHead->data =number;
    newHead->next = stack->head;
    stack->head = newHead;
    pthread_mutex_unlock(&(stack->stMutex));
}

int Pop( tsllSTACK *stack)
{
    int retval =-99;
    pthread_mutex_lock(&(stack->stMutex));
    if(stack->head)
    {
        stNode * oldHead = stack->head;
        retval = stack->head->data;
        stack->head =oldHead->next;
        free(oldHead);
    }
    pthread_mutex_unlock(&(stack->stMutex));    
    return retval;
}



