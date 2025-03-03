/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** ClockComponent.cpp
*/

#include "ClockComponent.hpp"

void nts::components::special::ClockComponent::simulate(const std::size_t tick)
{
    if (tick <= this->_currTick)
        return;
    this->_currTick = tick;

    this->_currentState = this->_futureState;
    this->_futureState = !this->_currentState;
}
