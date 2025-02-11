/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include "components/primary/TruePrimaryComponent.hpp"

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &name)
{
    if (name == "true")
        return std::make_unique<components::primary::TruePrimaryComponent>();
    throw std::exception();
}
