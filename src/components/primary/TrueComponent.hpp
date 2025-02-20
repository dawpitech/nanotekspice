/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** TrueComponent.hpp
*/

#ifndef TRUECOMPONENT_HPP
    #define TRUECOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::primary
{
    class TrueComponent final : public AComponent
    {
        public:
            explicit TrueComponent(): AComponent(PIN_NUMBER) {}
            ~TrueComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override {}
            Tristate compute([[maybe_unused]] std::size_t pin) override { return Tristate::True; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //TRUECOMPONENT_HPP
