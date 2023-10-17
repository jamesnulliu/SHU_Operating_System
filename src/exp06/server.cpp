// Build and run this file through a unique terminal process
// [To Build] 
// >>> g++ -std=c++20 -g -o ./bin/exp06/server.out -I ./src ./src/exp06/server.cpp
// [To Run]
// >>> ./bin/exp06/server.out

#include "common.hpp"
#include <iostream>
#include <format>

constexpr int MSGKEY = 75;

struct MsgForm
{
    long type = 0;
    char text[256] = {0};
};

MsgForm msg;

int msgqid = 0;

void cleanup(int msgqid)
{
    msgctl(msgqid, IPC_RMID, 0);
}

int main()
{
    int i = 0, pid = 0, *pint = nullptr;
    for (i = 0; i < 20; ++i) {
        signal(i, cleanup); // Set softirq signals
    }
    msgqid = msgget(MSGKEY, 0777 | IPC_CREAT); // Establish message queue
    while (true)
    {
        msgrcv(msgqid, &msg, 256, 1, 0); // Receive message
        pint = (int *)msg.text;
        pid = *pint;
        std::cout << std::format("Server: receive from pid {}\n", pid); // Print message source
        msg.type = pid;
        *pint = getpid();                     // Add identifier of current process
        msgsnd(msgqid, &msg, sizeof(int), 0); // Send message
    }
    return 0;
}