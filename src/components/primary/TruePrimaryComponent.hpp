/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** TruePrimaryComponent.hpp
*/

#ifndef TRUEPRIMARYCOMPONENT_HPP
    #define TRUEPRIMARYCOMPONENT_HPP

namespace nts::components::primary
{
    class TruePrimaryComponent final : public IComponent
    {
        void simulate(std::size_t tick) override {}
        Tristate compute(std::size_t pin) override { return Tristate::True; }
        void setLink(std::size_t pin, IComponent &other,
            std::size_t otherPin) override { throw std::exception(); }
    };
}
#endif //TRUEPRIMARYCOMPONENT_HPP
