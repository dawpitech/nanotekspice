/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AndComponent.cpp
*/

#include "AndComponent.hpp"

void nts::components::gates::AndComponent::simulate(const std::size_t tick)
{
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    this->protectedLocalSimulate(1, tick);
    this->protectedLocalSimulate(2, tick);
}

nts::Tristate nts::components::gates::AndComponent::compute(const std::size_t pin)
{
    if (pin == 0 || pin > getPinNumber())
        throw Exceptions::UnknownPinException();
    if (pin != 3)
        throw Exceptions::IncorrectPinUsageException();

    return this->protectedLocalCompute(1) && this->protectedLocalCompute(2);
}
