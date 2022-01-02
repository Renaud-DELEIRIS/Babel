/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Signals.hpp
*/

#ifndef SIGNALS_HPP
    #define SIGNALS_HPP

    #include <iostream>
    #include <csignal>

    namespace signals
    {
        void handler();
        void signalHandler(int);
    }

#endif /* SIGNALS_HPP */