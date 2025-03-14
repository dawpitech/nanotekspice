/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4040Component.hpp
*/

#ifndef INC_4040COMPONENT_HPP
    #define INC_4040COMPONENT_HPP

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
            int _counterValue = 0;
            Tristate _clockCurrentState = Tristate::Undefined;
            Tristate _clockFutureState = Tristate::Undefined;
    };
}
#endif //INC_4040COMPONENT_HPP
