/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Factory.hpp
*/

#ifndef FACTORY_HPP
    #define FACTORY_HPP

    #include <memory>

    #include "components/IComponent.hpp"
    #include "components/gates/AndComponent.hpp"
    #include "components/gates/NotComponent.hpp"
    #include "components/gates/OrComponent.hpp"
    #include "components/gates/XorComponent.hpp"
    #include "components/gatesIC/4001Component.hpp"
    #include "components/primary/FalsePrimaryComponent.hpp"
    #include "components/primary/TruePrimaryComponent.hpp"
    #include "components/special/InputComponent.hpp"
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
                if (name == "false")
                    return std::make_unique<components::primary::FalsePrimaryComponent>();
                if (name == "output")
                    return std::make_unique<components::special::OutputComponent>();
                if (name == "input")
                    return std::make_unique<components::special::InputComponent>();
                if (name == "not")
                    return std::make_unique<components::gates::NotComponent>();
                if (name == "xor")
                    return std::make_unique<components::gates::XorComponent>();
                if (name == "and")
                    return std::make_unique<components::gates::AndComponent>();
                if (name == "or")
                    return std::make_unique<components::gates::OrComponent>();
                if (name == "4001")
                    return std::make_unique<components::IC4001Component>();
                throw std::exception();
            }
    };
}
#endif //FACTORY_HPP
