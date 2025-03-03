/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4013Component.cpp
*/

#include "4013Component.hpp"

void nts::components::advanced::IC4013Component::updateFlipFlop(InternalFlipFlop flip_flop,
    const std::size_t tick)
{
    this->protectedLocalSimulate(flip_flop.pinClock, tick);
    this->protectedLocalSimulate(flip_flop.pinReset, tick);
    this->protectedLocalSimulate(flip_flop.pinSet, tick);
    this->protectedLocalCompute(flip_flop.pinClock);
    this->protectedLocalCompute(flip_flop.pinReset);
    this->protectedLocalCompute(flip_flop.pinSet);

    flip_flop.clockCurrentState = flip_flop.clockFutureState;
    flip_flop.clockFutureState = this->getLocalPin(flip_flop.pinClock);

    if (this->getLocalPin(flip_flop.pinReset) == Tristate::True &&
        this->getLocalPin(flip_flop.pinSet) == Tristate::False)
        return flip_flop.setState(Tristate::False);

    if (this->getLocalPin(flip_flop.pinReset) == Tristate::False &&
        this->getLocalPin(flip_flop.pinSet) == Tristate::True)
        return flip_flop.setState(Tristate::True);

    if (this->getLocalPin(flip_flop.pinReset) == Tristate::True &&
        this->getLocalPin(flip_flop.pinSet) == Tristate::True) {
        flip_flop.state = Tristate::True;
        flip_flop.state_invert = Tristate::True;
        return;
    }

    this->protectedLocalSimulate(flip_flop.pinData, tick);
    this->protectedLocalCompute(flip_flop.pinData);
    if (flip_flop.clockCurrentState == Tristate::False &&
        flip_flop.clockFutureState == Tristate::True)
        flip_flop.setState(this->getLocalPin(flip_flop.pinData));

    if (flip_flop.clockFutureState == Tristate::Undefined)
    {
        flip_flop.state = Tristate::Undefined;
        flip_flop.state_invert = Tristate::Undefined;
    }
}


void nts::components::advanced::IC4013Component::simulate(const std::size_t tick)
{
    if (tick <= this->_internalTick)
        return;
    this->_internalTick = tick;

    this->updateFlipFlop(_ff1, tick);
    this->updateFlipFlop(_ff2, tick);
}

nts::Tristate nts::components::advanced::IC4013Component::compute(const std::size_t pin)
{
    if (pin == 0 || pin > getPinNumber())
        throw Exceptions::UnknownPinException();

    switch (pin) {
        case 1: return this->_ff1.state;
        case 2: return this->_ff1.state_invert;
        case 12: return this->_ff2.state;
        case 13: return this->_ff2.state_invert;
        case 7:
        case 14:
            return Tristate::Undefined;
        default:
            throw Exceptions::IncorrectPinUsageException();
    }
}
