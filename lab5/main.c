/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: h6iqbal
 *
 * Created on February 20, 2022, 12:50 PM
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>

#define MAX 5

void * count(void *);
int globalNumber = 0;
//Create a mutex 
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];
    i=0;
    //Create the 5 threads
    while(i<MAX){
        pthread_create(&counterThread[i], NULL, count, NULL);
        i++;
    }
    //Wait for all treads to finish
    for(i=0;i< MAX;i++)
    {
        pthread_join(counterThread[i], NULL);    
    }   
    printf("globalNumber: %d\n", globalNumber);
    return (0);    
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    return (0);
}



