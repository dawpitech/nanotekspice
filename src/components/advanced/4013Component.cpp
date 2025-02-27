/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4013Component.cpp
*/

#include "4013Component.hpp"

void nts::components::advanced::IC4013Component::simulate(const std::size_t tick)
{
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    if (this->_connections.at(3 - 1) != std::nullopt)
        this->_connections.at(3 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(4 - 1) != std::nullopt)
        this->_connections.at(4 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(5 - 1) != std::nullopt)
        this->_connections.at(5 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(6 - 1) != std::nullopt)
        this->_connections.at(6 - 1).value().first.get().simulate(tick);

    if (this->_connections.at(8 - 1) != std::nullopt)
        this->_connections.at(8 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(9- 1) != std::nullopt)
        this->_connections.at(9 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(10 - 1) != std::nullopt)
        this->_connections.at(10 - 1).value().first.get().simulate(tick);
    if (this->_connections.at(11 - 1) != std::nullopt)
        this->_connections.at(11 - 1).value().first.get().simulate(tick);

    this->_ff1_clockOld = this->_ff1_clockNew;
    this->_ff1_clockNew = this->computePin(3);

    this->_ff2_clockOld = this->_ff2_clockNew;
    this->_ff2_clockNew = this->computePin(11);

    do {
        if (this->computePin(4) == Tristate::True &&
            this->computePin(6) == Tristate::False) {
            this->_ff1_state = Tristate::False;
            this->_ff1_state_invert = Tristate::True;
            break;
        }

        if (this->computePin(4) == Tristate::False &&
            this->computePin(6) == Tristate::True) {
            this->_ff1_state = Tristate::True;
            this->_ff1_state_invert = Tristate::False;
            break;
        }

        if (this->computePin(4) == Tristate::True &&
            this->computePin(6) == Tristate::True) {
            this->_ff1_state = Tristate::True;
            this->_ff1_state_invert = Tristate::True;
            break;
        }

        if (this->_ff1_clockOld == Tristate::False &&
            this->_ff1_clockNew == Tristate::True) {
            this->_ff1_state = this->computePin(5);
            this->_ff1_state_invert = !this->_ff1_state;
        }

        if (this->_ff1_clockNew != Tristate::Undefined)
            break;
        this->_ff1_state = Tristate::Undefined;
        this->_ff1_state_invert = Tristate::Undefined;
    } while (false);

    do {
        if (this->computePin(10) == Tristate::True &&
            this->computePin(8) == Tristate::False) {
            this->_ff1_state = Tristate::False;
            this->_ff1_state_invert = Tristate::True;
            break;
        }

        if (this->computePin(10) == Tristate::False &&
            this->computePin(8) == Tristate::True) {
            this->_ff1_state = Tristate::True;
            this->_ff1_state_invert = Tristate::False;
            break;
        }

        if (this->computePin(10) == Tristate::True &&
            this->computePin(8) == Tristate::True) {
            this->_ff1_state = Tristate::True;
            this->_ff1_state_invert = Tristate::True;
            break;
        }

        if (this->_ff1_clockOld == Tristate::False &&
            this->_ff1_clockNew == Tristate::True) {
            this->_ff1_state = this->computePin(9);
            this->_ff1_state_invert = !this->_ff1_state;
        }

        if (this->_ff1_clockNew != Tristate::Undefined)
            break;
        this->_ff1_state = Tristate::Undefined;
        this->_ff1_state_invert = Tristate::Undefined;
    } while (false);
}

nts::Tristate nts::components::advanced::IC4013Component::compute(const std::size_t pin)
{
    switch (pin) {
        case 1: return this->_ff1_state;
        case 2: return this->_ff1_state_invert;
        case 12: return this->_ff2_state_invert;
        case 13: return this->_ff2_state;
        case 7:
        case 14:
            throw Exceptions::IncorrectPinUsageException();
        default:
            throw Exceptions::UnknownPinException();
    }
}
