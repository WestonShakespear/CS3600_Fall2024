#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>        // pthread library, compile with "-pthread"
#include <unistd.h>         // for sleep() function
#include <math.h>           // for sin and cos, compile with "-lm"

#define THREADS_TO_RUN 10   // amount of threads to spawn
// time between spawning, and time between thread operations * 3
#define WAIT_TIME       3   

// definitions and macros for colored text output
#define CEX   "\x1b["       // base escape code
#define FRED  "31m"         // red foreground
#define FMAG  "35m"         // magenta foreground
#define FNRM  "0m"          // normal foreground
#define UND "\e[4m"         // underline

#define RED() ( printf("%s%s",CEX,FRED) )   // set console to red output
#define NRM() ( printf("%s%s",CEX,FNRM) )   // set the console to normal output

// Output magenta underlined text, with newline before and after
// Using #msg in the macro will auto convert the argument into a string
#define MAIN(msg) ( printf("\n%s%s%smain | %s\n\n",CEX,FMAG,UND,#msg), NRM() )

// Function prototype for thread worker
void *Worker(void *t_id);

// Main function
int main()
{
    // Output information using MAIN(msg) macro
    MAIN(Assignment4);

    // Create an array to hold all the thread ids
    pthread_t threads[THREADS_TO_RUN];

    // Define and initialize a thread attribute
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    // Set the thread detach state to joinable
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);

    // Loop and create the amount of threads defined by THREADS_TO_RUN
    MAIN(Creating threads:);
    for (int i = 0; i < THREADS_TO_RUN; i++)
    {
        // Output current thread number that will be spawned
        RED(); printf("main | Creating thread:%d\n", i); NRM();

        // Spawn the thread
        // The first argument is a reference as to where to store the thread id
        // The second is the attributes, this will make the thread joinable
        // The third is the function to be executed by the thread
        // The last is the argument to give to the function
        if (pthread_create(&threads[i], &attributes, Worker, (void *)i))
        {
            // If pthread_create returns not zero then there was an error, exit
            RED(); printf("main | Thread: %d exited with an error\n", i); NRM();
            exit(1);
        }
        // Sleep before spawning the next thread
        sleep(WAIT_TIME);
    }
    // Release the resources for the pthread attribute
    pthread_attr_destroy(&attributes);

    // Joing the first 6 threads
    MAIN(Joining first 6 threads:);
    // Loop through the first six values of threads[]
    for (int i = 0; i < 6; i++)
    {
        RED(); printf("main | Joining thread: %d\n", i); NRM();

        // If pthread_join returns a non zero there was an error.
        // Exit if there was an error or continue if not
        if (pthread_join(threads[i], NULL))
        {
            RED(); printf("main | Thread: %d exited with an error\n", i); NRM();
            exit(1);
        }
    }

    // Destroy the last thread
    MAIN(Killing the last thread);
    // pthread_cancel will request that the thread ends
    // depending on the threads cancel state this may happen instantly or not
    if (pthread_cancel(threads[THREADS_TO_RUN - 1]))
    {
        // If pthread_cancel returns a non zero
        // there was an error cancelling the thread
        RED();
        printf("main |\t pthread_kill resulted in an error\n");
        NRM();
        exit(1);
    }

    // If everything ran correctly, output and return success
    MAIN(The last thread was killed successfully);
    return 0;
}

// Thread worker function
void *Worker(void *t_id)
{
    // Immediately set the cancel state to asynchronous
    // This will cancel the thread as fast as possible after receiving the 
    // cancel signal
    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // Cast the argument to a long in order to get the thread id from the arg
    long tid = (long)t_id;
    printf("thrd%ld|\tThread worker started\n", tid);

    // Do some work and pretend it takes awhile with the sleep() function
    double stor = 0.0;
    for (int i = 0; i < 10; i++)
    {
        stor += sin(i) * tan(i);
        sleep(WAIT_TIME * 3);
    }

    // Output closing statement and exit the thread
    printf("thrd%ld|\tThread finished: %lf\n", tid, stor);
    pthread_exit((void*)tid);
}