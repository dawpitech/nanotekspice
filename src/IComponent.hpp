/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** IComponent.hpp
*/

#ifndef ICOMPONENT_HPP
    #define ICOMPONENT_HPP

    #include <cstddef>
    #include <list>
    #include <optional>
    #include <vector>

namespace nts
{
    enum class Tristate
    {
        Undefined = -true,
        True = true,
        False = false,
    };

    // ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
    class IComponent
    {
        public:
            typedef std::vector<std::optional<std::pair<std::reference_wrapper<IComponent>, std::size_t>>> connections_t;

            virtual ~IComponent() = default;

            virtual void simulate(std::size_t tick) = 0;
            virtual Tristate compute(std::size_t pin) = 0;
            virtual void setLink(std::size_t pin, IComponent &other,
                std::size_t otherPin) = 0;

            [[nodiscard]] virtual std::size_t getPinNumber() const = 0;
            [[nodiscard]] virtual connections_t& getConnections() = 0;

        protected:
            std::vector<Tristate> _currentPinStates;
            connections_t _connections;
    };

    namespace Exceptions
    {
        class GenericNTSException : public std::exception
        {
            public:
                explicit GenericNTSException(const std::string& what)
                {
                    this->_what = what;
                }
                [[nodiscard]] const char* what() const noexcept override
                {
                    return this->_what.c_str();
                }

            protected:
                std::string _what;
        };

        class UnknownPinException final : public GenericNTSException
        {
            public:
                explicit UnknownPinException(): GenericNTSException("Unknown pin used") {}
        };

        class UnknownChipException final : public GenericNTSException
        {
            public:
                explicit UnknownChipException(): GenericNTSException("Unknown chip used") {}
        };
    }
}

inline std::ostream& operator<<(std::ostream& os, const nts::Tristate& state)
{
    switch (state)
    {
        case nts::Tristate::True:
            os << "1";
            break;
        case nts::Tristate::False:
            os << "0";
            break;
        case nts::Tristate::Undefined:
            os << "U";
            break;
    }
    return os;
}
#endif //ICOMPONENT_HPP
