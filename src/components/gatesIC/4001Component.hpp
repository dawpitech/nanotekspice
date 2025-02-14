/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4001Component.hpp
*/

#ifndef INC_4001COMPONENT_HPP
    #define INC_4001COMPONENT_HPP

    #include "../AComponent.hpp"

namespace nts::components
{
    class IC4001Component final : public AComponent
    {
        public:
            explicit IC4001Component(): AComponent(PIN_NUMBER) {}
            ~IC4001Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 14;

        protected:
            std::size_t lastTick = 0;
            Tristate computePin(std::size_t pin);
            void simulatePin(std::size_t pin, std::size_t tick) const;
    };
}

#endif //INC_4001COMPONENT_HPP
