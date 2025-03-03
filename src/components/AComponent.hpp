/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AComponent.hpp
*/

#ifndef ACOMPONENT_HPP
    #define ACOMPONENT_HPP

    #include <iostream>

    #include "IComponent.hpp"

namespace nts
{
    class AComponent : public IComponent
    {
        public:
            explicit AComponent(const std::size_t pinNb)
            {
                this->_connections.resize(pinNb);
                this->_connections.assign(pinNb, std::nullopt);
                this->_pinStates.resize(pinNb);
                this->_pinStates.assign(pinNb, Tristate::Undefined);
            }

            void setLink(const std::size_t pin, IComponent& other, std::size_t otherPin) override
            {
                if (pin > this->getPinNumber() || otherPin > other.getPinNumber())
                    throw Exceptions::UnknownPinException();
                if (pin == 0 || otherPin == 0)
                    throw Exceptions::UnknownPinException();

                this->getConnections()[pin - 1] = std::make_optional(
                    std::make_pair(std::ref(other), otherPin)
                );
                other.getConnections()[otherPin - 1] = std::make_optional(
                    std::make_pair(std::ref(*this), pin)
                );
            }

            [[nodiscard]] connections_t& getConnections() override
            {
                return this->_connections;
            }


        protected:
            Tristate protectedLocalCompute(const std::size_t pin) override
            {
                if (this->_connections.at(pin - 1) == std::nullopt)
                    return Tristate::Undefined;

                auto& [otherComp, otherPin]
                    = this->_connections.at(pin - 1).value();
                this->setLocalPin(pin, otherComp.get().compute(otherPin));
                return this->getLocalPin(pin);
            }

            void protectedLocalSimulate(const std::size_t pin, const std::size_t tick) override
            {
                if (pin == 0 || pin > getPinNumber())
                    throw Exceptions::UnknownPinException();
                if (this->_connections.at(pin - 1) != std::nullopt)
                    this->_connections.at(pin - 1).value().first.get().simulate(tick);
            }

            void setLocalPin(const std::size_t pin, const Tristate state) override
            {
                if (pin == 0 || pin > getPinNumber())
                    throw Exceptions::UnknownPinException();
               this->_pinStates.at(pin - 1) = state;
            }

            Tristate getLocalPin(const std::size_t pin) override
            {
                if (pin == 0 || pin > getPinNumber())
                    throw Exceptions::UnknownPinException();
                return this->_pinStates.at(pin - 1);
            }
    };
}
#endif //ACOMPONENT_HPP
