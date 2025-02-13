/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AndComponent.cpp
*/

#include <optional>

#include "AndComponent.hpp"

void nts::components::gates::AndComponent::simulate(const std::size_t tick)
{
    if (this->_connections.at(0) != std::nullopt)
        this->_connections.at(0).value().first.get().simulate(tick);
    if (this->_connections.at(1) != std::nullopt)
        this->_connections.at(1).value().first.get().simulate(tick);
}

nts::Tristate nts::components::gates::AndComponent::compute(const std::size_t pin)
{
    if (pin != 3)
        //TODO make better exception when compute is called on an input pin
        throw std::exception();
    if (this->_connections.at(0) == std::nullopt ||
        this->_connections.at(1) == std::nullopt)
        return Tristate::Undefined;
    auto [cmpleft, cmpleft_pin] = this->_connections.at(0).value();
    auto [cmpright, cmpright_pin] = this->_connections.at(1).value();
    return cmpleft.get().compute(cmpleft_pin) & cmpright.get().compute(cmpright_pin);
}
