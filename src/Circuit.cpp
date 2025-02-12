/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Circuit.cpp
*/

#include <iostream>

#include "Circuit.hpp"

void nts::Circuit::addComponent(const std::string& name, std::unique_ptr<IComponent> comp)
{
    this->_components.insert(std::make_pair(name, std::move(comp)));
}

std::unique_ptr<nts::IComponent> nts::Circuit::getComponent(const std::string& name)
{
    try
    {
        return std::move(this->_components.at(name));
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
        return nullptr;
    }
}
