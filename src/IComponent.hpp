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
            [[nodiscard]] virtual connections_t getConnections() const = 0;

        protected:
            //Tristate currentValue
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
                const char* what() const noexcept override
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
    }
}

inline std::ostream& operator<<(std::ostream& os, const nts::Tristate& state)
{
    switch (state)
    {
        case nts::Tristate::True:
            os << "True";
            break;
        case nts::Tristate::False:
            os << "False";
            break;
        case nts::Tristate::Undefined:
            os << "Undefined";
            break;
    }
    return os;
}
#endif //ICOMPONENT_HPP
