/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** InputComponent.hpp
*/

#ifndef INPUTCOMPONENT_HPP
    #define INPUTCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::special
{
    class InputComponent final : public AComponent
    {
        public:
            explicit InputComponent(): AComponent(PIN_NUMBER) {}
            ~InputComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 1;

            void setState(const Tristate state) { this->_newState = state; }

        protected:
            Tristate _curState = Tristate::Undefined;
            Tristate _newState = Tristate::Undefined;
    };
}
#endif //INPUTCOMPONENT_HPP
