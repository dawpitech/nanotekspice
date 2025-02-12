/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <exception>
#include <iostream>

#include "Circuit.hpp"
#include "Factory.hpp"
#include "IComponent.hpp"
#include "AComponent.hpp"
#include "parser.hpp"

int main(const int argc, const char** argv)
{
    if (argc != 2)
        return 84;

    nts::Circuit circuit;
    nts::Parser p(circuit);

    try {
            p.parse_file(argv[1]);
    } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 84;
    }

    std::cout << "> ";
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            std::cout << "> ";
            continue;
        }
        nts::ParserUtils::trim_string(line);
        if (line == "exit")
            break;
        if (line.find("=") != std::string::npos) {
            std::string left, right;

            try {
                nts::ParserUtils::split_in_half(line, left, right, '=');
            } catch (...) {
                std::cout << "Bad command format." << std::endl << "> ";
                continue;
            }
            if (left.empty() || right.empty()) {
                std::cout << "Bad command format." << std::endl << "> ";
                continue;
            }
        }
        std::cout << "Unknown command: " << line << std::endl << "> ";
    }

    return 0;
};
