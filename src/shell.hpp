#pragma once
#include "Circuit.hpp"
#include <atomic>

namespace nts {
    class shell {
    private:
	static std::atomic<bool> running;
	nts::Circuit &circuit;

	static void signal_handler(int);
	void simulate();
	void display();
	void equal_operator(std::string &line);
	void loop();

    public:
	void run_shell();

	shell(nts::Circuit &c) : circuit(c) {
	}
    };
}
