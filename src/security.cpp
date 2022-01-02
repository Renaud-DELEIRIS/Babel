/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** security.cpp
*/

#include "security.hpp"

boost::array<std::bitset<16>, max_length> security::encoder(std::string data)
{
    boost::array<std::bitset<16>, max_length> payload;

    for (std::size_t i = 0; i < data.size(); i++) {
        payload[i] = (std::bitset<16>(data.c_str()[i]));
    }

    return (payload);
}

std::string security::decoder(boost::array<std::bitset<16>, max_length> data)
{
    char tmp;
    char previous;
    std::vector<char> dump;
    std::map<char, char> replace = {
        { '{', ';' },
        { '`', ' ' }
    };
    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++) {
        tmp = static_cast<char>(data[i].to_ulong());
        dump.push_back(tmp);
    }
    std::string payload(dump.begin(), dump.end());

    return (payload);
}

std::size_t security::get_size(boost::array<std::bitset<16>, max_length> data)
{
    std::size_t size = 0;

    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++, size++) {
        std::cout << data[i] << std::endl;
    }

    return (size);
}

void security::display(boost::array<std::bitset<16>, max_length> data)
{
    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++) {
        std::cout << data[i] << std::endl;
    }
}