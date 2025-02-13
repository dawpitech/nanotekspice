/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** OutputComponent.hpp
*/

#ifndef OUTPUTCOMPONENT_HPP
    #define OUTPUTCOMPONENT_HPP

    #include "src/IComponent.hpp"

namespace nts::components::special
{
    class OutputComponent final : public AComponent
    {
        public:
            explicit OutputComponent(): AComponent(PIN_NUMBER) {}
            ~OutputComponent() override = default;

            void simulate(const std::size_t tick) override
            {
                if (this->_connections.at(0) == std::nullopt)
                    return;
                this->_connections.at(0).value().first.get().simulate(tick);
            }

            Tristate compute(const std::size_t pin) override
            {
                if (pin != 1)
                    throw Exceptions::UnknownPinException();
                if (this->_connections.at(0) == std::nullopt)
                    return Tristate::Undefined;
                auto [component, pinOther] = this->_connections.at(0).value();
                return component.get().compute(pinOther);
            }

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }

            constexpr static std::size_t PIN_NUMBER = 1;
    };
}
#endif //OUTPUTCOMPONENT_HPP
