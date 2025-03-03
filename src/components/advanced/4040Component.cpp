/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4040Component.cpp
*/

#include "4040Component.hpp"

void nts::components::advanced::IC4040Component::simulate(const std::size_t tick)
{
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    this->protectedLocalSimulate(11, tick);
    this->protectedLocalSimulate(10, tick);

    this->_clockCurrentState = this->_clockFutureState;
    this->_clockFutureState = this->protectedLocalCompute(10);
    if (this->_clockCurrentState == Tristate::True &&
        this->_clockFutureState == Tristate::False)
        this->_counterValue++;

    if (this->protectedLocalCompute(11) == Tristate::True)
        this->_counterValue = 0;

    this->setLocalPin(1, this->_counterValue >> 11 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(2, this->_counterValue >> 5 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(3, this->_counterValue >> 4 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(4, this->_counterValue >> 6 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(5, this->_counterValue >> 3 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(6, this->_counterValue >> 2 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(7, this->_counterValue >> 1 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(9, this->_counterValue >> 0 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(12, this->_counterValue >> 8 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(13, this->_counterValue >> 7 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(14, this->_counterValue >> 9 & 1 ? Tristate::True : Tristate::False);
    this->setLocalPin(15, this->_counterValue >> 10 & 1 ? Tristate::True : Tristate::False);
}

nts::Tristate nts::components::advanced::IC4040Component::compute(const std::size_t pin)
{
    if (pin == 0 || pin > PIN_NUMBER)
        throw Exceptions::UnknownPinException();

    if (this->getLocalPin(11 -1) == Tristate::Undefined)
        return Tristate::Undefined;

    if (this->getLocalPin(11) == Tristate::True)
        return Tristate::False;

    if (pin == 10 || pin == 11)
        throw Exceptions::IncorrectPinUsageException();
    return this->getLocalPin(pin);
}
