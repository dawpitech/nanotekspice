/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OrComponent.hpp
*/

#ifndef ORCOMPONENT_HPP
    #define ORCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::gates
{
    class OrComponent final : public AComponent
    {
        public:
            explicit OrComponent(): AComponent(PIN_NUMBER) {}
            ~OrComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 3;
    };
}
#endif //ORCOMPONENT_HPP
