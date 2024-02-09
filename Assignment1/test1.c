// Standard imports
#include <stdio.h>
#include <stdlib.h>
// Syscall imports
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// Color Defines
#define CEX   "\x1b["
#define FRED  "31m"
#define FNRM  "0m"
// Color macros
#define RED() ( printf("%s%s",CEX,FRED) )
#define NRM() ( printf("%s%s",CEX,FNRM) )
// Function definitions
int get_input();
void calc_fib(int input);
// Main function
int main()
{
    // Output the beginning of the process
    RED();
    printf("-----------------------------------Start of process------\n\n");
    // Obtain a number from the user in this process
    int number = get_input();
    // Fork the process and store the pid of the new process
    pid_t p = fork();
    // Error in forking the process
    if (p == -1)
    {
        // Output to stderr
        perror("Error Forking");
        // Exit with error status
        exit(1);
    }
    // The pid will be 0 in the child process
    else if (p == 0)
    {
        // Inform the user that this code is running from the child process
        RED();
        printf("---------------------------------Child Process Code------\n\n");
        // Calculate the fibonacci sequence using the function below
        calc_fib(number);
        // Exit the child process successfully
        exit(0);
    }
    else
    {
        // Inform the user that this code is running from the parent process
        RED();
        printf("--------------------------------Parent Process Wait------\n\n");
        // If the parent process is "ahead" of the child
        // wait for all children (1) to finish
        wait(NULL);
    }
    // Inform the user of the pid for each process
    RED();
    printf("-----------------------------------------PID Report------\n\n");
    NRM();
    printf("parent\t|\t%d\n", getpid());
    printf("fork\t|\t%d\n", p);
    // Add some lines at the end and return goods
    printf("\n\n");
    return 0;
}
// Function to get a positive number from the user
int get_input()
{
    // Ask the user for a number
    NRM();
    printf("Please enter the fibonacci index: ");
    // Obtain this number from stdin
    int number;
    scanf("%d", &number);
    // Check if the number is above 0
    if (number < 0)
    {
        // Print "error" message and return this function
        printf("Please enter a valid number (above zero)\n");
        return get_input();
    }
    // The number is above zero so return it
    return number;
}
// Function to calculate the fibonacci sequence for a given index
void calc_fib(int input)
{
    // These will hold the current (b) and last (a) numbers
    int a = 0;
    int b = 1;
    // Output the "first"
    NRM();
    printf("%i -> ", a);
    // Loop and print/calculate the rest
    for (int i = 1; i < input; i++)
    {
        // Output the number unless it's the last one
        if (i < input - 1) { printf("%i -> ", b); }
        // Store the current number
        int _b = b;
        // Add the last number to the current
        b += a;
        // Store the old current in the last
        a = _b;
    }
    // Output the last number in the sequence
    printf("%i\n\n", a);
}