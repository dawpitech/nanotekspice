/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Circuit.cpp
*/

#include "Circuit.hpp"

#include <iostream>
#include <memory>
#include <unordered_map>

#include "IComponent.hpp"

namespace nts
{
    class Circuit
    {
        public:
            Circuit();
            ~Circuit() = default;
            void addComponent(std::string name, std::unique_ptr<IComponent> comp)
            {
                this->_components.insert(std::make_pair(name, comp));
            }
            std::unique_ptr<IComponent> getComponent(const std::string& name)
            {
                try
                {
                    return std::move(this->_components.at(name));
                } catch (std::exception& e)
                {
                    std::cerr << e.what();
                    return nullptr;
                }
            }

        private:
            std::pmr::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
    };

    Circuit::Circuit()
    {
        this->_components = {};
    }
}
