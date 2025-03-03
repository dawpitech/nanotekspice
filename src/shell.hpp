#pragma once

#include <atomic>

#include "Circuit.hpp"

namespace nts
{
    class shell
    {
        private:
            static std::atomic<bool> running;
            Circuit& circuit;

            static void signal_handler(int);
            void simulate() const;
            void display() const;
            void equal_operator(std::string& line) const;
            void loop() const;

        public:
            void run_shell() const;

            explicit shell(Circuit& c) : circuit(c) {}
    };
}
