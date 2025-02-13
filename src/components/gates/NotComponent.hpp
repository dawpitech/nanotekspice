/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** NotComponent.hpp
*/

#ifndef NOTCOMPONENT_HPP
    #define NOTCOMPONENT_HPP

namespace nts::components::gates
{
    class NotComponent final : public AComponent
    {
        public:
            explicit NotComponent(): AComponent(PIN_NUMBER) {}
            ~NotComponent() override = default;

            void simulate(const std::size_t tick) override
            {
                if (this->_connections.at(0) == std::nullopt)
                    return;
                this->_connections.at(0).value().first.get().simulate(tick);
            }
            Tristate compute([[maybe_unused]] const std::size_t pin) override
            {
                if (pin != 2)
                    //TODO make better exception when compute is called on an input pin
                    throw std::exception();
                if (this->_connections.at(0) == std::nullopt)
                    return Tristate::Undefined;
                auto [component, pinOther] = this->_connections.at(0).value();
                return !component.get().compute(pinOther);
            }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 2;
    };
}
#endif //NOTCOMPONENT_HPP
