/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** AAdvancedComponent.hpp
*/

#ifndef AADVANCEDCOMPONENT_HPP
    #define AADVANCEDCOMPONENT_HPP

    // ReSharper disable once CppUnusedIncludeDirective
    #include <format>

    #include "AComponent.hpp"
    #include "../Circuit.hpp"
    #include "../Debug.hpp"

namespace nts
{
    class AAdvancedComponent : public AComponent
    {
        public:
            explicit AAdvancedComponent(const std::size_t pinNb): AComponent(pinNb) {}

            [[nodiscard]] virtual std::unordered_map<std::size_t, std::pair<std::string, std::size_t>> getInternalPinBinds() = 0;

        protected:
            Circuit _internalCircuit;
            void updateLinks()
            {
                for (std::size_t pinIdx = 0; pinIdx < getPinNumber(); pinIdx++)
                {
                    if (this->_connections.at(pinIdx) == std::nullopt)
                        continue;

                    if (!this->getInternalPinBinds().contains(pinIdx + 1))
                        continue;

                    auto& [externalComp, externalPin] = this->_connections.at(pinIdx).value();
                    auto& [internalCompName, internalPin] = this->getInternalPinBinds().at(pinIdx + 1);
                    auto& internalComp = this->_internalCircuit.getComponent(internalCompName);

                    DEBUG_PRINT(std::format("[AAdvancedComponent] Linking external pin {} with internal pin {} of chip {}\n",
                        pinIdx, internalPin, internalCompName));
                    externalComp.get().setLink(externalPin, internalComp, internalPin);

                    this->_connections.at(pinIdx) = std::nullopt;
                }
            }
    };
}
#endif //AADVANCEDCOMPONENT_HPP
