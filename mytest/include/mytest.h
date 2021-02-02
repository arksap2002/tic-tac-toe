#ifndef MYTEST_H_
#define MYTEST_H_

#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mytest {

struct Test {
private:
    std::function<void()> function;
    std::string name;
    bool is_passed;

public:
    Test(std::function<void()>, std::string);

    [[nodiscard]] std::function<void()> get_function() const;

    [[nodiscard]] std::string get_name() const;

    [[nodiscard]] bool get_is_passed() const;

    void make_is_not_passed();
};

int &current_index_function();

std::vector<Test> &tests();

void output_failed(const bool &,
                   const std::string &,
                   const int &,
                   const std::string &);

void output_message(const std::string &);

int run_tests();

// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define MYTEST_INTERNAL_TEST_CASE(class_name, name)                         \
    static void class_name();                                               \
    namespace {                                                             \
    [[maybe_unused]] struct Adding_##class_name {                           \
        Adding_##class_name() {                                             \
            mytest::tests().emplace_back(std::function<void()>(class_name), \
                                         name);                             \
        }                                                                   \
    } const adding_##class_name;                                            \
    }                                                                       \
    static void class_name()
// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define MYTEST_INTERNAL_TEST_CASE2(line, name) \
    MYTEST_INTERNAL_TEST_CASE(mytest_test_class_##line, name)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MYTEST_INTERNAL_TEST_CASE1(line, name) \
    MYTEST_INTERNAL_TEST_CASE2(line, name)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_CASE(name) MYTEST_INTERNAL_TEST_CASE1(__LINE__, name)
// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define CHECK(expression) \
    mytest::output_failed(expression, #expression, __LINE__, __FILE__)
// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define CHECK_MESSAGE(expression, message)                              \
    mytest::output_failed(expression, #expression, __LINE__, __FILE__); \
    if (!(expression))                                                  \
        mytest::output_message(message);
}  // namespace mytest

#endif
