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
            typedef std::vector<std::optional<std::pair<std::reference_wrapper<IComponent>, std::size_t>>>
                connections_t;

            virtual ~IComponent() = default;

            virtual void simulate(std::size_t tick) = 0;
            virtual Tristate compute(std::size_t pin) = 0;
            virtual void setLink(std::size_t pin, IComponent& other,
                                 std::size_t otherPin) = 0;

            [[nodiscard]] virtual std::size_t getPinNumber() const = 0;
            [[nodiscard]] virtual connections_t& getConnections() = 0;

        protected:
            virtual Tristate computePin(std::size_t pin) = 0;
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

        class IncorrectPinUsageException final : public GenericNTSException
        {
            public:
                explicit IncorrectPinUsageException(): GenericNTSException
                    ("Incorrect usage of pin (using input as output or vice-versa)") {}
        };

        class InfiniteRecursiveLoop final : public GenericNTSException
        {
            public:
                explicit InfiniteRecursiveLoop(): GenericNTSException
                    ("Cannot simulate an infinite recursive loop, states are unclear") {}
        };
    }

    inline Tristate operator^(const Tristate lhs, const Tristate rhs)
    {
        if (lhs == Tristate::False && rhs == Tristate::False)
            return Tristate::False;
        if (lhs == Tristate::True && rhs == Tristate::True)
            return Tristate::False;
        if (lhs == Tristate::False && rhs == Tristate::True)
            return Tristate::True;
        if (lhs == Tristate::True && rhs == Tristate::False)
            return Tristate::True;
        return Tristate::Undefined;
    }

    inline Tristate operator!(const Tristate state)
    {
        switch (state)
        {
            case Tristate::False: return Tristate::True;
            case Tristate::True: return Tristate::False;
            default:
            case Tristate::Undefined: return Tristate::Undefined;
        }
    }

    inline Tristate operator&&(const Tristate lhs, const Tristate rhs)
    {
        if (lhs == Tristate::Undefined && rhs == Tristate::True)
            return Tristate::Undefined;
        if (lhs == Tristate::True && rhs == Tristate::Undefined)
            return Tristate::Undefined;
        if (lhs == Tristate::True && rhs == Tristate::True)
            return Tristate::True;
        return Tristate::False;
    }

    inline Tristate operator||(const Tristate lhs, const Tristate rhs)
    {
        if (lhs == Tristate::False && rhs == Tristate::False)
            return Tristate::False;
        if (lhs == Tristate::False && rhs == Tristate::Undefined)
            return Tristate::Undefined;
        if (lhs == Tristate::Undefined && rhs == Tristate::False)
            return Tristate::Undefined;
        if (lhs == Tristate::Undefined && rhs == Tristate::Undefined)
            return Tristate::Undefined;
        return Tristate::True;
    }

    inline Tristate nor(const Tristate lhs, const Tristate rhs)
    {
        return operator!(operator||(lhs, rhs));
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
