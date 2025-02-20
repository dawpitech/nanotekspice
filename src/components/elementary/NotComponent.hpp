/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** NotComponent.hpp
*/

#ifndef NOTCOMPONENT_HPP
    #define NOTCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::gates
{
    class NotComponent final : public AComponent
    {
        public:
            explicit NotComponent(): AComponent(PIN_NUMBER) {}
            ~NotComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 2;
    };
}
#endif //NOTCOMPONENT_HPP
