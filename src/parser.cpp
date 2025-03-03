/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Debug.cpp
*/

#include <cstddef>
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

#include "parser.hpp"
#include "Debug.hpp"
#include "components/IComponent.hpp"
#include "src/Factory.hpp"

size_t nts::ParserUtils::get_size_t_from_string(const std::string& s)
{
    std::istringstream iss(s);
    size_t res;
    iss >> res;
    if (iss.fail())
        throw std::runtime_error(s + " is not a valid number.");
    return res;
}

void nts::Parser::parse_file(const std::string& filename) const
{
    std::ifstream f;
    ParserState state = UNDEFINED;
    std::string line;

    f.open(filename);
    if (!f.is_open())
        throw std::runtime_error("could not open " + filename);

    while (getline(f, line))
        this->parse_line(line, state);
    f.close();
}

void nts::Parser::parse_buffer(const std::string& buffer) const
{
    std::istringstream f(buffer);
    ParserState state = UNDEFINED;
    std::string line;

    while (std::getline(f, line))
        this->parse_line(line, state);
}

//removes spaces before and after the string
void nts::ParserUtils::trim_string(std::string& str)
{
    if (str.empty())
        return;

    size_t i = 0;
    size_t j = str.length();

    while (i < str.length() && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (j > i && (str[j - 1] == ' ' || str[j - 1] == '\t'))
        j--;
    str = str.substr(i, j - i);
}

//splits a string around a delimiter
//trims left and right string
void nts::ParserUtils::split_in_half(std::string& line, std::string& left, // NOLINT(*-no-recursion)
                                     std::string& right, const char dl)
{
    std::size_t end;
    std::size_t start = end = 0;
    int found = 0;

    while ((start = line.find_first_not_of(dl, end)) != std::string::npos)
    {
        end = line.find(dl, start);
        if (found == 0 && left.empty())
            left = line.substr(start, end - start);
        if (found == 1 && right.empty())
            right = line.substr(start, end - start);
        ++found;
        if (found > 2)
            throw std::runtime_error("too many instructions in line");
    }
    if (found < 2 && dl == ' ')
        split_in_half(line, left, right, '\t');
    if (found < 2)
        throw std::runtime_error("not enough instructions in line");

    trim_string(left);
    trim_string(right);
}

void nts::Parser::extract_chipset(std::string& line) const
{
    std::string left, right;

    split_in_half(line, left, right);

    if (left.find(':') != std::string::npos || right.find(':') != std::string::npos)
        throw std::runtime_error("link found in chipset section.");

    DEBUG_PRINT("[chipset] " << left << " --> " << right << std::endl);

    try
    {
        const auto& c = this->m_circuit.getComponent(right);
        (void)c;
        throw std::runtime_error("chipset with name " + right + " already exists.");
    }
    catch (...) {}

    try
    {
        std::unique_ptr<IComponent> chipset = Factory::createComponent(left);
        this->m_circuit.addComponent(right, std::move(chipset));
    }
    catch (std::exception&)
    {
        throw std::runtime_error(left + " is not a valid chipset name.");
    }
}

void nts::Parser::extract_links(std::string& line) const
{
    std::string left, right;
    std::string ll, lr, rl, rr;

    split_in_half(line, left, right);
    DEBUG_PRINT("[links] " << left << " --> " << right << std::endl);

    split_in_half(left, ll, lr, ':');
    split_in_half(right, rl, rr, ':');

    const size_t l_pin = get_size_t_from_string(lr);
    const size_t r_pin = get_size_t_from_string(rr);

    IComponent& c1 = this->m_circuit.getComponent(ll);
    IComponent& c2 = this->m_circuit.getComponent(rl);

    if (c1.getConnections().at(l_pin - 1) != std::nullopt)
        throw std::runtime_error(std::to_string(l_pin) + " is already linked");
    if (c2.getConnections().at(r_pin - 1) != std::nullopt)
        throw std::runtime_error(std::to_string(l_pin) + " is already linked");

    if (l_pin > c1.getPinNumber() || l_pin <= 0)
        throw std::runtime_error(std::to_string(l_pin) + " is not a valid pin number for chipset " + ll);
    if (r_pin > c2.getPinNumber() || r_pin <= 0)
        throw std::runtime_error(std::to_string(r_pin) + " is not a valid pin number for chipset " + rl);
    c1.setLink(l_pin, c2, r_pin);
}

void nts::Parser::dispatch_operations(const ParserState state, std::string& line) const
{
    switch (state)
    {
        case CHIPSETS:
            extract_chipset(line);
            break;
        case LINKS:
            extract_links(line);
            break;
        default:
            throw std::runtime_error("invalid state in switch case or instruction outside of label");
    }
}

void nts::Parser::parse_line(std::string& line, ParserState& state) const
{
    if (line[0] == '#' || line.empty())
        return;
    trim_string(line);
    if (line[0] == '.')
    {
        if (line == ".chipsets:")
        {
            state = CHIPSETS;
        }
        else if (line == ".links:")
        {
            state = LINKS;
        }
        else
        {
            throw std::runtime_error(line + " is not a valid label.");
        }
        return;
    }
    dispatch_operations(state, line);
}
