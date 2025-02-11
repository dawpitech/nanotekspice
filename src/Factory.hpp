/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Factory.hpp
*/

#ifndef FACTORY_HPP
    #define FACTORY_HPP

    #include <memory>

    #include "IComponent.hpp"

namespace nts
{
    class Factory
    {
        public:
            static std::unique_ptr<IComponent> createComponent(const std::string &name);
    };
}
#endif //FACTORY_HPP
