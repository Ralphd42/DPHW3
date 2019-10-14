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
pthread_mutex_t MatRowmutex = PTHREAD_MUTEX_INITIALIZER;
void *ProcThread( void *arg);
int currm;  // the current  M
int currn;  // the current N
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
    GetNumbers(fname);
    tsllSTACK* stack;
    stack =CreateStack();
    int retval =0;
    // build the threads
    ThreadInfo * threads = (ThreadInfo *)malloc (numThreads * sizeof(ThreadInfo));
    int thcnt =0;
    //build
    for(;thcnt<numThreads;thcnt++)
    {
        threads[thcnt].threadid = thcnt;
        threads[thcnt].Stack    = stack;
        threads[thcnt].Maxm     = numSize;
        threads[thcnt].Maxn     = iteratiomn;
        pthread_create(&threads[thcnt].thread,NULL,ProcThread ,(void *) &threads[thcnt] );
    }
    void *status;
    for (thcnt =0; thcnt<numThreads;thcnt++)
    {
        pthread_join(threads[thcnt].thread, &status);
    }
    long long cnt = GetStackCount(stack);
    printf("\n%lld\n",cnt);
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
    int hasItemstoPUSH =1;
    while (hasItemstoPUSH){
        pthread_mutex_lock(&MatRowmutex);
        if(currm>=  inParams->Maxm )   
        {
            pthread_mutex_unlock(&MatRowmutex);
            hasItemstoPUSH =0;
        }else
        {
            int i = currm;
            int j = currn;
            currn++;
            if( currn>=inParams->Maxn)
            {
                currn=0;    
                currm++;
            }


            /* code */
        }
        
    
    }










    pthread_exit(NULL);
}