/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** FalseComponent.hpp
*/

#ifndef FALSECOMPONENT_HPP
    #define FALSECOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::primary
{
    class FalseComponent final : public AComponent
    {
        public:
            explicit FalseComponent(): AComponent(PIN_NUMBER) {}
            ~FalseComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override {}
            Tristate compute([[maybe_unused]] std::size_t pin) override { return Tristate::False; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //FALSECOMPONENT_HPP
