#include "src/Circuit.hpp"
#include <string>

namespace nts {
    class Parser {
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

	//removes spaces before and after the string
	void trim_string(std::string &str);
	
	//splits a string around a delimiter
	//trims left and right string
	void split_in_half(std::string &line, std::string &left, std::string &right, char dl = ' ');
	void extract_chipset(std::string &line);
	void extract_links(std::string &line);
	void dispatch_operations(ParserState state, std::string &line);
	void parse_file_internal(std::string filename);
    };
} // namespace nts
