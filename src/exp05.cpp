#include "common.hpp"
#include <string>
#include <iostream>

constexpr int INTERVAL_SECOND = 5;

enum PipeEnd { READ = 0, WRITE = 1 };

inline void wirtePipe(int *fd, const std::string &buf)
{
    close(fd[READ]);
    if (write(fd[WRITE], buf.c_str(), 50) == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

inline auto readPipe(int *fd) -> std::string
{
    close(fd[WRITE]);
    char m[50]{0};
    if (read(fd[READ], m, 50) == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    return {m};
}

void exp05()
{

    // Create a pipe
    int fd[2]{0};
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int i = 0;

    // Generate 5 processes
    for (i = 0; i < 5; i++)
    {
        if (fork() == 0)
        {
            break;
        }
    }

    // Child Process 1
    if (i == 0)
    {
        std::string str1{"I'm child process 01!"};
        wirtePipe(fd, str1);
        std::cout << "Child process 01 worte to pipe." << std::endl;
        exit(0);
    }
    // Child Process 2
    else if (i == 1)
    {
        auto message = readPipe(fd);
        std::cout << "Child process 02 recieved: " << message << std::endl;
        exit(0);
    }
    // Child Process 3
    else if (i == 2)
    {
        auto message = readPipe(fd);
        std::cout << "Child process 03 recieved: " << message << std::endl;
        exit(0);
    }
    // Child Process 4
    else if (i == 3)
    {
        sleep(INTERVAL_SECOND); // Sleep for 5 secs
        std::string str1{"I'm child process 04!"};
        wirtePipe(fd, str1);
        std::cout << "Child process 04 worte to pipe." << std::endl;
        exit(0);
    }
    // Parent Process
    else
    {
        close(fd[READ]);
        close(fd[WRITE]);
        // Parent process
        for (int i = 0; i < 5; ++i)
        {
            wait(nullptr);
        }
    }
}