/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** InputComponent.hpp
*/

#ifndef INPUTCOMPONENT_HPP
    #define INPUTCOMPONENT_HPP

    #include "src/AComponent.hpp"

namespace nts::components::special
{
    class InputComponent final : public AComponent
    {
        public:
            explicit InputComponent(): AComponent(PIN_NUMBER) {}
            ~InputComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override
                { this->_curState = this->_newState; }
            Tristate compute(const std::size_t pin) override
            {
                if (pin != PIN_NUMBER)
                    throw Exceptions::UnknownPinException();
                return this->_curState;
            }

            void setState(const Tristate state) { this->_newState = state; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 1;

        protected:
            Tristate _curState = Tristate::Undefined;
            Tristate _newState = Tristate::Undefined;
    };
}
#endif //INPUTCOMPONENT_HPP
