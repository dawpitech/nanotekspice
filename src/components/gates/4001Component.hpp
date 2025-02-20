/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** 4001Component.hpp
*/

#ifndef INC_4001COMPONENT_HPP
    #define INC_4001COMPONENT_HPP

    #include <map>

    #include "../AAdvancedComponent.hpp"

namespace nts::components
{
    class IC4001Component final : public AAdvancedComponent
    {
        public:
            explicit IC4001Component();
            ~IC4001Component() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            [[nodiscard]] std::size_t getPinNumber() const override { return PIN_NUMBER; }
            constexpr static std::size_t PIN_NUMBER = 14;
            [[nodiscard]] std::unordered_map<std::size_t, std::pair<std::string, std::size_t>> getInternalPinBinds()
                override { return INTERNAL_PIN_BINDS; }
            const static std::unordered_map<std::size_t, std::pair<std::string, std::size_t>> INTERNAL_PIN_BINDS;
    };
}

#endif //INC_4001COMPONENT_HPP
