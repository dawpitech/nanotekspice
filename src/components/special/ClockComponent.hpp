/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** ClockComponent.hpp
*/

#ifndef CLOCKCOMPONENT_HPP
    #define CLOCKCOMPONENT_HPP

    #include "InputComponent.hpp"

namespace nts::components::special
{
    class ClockComponent final : public InputComponent
    {
        public:
            explicit ClockComponent() = default;
            ~ClockComponent() override = default;

            void simulate(std::size_t tick) override;
    };
}
#endif //CLOCKCOMPONENT_HPP
