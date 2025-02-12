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
    #include "components/special/InputComponent.hpp"
    #include "components/special/OutputComponent.hpp"

namespace nts
{
    class Circuit
    {
        public:
            void addComponent(const std::string& name, std::unique_ptr<IComponent> comp);
            IComponent& getComponent(const std::string& name) const;

        private:
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
            std::vector<std::reference_wrapper<components::special::OutputComponent>> _outputs;
            std::vector<std::reference_wrapper<components::special::InputComponent>> _inputs;
    };
}

#endif //CIRCUIT_HPP
