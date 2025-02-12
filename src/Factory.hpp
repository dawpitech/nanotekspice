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
    #include "components/primary/TruePrimaryComponent.hpp"
    #include "components/special/OutputComponent.hpp"

namespace nts
{
    class Factory
    {
        public:
            static std::unique_ptr<IComponent> createComponent(const std::string& name)
            {
                if (name == "true")
                    return std::make_unique<components::primary::TruePrimaryComponent>();
                if (name == "output")
                    return std::make_unique<components::special::OutputComponent>();
                throw std::exception();
            }
    };
}
#endif //FACTORY_HPP
