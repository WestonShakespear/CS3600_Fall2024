#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

int main()
{
    char * name = "test.txt";

    //Test for file
    int t_fd = open(name, O_RDONLY | O_EXCL);
    int fd;

    if (t_fd == -1)
    {
        printf("Error no: %d\n", errno);
        if (errno == ENOENT)
        {
            printf("File doesn't exist...creating\n");
            fd = creat(name, O_RDONLY | O_CREAT);
        }
        else
        {
            printf("Undefined error\n");
            return 1;
        }
    }
    else
    {
        fd = t_fd;
    }

    printf("fd = %d\n", fd);

    if (fd == -1)
    {
        printf("Error no: %d\n", errno);
    }

    close(fd);

    printf("\n\n");
    return 0;
}