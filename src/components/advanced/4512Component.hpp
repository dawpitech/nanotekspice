/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4512Component.hpp
*/

#ifndef INC_4512COMPONENT_HPP
    #define INC_4512COMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::advanced
{
    class IC4512Component final : public AComponent
    {
        public:
            explicit IC4512Component(): AComponent(PIN_NUMBER) {}
            ~IC4512Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 16;
    };
}
#endif //INC_4512COMPONENT_HPP
