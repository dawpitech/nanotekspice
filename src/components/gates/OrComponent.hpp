/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OrComponent.hpp
*/

#ifndef ORCOMPONENT_HPP
    #define ORCOMPONENT_HPP

namespace nts::components::gates
{
    class OrComponent final : public AComponent
    {
        public:
        explicit OrComponent(): AComponent(PIN_NUMBER) {}
        ~OrComponent() override = default;

        void simulate(const std::size_t tick) override
        {
            if (this->_connections.at(0) != std::nullopt)
                this->_connections.at(0).value().first.get().simulate(tick);
            if (this->_connections.at(1) != std::nullopt)
                this->_connections.at(1).value().first.get().simulate(tick);
        }
        Tristate compute(const std::size_t pin) override
        {
            if (pin != 3)
                //TODO make better exception when compute is called on an input pin
                    throw std::exception();
            if (this->_connections.at(0) == std::nullopt ||
                this->_connections.at(1) == std::nullopt)
                return Tristate::Undefined;
            auto [cmpleft, cmpleft_pin] = this->_connections.at(0).value();
            auto [cmpright, cmpright_pin] = this->_connections.at(1).value();
            return cmpleft.get().compute(cmpleft_pin) | cmpright.get().compute(cmpright_pin);
        }

        [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

        constexpr static std::size_t PIN_NUMBER = 3;
    };
}
#endif //ORCOMPONENT_HPP
