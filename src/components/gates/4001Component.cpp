/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4001Component.cpp
*/

#include <format>

#include "4001Component.hpp"
#include "src/Factory.hpp"

const std::unordered_map<std::size_t, std::pair<std::string, std::size_t>>
    nts::components::IC4001Component::INTERNAL_PIN_BINDS = {
    {1, std::make_pair("gate1", 1)},
    {2, std::make_pair("gate1", 2)},
    {5, std::make_pair("gate2", 1)},
    {6, std::make_pair("gate2", 2)},
    {8, std::make_pair("gate3", 1)},
    {9, std::make_pair("gate3", 2)},
    {12, std::make_pair("gate4", 1)},
    {13, std::make_pair("gate4", 2)}};

nts::components::IC4001Component::IC4001Component()
    : AAdvancedComponent(PIN_NUMBER)
{
    for (int i = 1; i < 5; i++)
        this->_internalCircuit.addComponent(std::format("gate{}", i),
            Factory::createComponent("or"));
}

void nts::components::IC4001Component::simulate(const std::size_t tick)
{
    this->updateLinks();
    for (auto& [name, comp] : this->_internalCircuit.getComponents())
        comp.get().simulate(tick);
}

nts::Tristate nts::components::IC4001Component::compute(const std::size_t pin)
{
    switch (pin)
    {
        case 3:
            return !this->_internalCircuit.getComponent("gate1").compute(3);
        case 4:
            return !this->_internalCircuit.getComponent("gate2").compute(3);
        case 10:
            return !this->_internalCircuit.getComponent("gate3").compute(3);
        case 11:
            return !this->_internalCircuit.getComponent("gate4").compute(3);
        case 7:
        case 14:
            return Tristate::Undefined;
        default:
            throw Exceptions::UnknownPinException();
    }
}
