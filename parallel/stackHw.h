#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
//Use these to change iterations and threads
#define NUM_THREADS 50
#define ITERATIONS 500
#define TRUE    1
#define FALSE   0
// data structures
typedef struct stNode
{
    int data;  
    struct stNode * next;  // the actual data

}stNode;

typedef struct tsllSTACK
{
    int stackCount;
    struct stNode * head;
    pthread_mutex_t stMutex;
}tsllSTACK;





//globals 
extern int *numbers;
extern int numSize ;
//add More globals/etc below


//All functions
extern void GetNumbers(char fileName[]);

//You need to create all of the below functions
extern long long GetStackCount(tsllSTACK *stack); 
extern int Pop( tsllSTACK *stack);
extern void Push(tsllSTACK *stack,int number);
extern void PrintAll(tsllSTACK *stack); // optional
extern tsllSTACK* CreateStack();


