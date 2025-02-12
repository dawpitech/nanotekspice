/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AComponent.hpp
*/

#ifndef ACOMPONENT_HPP
    #define ACOMPONENT_HPP
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
                this->_connections[pin - 1] = std::make_optional(
                    std::make_pair(std::ref(other), otherPin)
                );
            }
    };
}
#endif //ACOMPONENT_HPP
