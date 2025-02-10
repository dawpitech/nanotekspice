/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include "IComponent.hpp"
#include "parser.hpp"

int main(const int argc, const char** argv)
{
    nts::Parser p;
    p.parse_file(argv[1]);
    return 0;
};
