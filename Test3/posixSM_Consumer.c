#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>

#include <errno.h>

/* the size (in bytes) of shared memory object */
#define SIZE 4096

int main()
{
    /* name of the shared memory object */
    const char *name = "OS";
    /* shared memory file descriptor */
    int shm_fd;
    /* pointer to shared memory obect */
    void *ptr;

    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDONLY, 0666);

    int errsv = errno;
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("errno Value: %d\n", errsv);

    if (errno > 0)
    {
        printf("There is no memory mapped data\n");
        return 1;
    }

    printf("Reading from shared memory object '%s'\n", name);
    /* read from the shared memory object */
    printf("%s\n",(char *)ptr);



    /* remove the shared memory object */
    shm_unlink(name);
    return 0;
}