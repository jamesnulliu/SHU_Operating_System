#include "common.hpp"
#include <iostream>
#include <format>

void exp03();
void exp04();
void exp05();

int main()
{
    std::cout << std::format("C++ version: {}, comilper: {}\n", __cplusplus, "g++-13");
    exp05();
}