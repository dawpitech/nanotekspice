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

    if (this->_connections.at(11 - 1) != std::nullopt)
        this->_connections.at(11 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(10 - 1) != std::nullopt)
        this->_connections.at(10 - 1).value().first.get().simulate(tick);

    this->_curState = this->_newState;
    this->_newState = this->computePin(10);
    if (this->_curState == Tristate::True &&
        this->_newState == Tristate::False)
        this->_counterValue++;

    if (this->_pinStates.at(11 -1) == Tristate::True)
        this->_counterValue = 0;

    this->_pinStates.at(1 - 1) = this->_counterValue >> 11 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(2 - 1) = this->_counterValue >> 5 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(3 - 1) = this->_counterValue >> 4 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(4 - 1) = this->_counterValue >> 6 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(5 - 1) = this->_counterValue >> 3 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(6 - 1) = this->_counterValue >> 2 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(7 - 1) = this->_counterValue >> 1 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(8 - 1) = Tristate::Undefined;
    this->_pinStates.at(9 - 1) = this->_counterValue >> 0 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(12 - 1) = this->_counterValue >> 8 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(13 - 1) = this->_counterValue >> 7 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(14 - 1) = this->_counterValue >> 9 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(15 - 1) = this->_counterValue >> 10 & 1 ? Tristate::True : Tristate::False;
    this->_pinStates.at(16 - 1) = Tristate::Undefined;
}

nts::Tristate nts::components::advanced::IC4040Component::compute(const std::size_t pin)
{
    if (pin == 0 || pin > PIN_NUMBER)
        throw Exceptions::UnknownPinException();

    if (this->_pinStates.at(11 -1) == Tristate::Undefined)
        return Tristate::Undefined;

    if (this->_pinStates.at(11 -1) == Tristate::True) {
        return Tristate::False;
    }

    if (pin == 10 || pin == 11)
        throw Exceptions::IncorrectPinUsageException();
    return this->_pinStates.at(pin - 1);
}
