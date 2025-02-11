/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <iostream>

#include "Factory.hpp"
#include "IComponent.hpp"
#include "parser.hpp"

int main(const int argc, const char** argv)
{
    nts::Parser p;
    p.parse_file(argv[1]);
    std::unique_ptr<nts::IComponent> const component = nts::Factory::createComponent("true");
    std::cout << component.get() << std::endl;
    return 0;
};
