/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4040Component.hpp
*/

#ifndef INC_4040COMPONENT_HPP
    #define INC_4040COMPONENT_HPP

    #include <array>

    #include "../AComponent.hpp"

namespace nts::components::advanced
{
    class IC4040Component final : public AComponent
    {
        public:
            explicit IC4040Component(): AComponent(PIN_NUMBER) {}
            ~IC4040Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 16;

        private:
            std::array<bool, PIN_NUMBER> _was_computed;
            std::array<Tristate, PIN_NUMBER> _pinStates;
            int _counterValue = 0;
            Tristate _curState = Tristate::Undefined;
            Tristate _newState = Tristate::Undefined;
    };
}
#endif //INC_4040COMPONENT_HPP
