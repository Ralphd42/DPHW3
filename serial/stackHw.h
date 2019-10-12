#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Use these to change iterations and threads
#define NUM_THREADS 50
#define ITERATIONS 500
// data structures
typedef struct stNode
{
    int data;  
    struct stNode * next;  // the actual data

}stNode;

//globals 
extern int *numbers;
extern int numSize ;
//add More globals/etc below


//All functions
extern void GetNumbers(char fileName[]);

//You need to create all of the below functions
extern long long GetStackCount(); 
extern int Pop( stNode *head);
extern void Push(stNode *head,int number);
//extern void PrintAll(); // optional



