#include "parser.hpp"
#include "src/Factory.hpp"
#include "src/IComponent.hpp"
#include <cstddef>
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

size_t nts::ParserUtils::get_size_t_from_string(std::string &s) {
    std::istringstream iss(s);
    size_t res;
    iss >> res;
    if (iss.fail())
        throw std::runtime_error(s + " is not a valid number.");
    return res;
}

void nts::Parser::parse_file(std::string filename) {
    this->parse_file_internal(filename);
}

//removes spaces before and after the string
void nts::ParserUtils::trim_string(std::string &str) {
    std::string res;
    unsigned int i = 0;
    unsigned int j = str.length() - 1;

    if (str.empty())
        return;
    for (; str[i] != '\0'; i++)
        if (str[i] != '\t' && str[i] != ' ')
            break;
    for (; str[j] != '\0'; j--)
        if (str[j] != '\t' && str[j] != ' ')
            break;
    res = str.substr(i, j - i + 1);
    str = res;
}

//splits a string around a delimiter
//trims left and right string
void nts::ParserUtils::split_in_half(std::string &line, std::string &left, std::string &right, char dl) {
    std::size_t start, end;
    start = end = 0;
    int found = 0;

    while ((start = line.find_first_not_of(dl, end)) != std::string::npos) {
        end = line.find(dl, start);
        if (found == 0 && left == "")
            left = line.substr(start, end - start);
        if (found == 1 && right == "")
            right = line.substr(start, end - start);
        ++found;
        if (found > 2)
            throw std::runtime_error("too many instructions in line");
    }
    if (found < 2 && dl == ' ') {
        split_in_half(line, left, right, '\t');
    }
    if (found < 2)
        throw std::runtime_error("not enough instructions in line");

    nts::ParserUtils::trim_string(left);
    nts::ParserUtils::trim_string(right);
}

void nts::Parser::extract_chipset(std::string &line) {
    std::string left, right;

    nts::ParserUtils::split_in_half(line, left, right);

    if ((left.find(':') != std::string::npos) || (right.find(':') != std::string::npos))
        throw std::runtime_error("link found in chipset section.");

    std::cout << "[chipset] " << left << " --> " << right << std::endl;

    try {
        this->m_circuit.getComponent(right);
        throw std::runtime_error("chipset with name " + right + " already exists.");
    } catch (...) {
    }

    try {
        std::unique_ptr<nts::IComponent> chipset = nts::Factory::createComponent(left);
        this->m_circuit.addComponent(right, std::move(chipset));
    } catch (std::exception &e) {
        throw std::runtime_error(left + " is not a valid chipset name.");
    }
}

void nts::Parser::extract_links(std::string &line) {
    std::string left, right;
    std::string ll, lr, rl, rr;
    size_t l_pin, r_pin;

    nts::ParserUtils::split_in_half(line, left, right);
    std::cout << "[links] " << left << " --> " << right << std::endl;

    nts::ParserUtils::split_in_half(left, ll, lr, ':');
    nts::ParserUtils::split_in_half(right, rl, rr, ':');

    l_pin = nts::ParserUtils::get_size_t_from_string(lr);
    r_pin = nts::ParserUtils::get_size_t_from_string(rr);

    std::cout << "\t[links] " << ll << " --> " << lr << std::endl;
    std::cout << "\t[links] " << rl << " --> " << rr << std::endl;
    
    IComponent &c1 = this->m_circuit.getComponent(ll);
    IComponent &c2 = this->m_circuit.getComponent(rl);

    if (l_pin > c1.getPinNumber() || l_pin <= 0)
        throw std::runtime_error(std::to_string(l_pin) + " is not a valid pin number for chipset " + ll);
    if (r_pin > c2.getPinNumber() || r_pin <= 0)
        throw std::runtime_error(std::to_string(r_pin) + " is not a valid pin number for chipset " + rl);
    c1.setLink(l_pin, c2, r_pin);
}

void nts::Parser::dispatch_operations(ParserState state, std::string &line) {
    switch (state) {
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

void nts::Parser::parse_file_internal(std::string filename) {
    std::ifstream f;
    std::string line;
    ParserState state = UNDEFINED;

    f.open(filename);
    if (!f.is_open())
        throw std::runtime_error("could not open " + filename);

    while (getline(f, line)) {
        if (line[0] == '#' || line.empty())
            continue;
        nts::ParserUtils::trim_string(line);
        if (line[0] == '.') {
            if (line == ".chipsets:") {
                state = CHIPSETS;
            } else if (line == ".links:") {
                state = LINKS;
            } else {
                throw std::runtime_error(line + " is not a valid label.");
            }
            continue;
        }
        dispatch_operations(state, line);
    }

    f.close();
}
