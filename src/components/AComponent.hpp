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
            Tristate computePin(const std::size_t pin) override
            {
                if (this->_connections.at(pin - 1) == std::nullopt)
                    return Tristate::Undefined;

                auto& [otherComp, otherPin]
                    = this->_connections.at(pin - 1).value();
                return otherComp.get().compute(otherPin);
            }
    };
}
#endif //ACOMPONENT_HPP
