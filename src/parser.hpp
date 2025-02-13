/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** parser.hpp
*/

#pragma once

#include <string>

#include "src/Circuit.hpp"

namespace nts {
    class ParserUtils {
    public:
	//removes spaces before and after the string
	static void trim_string(std::string &str);
	
	//splits a string around a delimiter
	//trims left and right string
	static void split_in_half(std::string &line, std::string &left, std::string &right, char dl = ' ');

	static size_t get_size_t_from_string(std::string &s);
    };
    
    class Parser : ParserUtils {
    public:
	Parser(nts::Circuit &circuit, std::string filename = "") : m_circuit(circuit) {
	    if (filename.empty())
		return;
	    parse_file(filename);
	}
	
	void parse_file(std::string filename);
    private:
	nts::Circuit &m_circuit;
	
	enum ParserState {
	    CHIPSETS,
	    LINKS,
	    UNDEFINED
	};

	void extract_chipset(std::string &line);
	void extract_links(std::string &line);
	void dispatch_operations(ParserState state, std::string &line);
	void parse_file_internal(std::string filename);
    };
} // namespace nts
