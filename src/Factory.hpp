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
    #include "components/elementary/AndComponent.hpp"
    #include "components/elementary/NotComponent.hpp"
    #include "components/elementary/OrComponent.hpp"
    #include "components/elementary/XorComponent.hpp"
    #include "components/gates/4001Component.hpp"
    #include "components/primary/FalseComponent.hpp"
    #include "components/primary/TrueComponent.hpp"
    #include "components/special/ClockComponent.hpp"
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
                    return std::make_unique<components::primary::TrueComponent>();
                if (name == "false")
                    return std::make_unique<components::primary::FalseComponent>();
                if (name == "output")
                    return std::make_unique<components::special::OutputComponent>();
                if (name == "input")
                    return std::make_unique<components::special::InputComponent>();
                if (name == "clock")
                    return std::make_unique<components::special::ClockComponent>();
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
