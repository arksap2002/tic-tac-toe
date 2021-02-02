#include "mytest.h"

namespace mytest {

Test::Test(std::function<void()> new_function, std::string new_name)
    : function(std::move(new_function)),
      name(std::move(new_name)),
      is_passed(true) {
}

std::function<void()> Test::get_function() const {
    return function;
}

std::string Test::get_name() const {
    return name;
}

bool Test::get_is_passed() const {
    return is_passed;
}

void Test::make_is_not_passed() {
    is_passed = false;
}

int &current_index_function() {
    static int new_current_index_function = 0;
    return new_current_index_function;
}

std::vector<Test> &tests() {
    static std::vector<Test> staticTests = {};
    return staticTests;
}

int run_tests() {
    current_index_function() = 0;
    int number_of_passed = 0;
    for (auto &function : tests()) {
        std::cerr << "Running \"" << function.get_name() << "\"...\n";
        function.get_function()();
        if (function.get_is_passed()) {
            number_of_passed++;
        }
        current_index_function()++;
    }
    std::cerr << "===== Tests passed: " << number_of_passed << '/'
              << tests().size() << " =====\n";
    return static_cast<int>(number_of_passed != int(tests().size()));
}

void output_failed(const bool &expression,
                   const std::string &string_expression,
                   const int &line,
                   const std::string &filename) {
    if (!expression) {
        std::cerr << "CHECK(" << string_expression << ") at " << filename << ":"
                  << line << " failed!\n";
        tests()[current_index_function()].make_is_not_passed();
    }
}

void output_message(const std::string &message) {
    std::cerr << "    message: " << message << '\n';
}
}  // namespace mytest
