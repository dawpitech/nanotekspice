/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Circuit.hpp
*/

#ifndef CIRCUIT_HPP
    #define CIRCUIT_HPP

    #include <memory>
    #include <string>
    #include <unordered_map>

    #include "IComponent.hpp"

namespace nts
{
    class Circuit
    {
        public:
            void addComponent(const std::string& name, std::unique_ptr<IComponent> comp);
            std::unique_ptr<IComponent> getComponent(const std::string& name);

        private:
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
    };
}

#endif //CIRCUIT_HPP
