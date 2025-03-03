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
            class InternalFlipFlop
            {
                public:
                    InternalFlipFlop(const std::size_t pin_State,
                        const std::size_t pin_StateInvert,
                        const std::size_t pin_Clock,
                        const std::size_t pin_Reset,
                        const std::size_t pin_Data,
                        const std::size_t pin_Set)
                    {
                        this->pinState = pin_State;
                        this->pinStateInvert = pin_StateInvert;
                        this->pinClock = pin_Clock;
                        this->pinReset = pin_Reset;
                        this->pinData = pin_Data;
                        this->pinSet = pin_Set;
                    }

                    void setState(const Tristate newState)
                    {
                        this->state = newState;
                        this->state_invert = !newState;
                    }

                    Tristate state = Tristate::Undefined;
                    Tristate state_invert = Tristate::Undefined;
                    Tristate clockCurrentState = Tristate::Undefined;
                    Tristate clockFutureState = Tristate::Undefined;

                    std::size_t pinState = 0;
                    std::size_t pinStateInvert = 0;
                    std::size_t pinClock = 0;
                    std::size_t pinReset = 0;
                    std::size_t pinData = 0;
                    std::size_t pinSet = 0;
            };

            InternalFlipFlop _ff1 = InternalFlipFlop(1, 2, 3, 4, 5, 6);
            InternalFlipFlop _ff2 = InternalFlipFlop(13, 12, 11, 10, 9, 8);

            void updateFlipFlop(InternalFlipFlop flip_flop, std::size_t tick);
    };
};
#endif //INC_4013COMPONENT_HPP
