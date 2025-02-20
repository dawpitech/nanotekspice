/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** NotComponent.cpp
*/

#include <optional>

#include "NotComponent.hpp"

void nts::components::gates::NotComponent::simulate(const std::size_t tick)
{
    if (this->_connections.at(0) == std::nullopt)
        return;
    this->_connections.at(0).value().first.get().simulate(tick);
}

nts::Tristate nts::components::gates::NotComponent::compute(const std::size_t pin)
{
    if (pin != 2)
        throw Exceptions::IncorrectPinUsageException();
    if (this->_connections.at(0) == std::nullopt)
        return Tristate::Undefined;
    auto [component, pinOther] = this->_connections.at(0).value();
    return !component.get().compute(pinOther);
}
