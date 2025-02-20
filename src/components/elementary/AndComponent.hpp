/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AndComponent.hpp
*/

#ifndef ANDCOMPONENT_HPP
    #define ANDCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::gates
{
    class AndComponent final : public AComponent
    {
        public:
            explicit AndComponent(): AComponent(PIN_NUMBER) {}
            ~AndComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 3;
    };
}
#endif //ANDCOMPONENT_HPP
