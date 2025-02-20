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

    IComponent* addedComp = &this->getComponent(name);
    if (const auto outputComp = dynamic_cast<components::special::OutputComponent*>(addedComp))
    {
        this->_outputs.emplace_back(name, std::ref(*outputComp));
    }
    if (const auto inputComp = dynamic_cast<components::special::InputComponent*>(addedComp))
    {
        this->_inputs.emplace_back(name, std::ref(*inputComp));
    }
    this->_componentsRef.emplace_back(name, std::ref(*addedComp));
}

nts::IComponent& nts::Circuit::getComponent(const std::string& name) const
{
    try
    {
        return *this->_components.at(name);
    }
    catch (std::exception&)
    {
        throw Exceptions::UnknownChipException();
    }
}
