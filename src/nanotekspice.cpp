/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** nanotekspice.cpp
*/

#include <exception>
#include <iostream>
#include <memory>

#include "Circuit.hpp"
#include "Factory.hpp"
#include "IComponent.hpp"
#include "parser.hpp"
#include "src/components/special/InputComponent.hpp"

int main(const int argc, const char** argv)
{
    if (argc != 2)
        return 84;

    nts::Circuit circuit;
    nts::Parser p(circuit);

    try {
            p.parse_file(argv[1]);
    } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 84;
    }

    std::cout << "> ";
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            std::cout << "> ";
            continue;
        }
        nts::ParserUtils::trim_string(line);
        if (line == "exit")
            break;
        if (line == "simulate")
        {
            circuit.upCurrentTick();
            const auto newTick = circuit.getCurrentTick();

            for (const auto&[name, out] : circuit.getOutputs())
                out.get().simulate(newTick);
            std::cout << "> ";
            continue;
        }
        if (line == "display")
        {
            std::cout << "tick: " << circuit.getCurrentTick() << std::endl;
            std::cout << "input(s):\n";
            for (const auto&[name, in] : circuit.getInputs())
                std::cout << "\t" << name << ": " << in.get().compute(1) << "\n";
            std::cout << "output(s):\n";
            for (const auto&[name, out] : circuit.getOutputs())
                std::cout << "\t" << name << ": " << out.get().compute(1) << "\n";
            std::cout << "> ";
            continue;
        }
        if (line.find('=') != std::string::npos) {
            std::string left, right;
            nts::Tristate state;
            try {
                nts::ParserUtils::split_in_half(line, left, right, '=');
            } catch (...) {
                std::cout << "Bad command format." << std::endl << "> ";
                continue;
            }
            if (left.empty() || right.empty()) {
                std::cout << "Bad command format." << std::endl << "> ";
                continue;
            }

            if (right == "0") {
                state = nts::Tristate::False;
            } else if (right == "1") {
                state = nts::Tristate::True;
            } else if (right == "U") {
                state = nts::Tristate::Undefined;
            } else {
                std::cout << right << " is not a valid Tristate." << std::endl << "> ";
                continue;
            }
	    try {
		nts::IComponent &c = circuit.getComponent(left);
		auto& rawPtr = dynamic_cast<nts::components::special::InputComponent&>(c);
		rawPtr.setState(state);
	    } catch (...) {
		std::cout << left << " is not a valid input component." << std::endl << "> ";
		continue;
	    }
            std::cout << "> ";
            continue;
        }
        std::cout << "Unknown command: " << line << std::endl << "> ";
    }

    return 0;
};
