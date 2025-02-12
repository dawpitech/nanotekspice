/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** TruePrimaryComponent.hpp
*/

#ifndef TRUEPRIMARYCOMPONENT_HPP
    #define TRUEPRIMARYCOMPONENT_HPP

    #include "src/AComponent.hpp"

namespace nts::components::primary
{
    class TruePrimaryComponent final : public AComponent
    {
        public:
            explicit TruePrimaryComponent(): AComponent(PIN_NUMBER) {}
            ~TruePrimaryComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override {}
            Tristate compute([[maybe_unused]] std::size_t pin) override { return Tristate::True; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //TRUEPRIMARYCOMPONENT_HPP
