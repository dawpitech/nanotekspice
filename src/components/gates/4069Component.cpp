/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4069Component.cpp
*/

#include <format>

#include "4069Component.hpp"
#include "src/Factory.hpp"

const std::unordered_map<std::size_t, std::pair<std::string, std::size_t>>
    nts::components::IC4069Component::INTERNAL_PIN_BINDS = {
    {1, std::make_pair("not1", 1)},
    {3, std::make_pair("not2", 1)},
    {5, std::make_pair("not3", 1)},
    {9, std::make_pair("not4", 1)},
    {11, std::make_pair("not5", 1)},
    {13, std::make_pair("not6", 1)}};

nts::components::IC4069Component::IC4069Component()
    : AAdvancedComponent(PIN_NUMBER)
{
    for (int i = 0; i < 6; i++)
        this->_internalCircuit.addComponent(std::format("not{}", i + 1),
            Factory::createComponent("not"));
}

void nts::components::IC4069Component::simulate(const std::size_t tick)
{
    this->updateLinks();
    for (auto& [name, comp] : this->_internalCircuit.getComponents())
        comp.get().simulate(tick);
}

nts::Tristate nts::components::IC4069Component::compute(const std::size_t pin)
{
    switch (pin)
    {
        case 2:
            return this->_internalCircuit.getComponent("not1").compute(2);
        case 4:
            return this->_internalCircuit.getComponent("not2").compute(2);
        case 6:
            return this->_internalCircuit.getComponent("not3").compute(2);
        case 8:
            return this->_internalCircuit.getComponent("not4").compute(2);
        case 10:
            return this->_internalCircuit.getComponent("not5").compute(2);
        case 12:
            return this->_internalCircuit.getComponent("not6").compute(2);
        case 7:
        case 14:
            return Tristate::Undefined;
        default:
            throw Exceptions::UnknownPinException();
    }
}
