#include "common.hpp"

int g_variable = 4;

void exp04()
{
    pid_t pid = 0;
    int l_variable = 5;
    printf("Before fork.\n");
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(0);
    }
    if (pid == 0) {
        ++g_variable;
        --l_variable;
        printf("Child %d changed the global and local variable.\n", getpid());
    } else {
        wait(nullptr);
        printf("Parent %d did not change the global and local variable.\n", getpid());
    }
    printf("pid=%d, global variable=%d, local variable=%d\n", getpid(), g_variable, l_variable);
    exit(0);
}