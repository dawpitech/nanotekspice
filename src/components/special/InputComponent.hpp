/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** InputComponent.hpp
*/

#ifndef INPUTCOMPONENT_HPP
    #define INPUTCOMPONENT_HPP

    #include "src/IComponent.hpp"

namespace nts::components::special
{
    class InputComponent final : public AComponent
    {
        public:
            explicit InputComponent(): AComponent(PIN_NUMBER) {}
            ~InputComponent() override = default;

            void simulate([[maybe_unused]] std::size_t tick) override {}
            Tristate compute([[maybe_unused]] const std::size_t pin) override { return this->_currentPinStates[0]; }

            void setState(const Tristate state) { this->_currentPinStates[0] = state; }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //INPUTCOMPONENT_HPP
