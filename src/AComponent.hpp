/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AComponent.hpp
*/

#ifndef ACOMPONENT_HPP
    #define ACOMPONENT_HPP
#include <iostream>

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
    };
}
#endif //ACOMPONENT_HPP
