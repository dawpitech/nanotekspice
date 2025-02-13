/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OutputComponent.hpp
*/

#ifndef OUTPUTCOMPONENT_HPP
    #define OUTPUTCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::special
{
    class OutputComponent final : public AComponent
    {
        public:
            explicit OutputComponent(): AComponent(PIN_NUMBER) {}
            ~OutputComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //OUTPUTCOMPONENT_HPP
