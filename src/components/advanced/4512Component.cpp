/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4512Component.cpp
*/

#include "4512Component.hpp"

void nts::components::advanced::IC4512Component::simulate(const std::size_t tick)
{
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    for (std::size_t i = 1; i <= 7; i++) {
        this->protectedLocalSimulate(i, tick);
        this->protectedLocalCompute(i);
    }
    for (std::size_t i = 9; i <= 13; i++)
        this->protectedLocalSimulate(i, tick);
    this->protectedLocalCompute(9);
    this->protectedLocalSimulate(15, tick);
}

nts::Tristate nts::components::advanced::IC4512Component::compute(const std::size_t pin)
{
    if (pin == 0 || pin > PIN_NUMBER)
        throw Exceptions::UnknownPinException();

    this->protectedLocalCompute(10);
    this->protectedLocalCompute(15);

    if (this->getLocalPin(15) == Tristate::Undefined || this->getLocalPin(10) == Tristate::Undefined)
        return Tristate::Undefined;

    // If Output Enable is pulled high, output is floating
    if (this->getLocalPin(15) == Tristate::True)
        return Tristate::Undefined;
    // If inhibit is pulled high, set the
    // return zero regardless of the inputs
    if (this->getLocalPin(10) == Tristate::True)
        return Tristate::False;

    if (pin == 8 || pin == 16)
        return Tristate::Undefined;
    if (pin != 14)
        throw Exceptions::IncorrectPinUsageException();

    const Tristate inputA = this->protectedLocalCompute(11);
    const Tristate inputB = this->protectedLocalCompute(12);
    const Tristate inputC = this->protectedLocalCompute(13);
    if (inputA == Tristate::Undefined || inputB == Tristate::Undefined || inputC == Tristate::Undefined)
        return Tristate::Undefined;
    int selectedAddr = inputC == Tristate::True ? 1 : 0;
    selectedAddr = (selectedAddr << 1) + (inputB == Tristate::True ? 1 : 0);
    selectedAddr = (selectedAddr << 1) + (inputA == Tristate::True ? 1 : 0);

    if (selectedAddr == 7)
        return this->getLocalPin(9);
    return this->getLocalPin(selectedAddr + 1);
}
