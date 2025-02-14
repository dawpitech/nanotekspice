/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4001Component.cpp
*/

#include "4001Component.hpp"

void nts::components::IC4001Component::simulatePin(const std::size_t pin,
    const std::size_t tick) const
{
    if (this->_connections.at(pin - 1) != std::nullopt)
        this->_connections.at(pin - 1).value().first.get().simulate(tick);
}

void nts::components::IC4001Component::simulate(const std::size_t tick)
{
    simulatePin(1, tick);
    simulatePin(2, tick);
    simulatePin(5, tick);
    simulatePin(6, tick);
    simulatePin(8, tick);
    simulatePin(9, tick);
    simulatePin(12, tick);
    simulatePin(13, tick);
}

nts::Tristate nts::components::IC4001Component::computePin(const std::size_t pin)
{
    if (this->_connections.at(pin - 1) == std::nullopt)
        return Tristate::Undefined;
    auto [cmp, cmpPin]
        = this->_connections.at(pin - 1).value();
    return cmp.get().compute(cmpPin);
}


nts::Tristate nts::components::IC4001Component::compute(const std::size_t pin)
{
    switch (pin)
    {
        case 3:
            return nor(computePin(1), computePin(2));
        case 4:
            return nor(computePin(5), computePin(6));
        case 10:
            return nor(computePin(8), computePin(9));
        case 11:
            return nor(computePin(12), computePin(13));
        case 7:
        case 14:
            return Tristate::Undefined;
        default:
            throw Exceptions::UnknownPinException();
    }
}
