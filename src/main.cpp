#include "common.hpp"
#include <iostream>
#include <format>

void exp01();
void exp02();
void exp03();
void exp04();
void exp05();
void exp07();

int main()
{
    std::cout << std::format("C++ version: {}, comilper: {}\n", __cplusplus, "g++-13");
    exp07();
}