/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4013Component.hpp
*/

#ifndef INC_4013COMPONENT_HPP
    #define INC_4013COMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::advanced
{
    class IC4013Component final : public AComponent
    {
        public:
            explicit IC4013Component(): AComponent(PIN_NUMBER) {}
            ~IC4013Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 14;

        private:
            Tristate _ff1_state = Tristate::Undefined;
            Tristate _ff1_state_invert = Tristate::Undefined;
            Tristate _ff1_clockOld = Tristate::Undefined;
            Tristate _ff1_clockNew = Tristate::Undefined;

            Tristate _ff2_state = Tristate::Undefined;
            Tristate _ff2_state_invert = Tristate::Undefined;
            Tristate _ff2_clockOld = Tristate::Undefined;
            Tristate _ff2_clockNew = Tristate::Undefined;
    };
};
#endif //INC_4013COMPONENT_HPP
