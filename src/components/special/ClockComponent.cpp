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
    this->_curState = this->_newState;
    this->_newState = !this->_curState;
    this->_currTick = tick;
}
