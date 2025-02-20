/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4001Component.hpp
*/

#ifndef INC_4001COMPONENT_HPP
    #define INC_4001COMPONENT_HPP

    #include <map>

    #include "../AComponent.hpp"
    #include "../../Circuit.hpp"

namespace nts::components
{
    class IC4001Component final : public AComponent
    {
        public:
            explicit IC4001Component();
            ~IC4001Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 14;
            const static std::map<std::size_t, std::pair<std::string, std::size_t>> INTERNAL_PIN_BINDS;

        protected:
            Circuit _internalCircuit;
            void updateLinks();
    };
}

#endif //INC_4001COMPONENT_HPP
