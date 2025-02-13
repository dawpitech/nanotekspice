/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** FalsePrimaryComponent.hpp
*/

#ifndef FALSEPRIMARYCOMPONENT_HPP
    #define FALSEPRIMARYCOMPONENT_HPP

    #include "src/AComponent.hpp"

namespace nts::components::primary
{
    class FalsePrimaryComponent final : public AComponent
    {
        public:
            explicit FalsePrimaryComponent(): AComponent(PIN_NUMBER) {}
            ~FalsePrimaryComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override {}
            Tristate compute([[maybe_unused]] std::size_t pin) override { return Tristate::False; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //FALSEPRIMARYCOMPONENT_HPP
