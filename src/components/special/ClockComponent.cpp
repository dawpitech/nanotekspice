/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** ClockComponent.cpp
*/

#include "ClockComponent.hpp"

void nts::components::special::ClockComponent::simulate(std::size_t tick)
{
    this->_curState = this->_newState;
    this->_newState = !this->_curState;
}
