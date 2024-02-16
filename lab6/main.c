//**
// *
// * COE 628 - Operating Systems
// * Lab 6
// * Hamza Iqbal
// * 
// **/

// if not already compiled run: (wont build in netbeans)
// gcc -pthread -o main main.c
// else if the main executable is already in folder you can just run it

#include <stdlib.h>     /* NULL */
#include <stdio.h>	/* printf */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>	/* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h> 	/* wait */
#include <pthread.h>

#define PRODUCER_NO 5	//Number of producers, can change here
#define NUM_PRODUCED 20 //2000 //Number of items to be produced, can change here

void *generator_function(void*);
void *print_function();
long sum; /* Sum of generated values*/
long finished_producers; /* number of the producer that finished producing */

//C: Mutex declaration and initialization
static pthread_mutex_t mutex1= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond_var= PTHREAD_MUTEX_INITIALIZER;

//F: Condition variable declaration and initialization
pthread_cond_t cond_var1 = PTHREAD_COND_INITIALIZER;

int main(void) {
    int i;
    /* initialize random seed: */
    srand(time(NULL));
    sum = 0;
    finished_producers=0;
    
    //A: Creates five generator thread
    pthread_t generated_threads[5];
    for(i=0;i<5;i++){
        pthread_create(&generated_threads[i],NULL,generator_function,NULL);
    }
    
    //D: Creates print thread
    pthread_t printThread;
    pthread_create(&printThread,NULL,print_function,NULL);
    
    //B: Makes sure that all generator threads has finished before proceeding
    for(i=0;i<5;i++){
        pthread_join(generated_threads[i],NULL);
    }
    //print_function();
    
    //E: Makes sure that print thread has finished before proceeding
    pthread_join (printThread,NULL);
    return (0);

}

void * generator_function(void* junk) {
    
    long counter = 0;
    long sum_this_generator = 0;
   
    while (counter < NUM_PRODUCED) {
    pthread_mutex_lock(&mutex1); // lock
      long tmpNumber = sum;
      long rnd_number = 1;//rand() % 10; 
        // can make = 1, output should be 100 (20 loops*5 threads)
      printf("current sum of the generated number up to now is %ld going to add %ld to it.\n", tmpNumber, rnd_number);
        sum = tmpNumber + rnd_number;
        counter++;
        pthread_mutex_unlock(&mutex1);
        sum_this_generator += rnd_number;
        usleep(1000);
    }
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    printf("The sum of produced items for this number generator at the end is: %ld \n", sum_this_generator);
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    finished_producers++;
    
    //H: If all generator has finished fire signal for condition variable
    pthread_mutex_lock(&cond_mutex);
    while (1){
        if(finished_producers>=5){
            pthread_cond_signal(&cond_var1);
        }
    break;
    }
    pthread_mutex_unlock(&cond_mutex);
    return (0);
}

  void *print_function(void* junk) {
   //G: Wait until all generator has finished
   pthread_mutex_lock(&cond_mutex);
    while(finished_producers<5){
        pthread_cond_wait(&cond_var1,&cond_mutex);
   }
    pthread_mutex_unlock(&cond_mutex);
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("The value of counter at the end is: %ld \n", sum);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}







