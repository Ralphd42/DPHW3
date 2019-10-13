 #include "stackHw.h"
  
 //void Push(stNode *head,int number);
int main(int argc, char*argv[])
{
    timing_start();
    tsllSTACK* stack;
    stack =CreateStack();
    int retval =0;
    
    Push(stack,5   );
    Push(stack,7  );
    Push(stack,2  );
    long long cnt = GetStackCount(stack);
    printf("\n%lld\n",cnt);
    timing_stop();
    print_timing();
    return retval;
}   

extern tsllSTACK* CreateStack(){
    tsllSTACK* newStack = (tsllSTACK* )malloc(sizeof(tsllSTACK ));
    newStack->head=NULL;
     newStack->stackCount=0;
    pthread_mutex_init(&(newStack->stMutex),NULL);
    return newStack;
}





long long GetStackCount(tsllSTACK *stack){
    long long retval=0;
    stNode * start =stack->head;
    while (start)
    {
        retval ++;    
        start = start->next;
    }
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
    newHead->data =number;
    newHead->next = stack->head;
    stack->head = newHead;
}
 int Pop( tsllSTACK *stack)
 {
    int retval =-99;
    if(stack->head)
    {
        stNode * oldHead = stack->head;
        retval = stack->head->data;
        stack->head =oldHead->next;
        free(oldHead);
    }    
    return retval;

 }



