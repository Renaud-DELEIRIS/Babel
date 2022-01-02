/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Protocol.hpp
*/

#ifndef PROTOCOL_HPP
    #define PROTOCOL_HPP

    #include <iostream>
    #include <string>
    #include "common/User.hpp"

    enum
    {
        max_length = (1024 * 6)
    };

    struct Commands
    {
        std::string command;
        std::string arguments;
    };

    struct C_Commands
    {
        char *command;
        char *arguments;
    };

    struct C_User
    {
        char *username;
        char *password;
        char *address;
        int id;
    };

    struct Protocol
    {
        C_Commands command;
        C_User user;
    };

    struct S_Protocol
    {
        Commands command;
        UserApp user;
    };

#endif /* PROTOCOL_HPP */
