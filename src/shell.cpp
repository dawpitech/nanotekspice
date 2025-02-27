#include "shell.hpp"
#include <iostream>
#include "parser.hpp"
#include <csignal>
#include <algorithm>

std::atomic<bool> nts::shell::running{true};

void nts::shell::signal_handler(int) {
    running = false;
}

void nts::shell::simulate() {
    circuit.upCurrentTick();
    const auto newTick = circuit.getCurrentTick();

    for (const auto&[name, out] : circuit.getOutputs())
	out.get().simulate(newTick);
    std::cout << "> ";
}

void nts::shell::display() {
    std::cout << "tick: " << circuit.getCurrentTick() << std::endl;
    std::cout << "input(s):\n";
    auto inputs = circuit.getInputs();
    std::sort(inputs.begin(), inputs.end(), [](const auto& a, const auto& b) {
	return a.first < b.first;
    });
    for (const auto&[name, in] : inputs)
	std::cout << "  " << name << ": " << in.get().compute(1) << "\n";
    std::cout << "output(s):\n";
    auto outputs = circuit.getOutputs();
    std::sort(outputs.begin(), outputs.end(), [](const auto& a, const auto& b) {
	return a.first < b.first;
    });
    for (const auto&[name, out] : outputs)
	std::cout << "  " << name << ": " << out.get().compute(1) << "\n";
    std::cout << "> ";
}

void nts::shell::equal_operator(std::string &line) {
    std::string left, right;
    nts::Tristate state;
    try {
	nts::ParserUtils::split_in_half(line, left, right, '=');
    } catch (...) {
	std::cout << "Bad command format." << std::endl << "> ";
	return;
    }
    if (left.empty() || right.empty()) {
	std::cout << "Bad command format." << std::endl << "> ";
	return;
    }

    if (right == "0") {
	state = nts::Tristate::False;
    } else if (right == "1") {
	state = nts::Tristate::True;
    } else if (right == "U") {
	state = nts::Tristate::Undefined;
    } else {
	std::cout << right << " is not a valid Tristate." << std::endl << "> ";
	return;
    }
    try {
	nts::IComponent &c = circuit.getComponent(left);
	auto& rawPtr = dynamic_cast<nts::components::special::InputComponent&>(c);
	rawPtr.setState(state);
    } catch (...) {
	std::cout << left << " is not a valid input component." << std::endl << "> ";
	return;
    }
    std::cout << "> ";
}

void nts::shell::loop() {
    running = true;
    std::signal(SIGINT, signal_handler);
    while (running) {
	simulate();
	display();
    }
}

void nts::shell::run_shell() {
    std::cout << "> ";
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            std::cout << "> ";
            continue;
        }
        nts::ParserUtils::trim_string(line);
        if (line == "exit") {
            break;
	} else if (line == "simulate") {
	    simulate();
        } else if (line == "display") {
	    display();
        } else if (line == "loop") {
	    loop();
	} else if (line.find('=') != std::string::npos) {
	    equal_operator(line);
        } else {
	    std::cout << "Unknown command: " << line << std::endl << "> ";
	}
    }
}
