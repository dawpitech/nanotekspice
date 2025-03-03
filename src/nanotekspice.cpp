/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <exception>
#include <iostream>
#include "parser.hpp"
#include "shell.hpp"

int main(const int argc, const char** argv)
{
    nts::Circuit circuit;
    const nts::Parser p(circuit);

    if (argc != 2)
        return 84;

    try
    {
        p.parse_file(argv[1]);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    const nts::shell s(circuit);
    try
    {
        s.run_shell();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
