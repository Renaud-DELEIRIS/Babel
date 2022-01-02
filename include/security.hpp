/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Security.hpp
*/

#ifndef SECURITY_HPP
    #define SECURITY_HPP

    #include <iostream>
    #include <list>
    #include <set>
    #include <vector>
    #include <utility>
    #include <algorithm>
    #include <string>
    #include <bitset>
    #include <boost/array.hpp>

    #include "Protocol.hpp"

    namespace security
    {
        enum {
            limit = 0b0000000000000000
        };

        boost::array<std::bitset<16>, max_length> encoder(std::string);
        std::string decoder(boost::array<std::bitset<16>, max_length>);
    
        std::size_t get_size(boost::array<std::bitset<16>, max_length>);
        void display(boost::array<std::bitset<16>, max_length>);
    };

#endif /* SECURITY_HPP */
