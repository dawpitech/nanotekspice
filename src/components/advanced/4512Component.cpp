/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4512Component.cpp
*/

#include "4512Component.hpp"

void nts::components::advanced::IC4512Component::simulate(const std::size_t tick)
{
    for (std::size_t i = 0; i < PIN_NUMBER; i++) {
        // skip, VSS, Z and VDD
        if (i == 7 || i == 13 || i == 15)
            continue;
        if (this->_connections.at(i) != std::nullopt)
            this->_connections.at(i).value().first.get().simulate(tick);
    }
}

nts::Tristate nts::components::advanced::IC4512Component::compute(const std::size_t pin)
{
    if (pin == 0 || pin > PIN_NUMBER)
        throw Exceptions::UnknownPinException();

    if (this->computePin(15) == Tristate::Undefined
        || this->computePin(10) == Tristate::Undefined)
        return Tristate::Undefined;

    // If Output Enable is pulled high, set the output as floating
    if (this->computePin(15) == Tristate::True)
        return Tristate::Undefined;
    // If inhibit is pulled high, set the
    // output as zero regardless of the inputs
    if (this->computePin(10) == Tristate::True)
        return Tristate::False;

    if (pin == 8 || pin == 16)
        return Tristate::Undefined;
    if (pin != 14)
        throw Exceptions::IncorrectPinUsageException();
    const Tristate inputA = this->computePin(11);
    const Tristate inputB = this->computePin(12);
    const Tristate inputC = this->computePin(13);
    if (inputA == Tristate::Undefined || inputB == Tristate::Undefined
        || inputC == Tristate::Undefined)
        return Tristate::Undefined;
    int selectedAddr = inputC == Tristate::True ? 1 : 0;
    selectedAddr = (selectedAddr << 1) + (inputB == Tristate::True ? 1 : 0);
    selectedAddr = (selectedAddr << 1) + (inputA == Tristate::True ? 1 : 0);
    if (selectedAddr == 7)
        return this->computePin(9);
    return this->computePin(selectedAddr + 1);
}
