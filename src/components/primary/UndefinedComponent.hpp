/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** UndefinedComponent.hpp
*/

#ifndef UNDEFINEDCOMPONENT_HPP
    #define UNDEFINEDCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::primary
{
    class UndefinedComponent final : public AComponent
    {
        public:
        explicit UndefinedComponent(): AComponent(PIN_NUMBER) {}
        ~UndefinedComponent() override = default;

        void simulate([[maybe_unused]] std::size_t tick) override {}
        Tristate compute([[maybe_unused]] std::size_t pin) override { return Tristate::Undefined; }

        [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
        constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //UNDEFINEDCOMPONENT_HPP
