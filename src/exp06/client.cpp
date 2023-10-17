// Build and run this file through a unique terminal process
// [To Build] 
// >>> g++ -std=c++20 -g -o ./bin/exp06/client.out -I ./src ./src/exp06/client.cpp
// [To Run]
// >>> ./bin/exp06/client.out

#include "common.hpp"
#include <iostream>
#include <format>

constexpr auto MSGKEY = 75;

struct MsgForm
{
    long type = 0;
    char text[256] = {0};
};

int main()
{
    MsgForm msg{};
    int msgqid = 0, pid = 0, *pint = nullptr;
    msgqid = msgget(MSGKEY, 0777); // Establish message queue
    pid = getpid();
    pint = (int *)msg.text;
    *pint = pid;
    msg.type = 1;
    msgsnd(msgqid, &msg, sizeof(int), 0);
    msgrcv(msgqid, &msg, 256, pid, 0);
    std::cout << ("Clint: receive from pid {}\n", *pint);
    return 0;
}
