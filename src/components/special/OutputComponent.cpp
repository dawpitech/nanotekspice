/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OutputComponent.cpp
*/

#include "OutputComponent.hpp"

void nts::components::special::OutputComponent::simulate(const std::size_t tick)
{
    this->protectedLocalSimulate(1, tick);
}

nts::Tristate nts::components::special::OutputComponent::compute(const std::size_t pin)
{
    if (pin != PIN_NUMBER)
        throw Exceptions::UnknownPinException();
    return this->protectedLocalCompute(1);
}
