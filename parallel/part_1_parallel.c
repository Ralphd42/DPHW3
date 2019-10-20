 #include "stackHw.h"
 #include "timing.h"
typedef struct ThreadInfo
{
    pthread_t thread;
    int Maxn;  
    int Maxm;
    int threadid;
    tsllSTACK* Stack;
}ThreadInfo;
pthread_mutex_t MatRowmutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t popMutex        = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  popcond         = PTHREAD_COND_INITIALIZER;
void *ProcThread( void *arg);
int currm;  // the current  M
int currn;  // the current N
int popcnt;
int main(int argc, char*argv[])
{
    timing_start();
    if(argc<4)
    {
        perror("\nUsage ./part_1_parallel.out <inputfile.csv> <threadCount> <iterations>\n");
        exit(-1);
    }
    int numThreads =atoi(argv[2]);
    int iteratiomn = atoi(argv[3]);
    char* fname = argv[1];
    popcnt=0;
    GetNumbers(fname);
    tsllSTACK* stack;
    stack =CreateStack();
    int retval =0;
    // build the threads
    ThreadInfo * threads = (ThreadInfo *)malloc (numThreads * sizeof(ThreadInfo));
    int thcnt =0;
    //build
    for(;thcnt<numThreads;++thcnt)
    {
        threads[thcnt].threadid = thcnt;
        threads[thcnt].Stack    = stack;
        threads[thcnt].Maxm     = numSize;
        threads[thcnt].Maxn     = iteratiomn;
        pthread_create(&threads[thcnt].thread,NULL,ProcThread ,(void *) &threads[thcnt] );
    }
    void *status;
    for (thcnt =0; thcnt<numThreads;++thcnt)
    {
        pthread_join(threads[thcnt].thread, &status);
    }
    
    //PrintAll(stack);
    long long cnt = GetStackCount(stack);
    

    //show stack
    timing_stop();
    print_timing();
    pthread_exit(NULL);
    return retval;
}  

void *ProcThread( void *arg)
{
    
    //ThreadItem *inParams = (ThreadItem *)arg;
    //MatrixMultiply(inParams);
    // handle pushing first
    ThreadInfo *inParams = (ThreadInfo *)arg;
    int Allpops =inParams->Maxn  * inParams->Maxm;
    int hasItemstoPUSH =1;
    while (hasItemstoPUSH){
        pthread_mutex_lock(&MatRowmutex);
        if(currm >=  inParams->Maxm )   
        {
            pthread_mutex_unlock(&MatRowmutex);
            hasItemstoPUSH =0;
            //printf("\nthead %d has nothing to do\n", inParams->threadid);
        }else
        {
            int i = currm;
            //int j = currn;
            ++currn;
            if( currn>=inParams->Maxn)
            {
                currn=0;    
                ++currm;
            }
            pthread_mutex_unlock(&MatRowmutex);
            Push(inParams->Stack,*(numbers+i));
            //printf(" %d" ,inParams->threadid  );
        }
    }
    int needspop =TRUE;
    //printf("\n Start poping %d\n" ,inParams->threadid  );
    while( needspop )
    {
        pthread_mutex_lock(&popMutex);
        if(popcnt<Allpops)
        {
            if(GetStackCount(inParams->Stack)>0){
                ++popcnt;
                Pop(inParams->Stack);
                pthread_mutex_unlock(&popMutex);
            }
        }else
        {
            pthread_mutex_unlock(&popMutex);
            needspop =FALSE;
        }
        
    }
    pthread_exit(NULL);
}