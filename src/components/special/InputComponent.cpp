/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** InputComponent.cpp
*/

#include "InputComponent.hpp"

void nts::components::special::InputComponent::simulate([[maybe_unused]] std::size_t tick)
{
    this->_curState = this->_newState;
}

nts::Tristate nts::components::special::InputComponent::compute(const std::size_t pin)
{
    if (pin != PIN_NUMBER)
        throw Exceptions::UnknownPinException();
    return this->_curState;
}
