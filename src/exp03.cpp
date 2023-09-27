#include "common.hpp"

void exp03()
{
    int childPid1 = 0,
        childPid2 = 0,
        childPid3 = 0;

    int pid = 0, status = 0;

    setbuf(stdout, nullptr);

    childPid1 = fork(); // Create a child process
    if (childPid1 == 0) {
        execlp("echo", "echo", "Hey, I'm child process 1!", nullptr);
        perror("exec1 error.\n");
        exit(1);
    }

    childPid2 = fork(); // Create a child process
    if (childPid2 == 0) {
        execlp("date", "date", nullptr);
        perror("exec2 error.\n");
        exit(2);
    }

    childPid3 = fork();
    if (childPid3 == 0) {
        execlp("ls", "ls", nullptr);
        perror("exec3 error.\n");
        exit(3);
    }

    puts("Parent process is waiting for child process returning!");

    while ((pid = wait(&status)) != -1) {
        if (childPid1 == pid) {
            printf("Child process 1 terminated with status %d\n", (status >> 8));
        } else if (childPid2 == pid) {
            printf("Child process 2 terminated with status %d\n", (status >> 8));
        } else if (childPid3 == pid) {
            printf("Child process 3 terminated with status %d\n", (status >> 8));
        }
    }

    puts("All child processes terminated.");
    puts("Parent process terminated");

    exit(0);
}