 #include "stackHw.h"
 #include "timing.h"
 /*
 sbatch -n8 -p batch --wrap="/network/rit/home/rd716418/C/HW2/parrelle/part_1_parallel.out IM10"
 */ 
 //void Push(stNode *head,int number);
int main(int argc, char*argv[])
{
    timing_start();
    tsllSTACK * stack;
    stack =CreateStack();
    
    if(argc<2)
    {
        perror("\nUsage ./matmul <inputfile.csv>\n");
        exit(-1);
    }
    char * filename= argv[1];
    GetNumbers(filename);
    int cnt =0;
    for(cnt=0;cnt<numSize;cnt++ )
    {
        //stack->Push(numbers[cnt]);
        Push(stack,*(numbers+cnt));

    }
    int retval =0;
    long long scnt = GetStackCount(stack);
    printf("\nFull Stack count %lld\n",scnt);
    printf("Stack Pop \n");
    for(cnt=0;cnt<numSize;cnt++ )
    {
        //stack->Push(numbers[cnt]);
        int poppedOut =Pop(stack);
        printf("%d\n",poppedOut );
    }
    timing_stop();
    print_timing();
    return retval;
}   

extern tsllSTACK* CreateStack(){
    tsllSTACK* newStack = (tsllSTACK* )malloc(sizeof(tsllSTACK ));
    newStack->head=NULL;
     newStack->stackCount=0;
     
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



