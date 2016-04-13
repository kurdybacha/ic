#ifndef _IC_UNIT_TESTS_H_
#define _IC_UNIT_TESTS_H_

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

namespace unit_tests {

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "vector = { ";
    if (!v.empty()) {
        std::copy(v.cbegin(), std::prev(v.cend()), std::ostream_iterator<T>(os, ", "));
        os << v.back();
    }
    os << " }";
    return os;
}

template<typename T> 
void print_data(T t, const int& width)
{
    using namespace std;
    static const char fill_char = ' ';
    cout << left << setw(width) << setfill(fill_char) << t;
}

template<typename T>
void compare(const T& actual, const T& expected, const char* actual_s, const char* expected_s, const char* function, const char* file, int line)
{
    using namespace std;
    static const int result_width = 9;
    static const int line_width = 4;
    static const int function_width = 50;

    const bool pass = actual == expected;

    print_data(pass ? "OK" : "FAILED", result_width);
    print_data(std::to_string(line) + ":", line_width);
    print_data(function, function_width);
    if (!pass)
        cout << "Expected (" << expected << ") Result (" << actual << ")" << " COMPARE(" << actual_s << " == " << expected_s << ")";
    cout << endl;
}

} // namespace unit_tests

#define COMPARE(actual, expected) unit_tests::compare(actual, expected, #actual, #expected, __FUNCTION__, __FILE__, __LINE__)

#endif /* ifndef _IC_UNIT_TESTS_H_ */
