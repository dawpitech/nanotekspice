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

    #include "components/IComponent.hpp"
    #include "components/special/InputComponent.hpp"
    #include "components/special/OutputComponent.hpp"

namespace nts
{
    class Circuit
    {
        public:
            void addComponent(const std::string& name, std::unique_ptr<IComponent> comp);
            [[nodiscard]] IComponent& getComponent(const std::string& name) const;

            bool isInCircuit(const std::string& name) const;
            std::vector<std::pair<std::string, std::reference_wrapper<components::special::OutputComponent>>>
                getOutputs() const { return this->_outputs; }
            std::vector<std::pair<std::string, std::reference_wrapper<components::special::InputComponent>>>
                getInputs() const { return this->_inputs; }
            std::vector<std::pair<std::string, std::reference_wrapper<IComponent>>>
                getComponents() const { return this->_componentsRef; }
            std::size_t getCurrentTick() const { return this->_curr_tick; }
            std::size_t upCurrentTick() { return this->_curr_tick++; }

        private:
            std::size_t _curr_tick = 0;
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
            std::vector<std::pair<std::string, std::reference_wrapper<IComponent>>>
                _componentsRef{};
            std::vector<std::pair<std::string, std::reference_wrapper<components::special::OutputComponent>>>
                _outputs{};
            std::vector<std::pair<std::string, std::reference_wrapper<components::special::InputComponent>>>
                _inputs{};
    };
}

#endif //CIRCUIT_HPP
