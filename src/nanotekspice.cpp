/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <exception>
#include <iostream>
#include <stdexcept>

#include "parser.hpp"
#include "shell.hpp"

int nts_main(const int argc, const char** argv)
{
    nts::Circuit circuit;
    const nts::Parser p(circuit);

    if (argc != 2)
        return 84;

    try
    {
        p.parse_file(argv[1]);
	if (circuit.getComponents().empty())
	    throw std::runtime_error("no components found in file.");
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
