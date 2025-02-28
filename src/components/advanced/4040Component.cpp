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
}

nts::Tristate nts::components::advanced::IC4040Component::compute(const std::size_t pin)
{
    if (this->was_computed) {
        this->was_computed = false;
        return Tristate::Undefined;
    }
    this->was_computed = true;
    if (pin == 0 || pin > PIN_NUMBER)
        throw Exceptions::UnknownPinException();

    if (this->computePin(11) == Tristate::Undefined)
        return Tristate::Undefined;

    if (this->computePin(11) == Tristate::True) {
        this->_counterValue = 0;
        return Tristate::False;
    }

    switch (pin)
    {
        case 1: return this->_counterValue >> 11 & 1 ? Tristate::True : Tristate::False;
        case 2: return this->_counterValue >> 5 & 1 ? Tristate::True : Tristate::False;
        case 3: return this->_counterValue >> 4 & 1 ? Tristate::True : Tristate::False;
        case 4: return this->_counterValue >> 6 & 1 ? Tristate::True : Tristate::False;
        case 5: return this->_counterValue >> 3 & 1 ? Tristate::True : Tristate::False;
        case 6: return this->_counterValue >> 2 & 1 ? Tristate::True : Tristate::False;
        case 7: return this->_counterValue >> 1 & 1 ? Tristate::True : Tristate::False;
        case 9: return this->_counterValue >> 0 & 1 ? Tristate::True : Tristate::False;
        case 12: return this->_counterValue >> 8 & 1 ? Tristate::True : Tristate::False;
        case 13: return this->_counterValue >> 7 & 1 ? Tristate::True : Tristate::False;
        case 14: return this->_counterValue >> 9 & 1 ? Tristate::True : Tristate::False;
        case 15: return this->_counterValue >> 10 & 1 ? Tristate::True : Tristate::False;
        case 10:
        case 11:
            throw Exceptions::IncorrectPinUsageException();
        case 8:
        case 16:
            return Tristate::Undefined;
        default:
            throw Exceptions::UnknownPinException();
    }
}
