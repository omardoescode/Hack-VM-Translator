#pragma once
#include <iostream>
#include <string>

class Tester {
public:
    Tester ();
    void operator() (bool (*func) (), std::string_view test_name, std::string_view wrong_message);

    void operator() (bool (*func) (), std::string_view test_name);
    int getTestsCount () const {
        return count;
    }

    std::string get_state () const {
        return failed ? "Failure" : "Success";
    }

private:
    int count;
    bool failed;
};
