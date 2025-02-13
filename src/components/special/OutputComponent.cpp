/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OutputComponent.cpp
*/

#include "OutputComponent.hpp"

void nts::components::special::OutputComponent::simulate(const std::size_t tick)
{
    if (this->_connections.at(0) == std::nullopt)
        return;
    this->_connections.at(0).value().first.get().simulate(tick);
}

nts::Tristate nts::components::special::OutputComponent::compute(const std::size_t pin)
{
    if (pin != 1)
        throw Exceptions::UnknownPinException();
    if (this->_connections.at(0) == std::nullopt)
        return Tristate::Undefined;
    auto [component, pinOther] = this->_connections.at(0).value();
    return component.get().compute(pinOther);
}
