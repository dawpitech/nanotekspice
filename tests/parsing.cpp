/*
** EPITECH PROJECT, 2025
** tests
** File description:
** parsing
*/

#include <criterion/criterion.h>
#include <stdexcept>
#include "../src/parser.hpp"

bool test_file(std::string filename) {
    nts::Circuit circuit;
    const nts::Parser p(circuit);

    try {
	p.parse_file("tests/parser/" + filename);
	if (circuit.getComponents().empty())
	    throw std::runtime_error("no components found in file.");
	return true;
    } catch (...) {
	return false;
    }
}

Test(parsing, valid_file_comments) {
    if (!test_file("valid_file_comments.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_duplicates) {
    if (test_file("invalid_file_duplicates.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_links_in_chipsets) {
    if (test_file("invalid_file_links_in_chipsets.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_no_components) {
    if (test_file("invalid_file_no_components.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_empty) {
    if (test_file("invalid_file_empty.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_bad_link_name) {
    if (test_file("invalid_file_bad_link_name.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_NaN) {
    if (test_file("invalid_file_NaN.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file) {
    if (test_file("uwu"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_too_much_instr) {
    if (test_file("invalid_file_too_much_instr.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_not_enough_instr) {
    if (test_file("invalid_file_not_enough_instr.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_bad_chipset_name) {
    if (test_file("invalid_file_bad_chipset_name.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_bad_pin_l) {
    if (test_file("invalid_file_bad_pin_l.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_bad_pin_r) {
    if (test_file("invalid_file_bad_pin_r.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_already_linked_l) {
    if (test_file("invalid_file_already_linked_l.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_already_linked_r) {
    if (test_file("invalid_file_already_linked_r.nts"))
	throw std::runtime_error("test failed");
}

Test(parsing, invalid_file_bad_label) {
    if (test_file("invalid_file_bad_label.nts"))
	throw std::runtime_error("test failed");
}
