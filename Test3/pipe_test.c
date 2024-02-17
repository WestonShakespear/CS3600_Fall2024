#include <stdio.h>
#include <stdlib.h>

// Include for pid_t
#include <sys/types.h>

// Include for getpid(), getpgid(), fork()
#include <unistd.h>

// Include for wait()
#include <sys/wait.h>


int main()
{
    pid_t main_pid = getpid();
    pid_t group_pid = getpgid(main_pid);

    printf("Main process:\n");
    printf("\t      PID: %d\n", main_pid);
    printf("\tGroup PID: %d\n\n", group_pid);

    int pipefd[2];
    char buf;

    int err = pipe(pipefd);

    if (err == -1)
    {
        printf("Error");
        return 1;
    }

    printf("Fork the process:\n");
    pid_t fork1_pid = fork();

    if (fork1_pid == 0)
    {
        // Child
        printf("\tChild\n");
        pid_t child_pid = getpid();
        pid_t child_group_pid = getpgid(child_pid);

        printf("\t\t      PID: %d\n", child_pid);
        printf("\t\tGroup PID: %d\n", child_group_pid);

        pid_t fork2_pid = fork();

        if (fork2_pid == 0)
        {

        }
        else
        {
            close(pipefd[0]);

            pid_t ccg = getpgid(fork2_pid);

            write(pipefd[1], &ccg, 4);
        }

        

    
        
        close(pipefd[0]);
        

        _exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent

        printf("\tParent\n");
        printf("\t\tThe child pid is %d\n", fork1_pid);

        close(pipefd[1]);

        int c = 0;
        char ppid[10];

        int nn = 0;
        read(pipefd[0], &nn, sizeof(1234));

        printf("%d", nn);

        wait(NULL);
        
        close(pipefd[1]);
        
        
    }





    printf("\n\n");
    return 0;
}