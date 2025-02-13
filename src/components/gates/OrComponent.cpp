/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OrComponent.cpp
*/

#include "OrComponent.hpp"

void nts::components::gates::OrComponent::simulate(const std::size_t tick)
{
    if (this->_connections.at(0) != std::nullopt)
        this->_connections.at(0).value().first.get().simulate(tick);
    if (this->_connections.at(1) != std::nullopt)
        this->_connections.at(1).value().first.get().simulate(tick);
}

nts::Tristate nts::components::gates::OrComponent::compute(const std::size_t pin)
{
    if (pin != 3)
        throw Exceptions::IncorrectPinUsageException();
    if (this->_connections.at(0) == std::nullopt ||
        this->_connections.at(1) == std::nullopt)
        return Tristate::Undefined;
    auto [cmpleft, cmpleft_pin] = this->_connections.at(0).value();
    auto [cmpright, cmpright_pin] = this->_connections.at(1).value();
    return cmpleft.get().compute(cmpleft_pin) | cmpright.get().compute(cmpright_pin);
}
