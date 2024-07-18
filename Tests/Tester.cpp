#include "Tester.h"

Tester::Tester () {
    count = 0, failed = false;
}

void Tester::operator() (bool (*func) (), std::string_view test_name, std::string_view wrong_message) {
    if (failed)
        return;
    count++;
    if (!func ()) {
        std::cerr << test_name << ": " << wrong_message << std::endl;
        failed = true;
        std::cout << "Testcase failed, not proceeding with the remaining ones" << std::endl;
        return;
    }

    std::cout << "Test #" << count << ": '" << test_name << "' succeeded" << std::endl;
}


void Tester::operator() (bool (*func) (), std::string_view test_name) {
    operator() (func, test_name, "Testcase #" + std::to_string (count + 1) + " failed");
}
