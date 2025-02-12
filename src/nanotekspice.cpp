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
    if (argc == 1)
        return 84;

    nts::Circuit circuit;
    nts::Parser p(circuit);

    try {
	    p.parse_file(argv[1]);
    } catch (std::exception &e) {
	    std::cerr << e.what() << std::endl;
	    return 84;
    }

    std::unique_ptr<nts::IComponent> true1 = nts::Factory::createComponent("true");
    std::unique_ptr<nts::IComponent> output1 = nts::Factory::createComponent("output");

    output1->setLink(1, *true1, 1);
    std::cout << output1->compute(1) << std::endl;
    return 0;
};
