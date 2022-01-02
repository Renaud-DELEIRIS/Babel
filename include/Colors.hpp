/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Colors.hpp
*/

#ifndef COLORS_HPP
    #define COLORS_HPP

    #include <iostream>
    
    namespace colors
    {
        std::string bold = "\033[0;1m";
        std::string italic = "\033[0;3m";
        std::string underline = "\033[0;4m";

        std::string reset = "\033[0m";
        std::string red = "\033[31m";
        std::string green = "\033[32m";
        std::string yellow = "\033[33m";
        std::string blue = "\033[34m";
        std::string magenta = "\033[35m";
        std::string cyan = "\033[36m";
        std::string White = "\033[37m";
    }

#endif /* COLORS_HPP */