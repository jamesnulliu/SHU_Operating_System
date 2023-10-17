#include "common.hpp"
#include <iostream>
#include <format>

void foo(int)
{
    int m = getpid();
    std::cout << std::format("I am process {}. It is signal 18 processing function.\n", m);
}

void exp07()
{
    signal(18, foo);
    int i = fork();
    if(i!=0){
        int j = kill(i, 18); // Send signal to child processs
        std::cout << std::format("Parent signal 18 has been sent to child {}, and returned {}\n", i, j);
        int k = wait(nullptr);
        std::cout << std::format("After wait {}, parent process {} is finished.\n\n", k, getpid());
    }
     else
    {
        sleep(5);
        std::cout << std::format("Child {}: A signal from my parent process {} is recieved.\n", getpid(), getppid());
    }
}