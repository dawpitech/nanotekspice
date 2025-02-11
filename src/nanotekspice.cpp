/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <iostream>

#include "Circuit.hpp"
#include "Factory.hpp"
#include "IComponent.hpp"
#include "parser.hpp"

int main(const int argc, const char** argv)
{
    if (argc == 1)
        return 84;

    nts::Circuit circuit;
    nts::Parser p;

    p.parse_file(argv[1]);

    std::unique_ptr<nts::IComponent> true1 = nts::Factory::createComponent("true");
    std::unique_ptr<nts::IComponent> true2 = nts::Factory::createComponent("true");

    circuit.addComponent("true1", std::move(true1));
    circuit.addComponent("true2", std::move(true2));

    std::cout << circuit.getComponent("true1") << std::endl;
    std::cout << circuit.getComponent("true2") << std::endl;
    return 0;
};
