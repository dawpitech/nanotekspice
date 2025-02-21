/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** LoggerComponent.cpp
*/

#include <array>

#include "LoggerComponent.hpp"

void nts::components::special::LoggerComponent::simulate(const std::size_t tick)
{

}

nts::Tristate nts::components::special::LoggerComponent::compute(std::size_t pin)
{
    this->_oldClockState = this->_newClockState;
    this->_newClockState = this->computePin(9);

    std::array<Tristate, 8> bits{};
    char chr = true;
    for (int i = 0; i < 8; i++)
        bits.at(i) = this->computePin(i + 1);
    for (const auto& bit : bits)
    {
        if (bit == Tristate::Undefined)
        {
            return;
        }
    }
    if (chr == -1)
}

nts::Tristate nts::components::special::LoggerComponent::computePin(const std::size_t pin)
{
    if (this->_connections.at(pin - 1) == std::nullopt)
        return Tristate::Undefined;
    auto& [otherComp, otherPin] = this->_connections.at(pin - 1).value();
    return otherComp.get().compute(otherPin);
}
