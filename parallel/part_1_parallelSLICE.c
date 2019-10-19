 #include "stackHw.h"
 #include "timing.h"
typedef struct ThreadInfo
{
    pthread_t thread;
    int IterationCount;  
     
    int slicecount;
    int slicestart;
    int threadid;
    tsllSTACK* Stack;
}ThreadInfo;
pthread_mutex_t MatRowmutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t popMutex        = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  popcond  = PTHREAD_COND_INITIALIZER;
void *ProcThread( void *arg);
//int currm;  // the current  M
//int currn;  // the current N
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
    //build slice cnt ant slice start
    int slicesz =0;
    if(numSize%numThreads ==0)
    {
        slicesz =(numSize/numThreads);
        for(;thcnt<(numThreads);++thcnt)
        {
            threads[thcnt].threadid = thcnt;
            threads[thcnt].Stack    = stack;
            threads[thcnt].slicestart     = thcnt* slicesz;
            threads[thcnt].IterationCount = iteratiomn;
            threads[thcnt].slicecount     = slicesz;
            pthread_create(&threads[thcnt].thread,NULL,ProcThread ,(void *) &threads[thcnt] );
        }

    }else
    {
       int extras =numSize%numThreads;
        slicesz =(numSize/numThreads);
        int sliceStart =0;
        for(;thcnt<(numThreads);++thcnt)
        {
            threads[thcnt].threadid = thcnt;
            threads[thcnt].Stack    = stack;
            int adder =0;
            if( extras>0)    
            {
                --extras;
                adder=1;
            }
            
            
            threads[thcnt].slicestart     = sliceStart;//thcnt* slicesz;
            threads[thcnt].IterationCount = iteratiomn;
            threads[thcnt].slicecount     = (slicesz  +adder);
            pthread_create(&threads[thcnt].thread,NULL,ProcThread ,(void *) &threads[thcnt] );
            sliceStart +=  (slicesz  +adder);
        }
    }
    




    





    void *status;
    for (thcnt =0; thcnt<numThreads;++thcnt)
    {
        pthread_join(threads[thcnt].thread, &status);
    }
    
    //PrintAll(stack);
    long long cnt = GetStackCount(stack);
    printf("\n%lld Number Items\n",cnt);

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
    //int Allpops =inParams->Maxn  * inParams->Maxm;
    int hasItemstoPUSH =TRUE;
    int i ;
    int icnt;
    int end = inParams->slicestart + inParams->slicecount;
     
    for(icnt =inParams->slicestart; icnt<end ; ++icnt)
    {
        int repcnt;
        for (repcnt=0;repcnt<inParams->IterationCount;repcnt++)
        {
            Push(inParams->Stack,*(numbers+icnt));
        }
    }
    
    int needspop =TRUE;
    //printf("\n Start poping %d\n" ,inParams->threadid  );
    /*while( needspop )
    {
        pthread_mutex_lock(&popMutex);
        if(popcnt<Allpops)
        {
            popcnt++;
            pthread_mutex_unlock(&popMutex);     
            Pop(inParams->Stack);
        }else
        {
            pthread_mutex_unlock(&popMutex);
            needspop =FALSE;
        }
        
    }*/
    pthread_exit(NULL);
}