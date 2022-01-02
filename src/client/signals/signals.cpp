/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** signals.cpp
*/

#include "client/Signals.hpp"

void signals::signalHandler(int signum)
{
    if (signum == 2)
        std::cout << "\b\bClosing client..." << std::endl;
    else
        std::cout << "\b\bInterrupt signal (" << signum << ") received" << std::endl;

    exit(signum);
}

void signals::handler()
{
    signal(SIGINT, signals::signalHandler);
}
