#include "common.hpp"

int exp01()
{
    int i;
    if (fork())  // Parent --> if (123454); Child --> if (0)
    {
        printf("This is a parent process.\n");
        i = wait(NULL); // Wait for child
        printf("The child process, ID number %d, is finished.\n", i);
    }
    else
    {
        printf("It is a child process.\n");
        sleep(5);
        exit(EXIT_SUCCESS);
    }
    return 0;
}