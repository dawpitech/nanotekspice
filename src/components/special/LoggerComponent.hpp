/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** LoggerComponent.hpp
*/

#ifndef LOGGERCOMPONENT_HPP
    #define LOGGERCOMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components::special
{
    class LoggerComponent final : public AComponent
    {
        public:
            explicit LoggerComponent(): AComponent(PIN_NUMBER) {}
            ~LoggerComponent() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 10;

        protected:
            Tristate computePin(std::size_t pin);
            Tristate _oldClockState = Tristate::Undefined;
            Tristate _newClockState = Tristate::Undefined;
    };
}
#endif //LOGGERCOMPONENT_HPP
