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
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    this->protectedLocalSimulate(1, tick);
}

nts::Tristate nts::components::gates::NotComponent::compute(const std::size_t pin)
{
    if (pin == 0 || pin > getPinNumber())
        throw Exceptions::UnknownPinException();
    if (pin != 2)
        throw Exceptions::IncorrectPinUsageException();

    return !this->protectedLocalCompute(1);
}
