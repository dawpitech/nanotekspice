/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** XorComponent.hpp
*/

#ifndef XORCOMPONENT_HPP
    #define XORCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::gates
{
    class XorComponent final : public AComponent
    {
        public:
            explicit XorComponent(): AComponent(PIN_NUMBER) {}
            ~XorComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 3;
    };
}
#endif //XORCOMPONENT_HPP
