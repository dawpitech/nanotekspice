#include <algorithm>
#include <csignal>
#include <iostream>

#include "shell.hpp"
#include "parser.hpp"

std::atomic<bool> nts::shell::running{true};

void nts::shell::signal_handler(int)
{
    running = false;
}

void nts::shell::simulate() const
{
    circuit.upCurrentTick();
    const auto newTick = circuit.getCurrentTick();

    for (const auto& [name, out] : circuit.getOutputs())
        out.get().simulate(newTick);
    std::cout << "> ";
}

void nts::shell::display() const
{
    std::cout << "tick: " << circuit.getCurrentTick() << std::endl;
    std::cout << "input(s):\n";
    auto inputs = circuit.getInputs();
    std::ranges::sort(inputs, [](const auto& a, const auto& b) { return a.first < b.first; });
    for (const auto& [name, in] : inputs)
        std::cout << "  " << name << ": " << in.get().compute(1) << "\n";
    std::cout << "output(s):\n";
    auto outputs = circuit.getOutputs();
    std::ranges::sort(outputs, [](const auto& a, const auto& b) { return a.first < b.first; });
    for (const auto& [name, out] : outputs)
        std::cout << "  " << name << ": " << out.get().compute(1) << "\n";
    std::cout << "> ";
}

void nts::shell::equal_operator(std::string& line) const
{
    std::string left, right;
    Tristate state;
    try
    {
        ParserUtils::split_in_half(line, left, right, '=');
    }
    catch (...)
    {
        std::cout << "Bad command format." << std::endl << "> ";
        return;
    }
    if (left.empty() || right.empty())
    {
        std::cout << "Bad command format." << std::endl << "> ";
        return;
    }

    if (right == "0")
        state = Tristate::False;
    else if (right == "1")
        state = Tristate::True;
    else if (right == "U")
        state = Tristate::Undefined;
    else
    {
        std::cout << right << " is not a valid Tristate." << std::endl << "> ";
        return;
    }
    try
    {
        IComponent& c = circuit.getComponent(left);
        auto& rawPtr = dynamic_cast<components::special::InputComponent&>(c);
        rawPtr.setState(state);
    }
    catch (...)
    {
        std::cout << left << " is not a valid input component." << std::endl << "> ";
        return;
    }
    std::cout << "> ";
}

void nts::shell::loop() const
{
    running = true;
    std::signal(SIGINT, signal_handler);
    while (running)
    {
        simulate();
        display();
    }
}

void nts::shell::run_shell() const
{
    std::cout << "> ";
    for (std::string line; std::getline(std::cin, line);)
    {
        if (line.empty())
        {
            std::cout << "> ";
            continue;
        }
        ParserUtils::trim_string(line);
        if (line == "exit")
            break;
        if (line == "simulate")
            simulate();
        else if (line == "display")
            display();
        else if (line == "loop")
            loop();
        else if (line.find('=') != std::string::npos)
            equal_operator(line);
        else
            std::cout << "Unknown command: " << line << std::endl << "> ";
    }
}
