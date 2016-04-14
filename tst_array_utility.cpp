#include "array_utility.h"
#include "integer.h"
#include "unit_test.h"
#include <stack>

std::ostream& operator<<(std::ostream& os, const ic::Array &array)
{
    os << "[";
    for (auto it = array.begin(), end = array.end(); it != end; ++it) {
        if (ic::Integer *integer = dynamic_cast<ic::Integer*>((*it).get())) {
            std::cout << static_cast<int>(*integer);
        } else if (ic::Array *subarray = dynamic_cast<ic::Array*>((*it).get())) {
            os << *subarray;
        }

        if (std::next(it) != end)
            os << ",";
    }
    os << "]";
    return os;
}

class UtilityTest
{
public:

    static std::unique_ptr<ic::Array> array_from_string(const std::string &string_array);

    //tests
    void empty_array_test() const;
    void array_with_one_integer_test() const;
    void flat_array_test() const;
    void invalid_type_in_array_ignored_test() const;
    void array_of_empty_array_test() const;
    void array_of_array_of_integer_test() const;
    void negative_integers_test() const;
    void requirements_example_test() const;
    void array_of_array_complex_test() const;
    void array_with_nullptr_test() const;
};


std::unique_ptr<ic::Array> UtilityTest::array_from_string(const std::string &string_array)
{
    auto begin = std::begin(string_array);
    auto end = std::end(string_array);

    ++begin;

    std::stack<ic::Array*> stack;
    auto array = std::make_unique<ic::Array>();
    stack.push(array.get());
    
    while (!stack.empty() && begin != end) {

        auto &current_array = *stack.top();

        switch (*begin) {

            case '[': {
                current_array.emplace_back(std::make_unique<ic::Array>());
                stack.push(static_cast<ic::Array*>(current_array.last().get()));
                ++begin;
            } break;
            
            case ']': {
                stack.pop();
                ++begin;
            } break;

            case ',': ++begin; break;

            default: {
                auto it = std::find_if(begin, end, [](char c) { return c == ',' || c == ']'; });
                current_array.emplace_back(std::make_unique<ic::Integer>(std::stoi(std::string(begin, it))));
                begin = it;
            }

        }
    }

    return array;
}

void UtilityTest::empty_array_test() const
{
    auto array = std::make_unique<ic::Array>();
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{});

    array = array_from_string("[]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{});
}

void UtilityTest::array_with_one_integer_test() const
{
    auto array = array_from_string("[42]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{42});
}

void UtilityTest::flat_array_test() const
{
    auto array = array_from_string("[42,1,90,145,1234,5,94,42]");
    std::vector<int> expected =     {42,1,90,145,1234,5,94,42};
    COMPARE(ic::array_utility::flatten_array(*array), expected);
}

void UtilityTest::invalid_type_in_array_ignored_test() const
{
    class TestType : public ic::Object
    {
    };

    ic::Array array;
    array.emplace_back(std::make_unique<TestType>());
    array.emplace_back(std::make_unique<ic::Integer>(42));
    array.emplace_back(std::make_unique<TestType>());
    COMPARE(ic::array_utility::flatten_array(array), std::vector<int>{42});
}

void UtilityTest::array_of_empty_array_test() const
{
    auto array = array_from_string("[[[[]]]]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{});

    array = array_from_string("[[[],[]]]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{});
}

void UtilityTest::array_of_array_of_integer_test() const
{
    auto array = array_from_string("[[[42]]]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{42});

    array = array_from_string("[[42],[],[]]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{42});

    array = array_from_string("[[],[],[],42]");
    COMPARE(ic::array_utility::flatten_array(*array), std::vector<int>{42});
}

void UtilityTest::negative_integers_test() const
{
    auto array = array_from_string("[-42]");
    std::vector<int> expected = {-42};
    COMPARE(ic::array_utility::flatten_array(*array), expected);

    array = array_from_string("[[],[2,5,-235],42]");
    expected = {2,5,-235,42};
    COMPARE(ic::array_utility::flatten_array(*array), expected);
}

void UtilityTest::requirements_example_test() const
{
    auto array = array_from_string("[[1,2,[3]],4]");
    std::vector<int> expected = {1,2,3,4};
    COMPARE(ic::array_utility::flatten_array(*array), expected);
}

void UtilityTest::array_of_array_complex_test() const
{
    auto array = array_from_string("[-1233,34,[1,2,[3]],434,[],[232,-4,[[[-122],-233,[]]]]]");
    std::vector<int> expected =    { -1233,34, 1,2, 3,  434,    232,-4,   -122, -233 };
    COMPARE(ic::array_utility::flatten_array(*array), expected);

    array = array_from_string("[1,[1,2,[1,2,3,[1,2,3,4,[1,2,3,4,5,[1,2,3,4,5,6,[1,2,3,4,5,6,7,[1,2,3,4,5,6,7,8,[1,2,3,4,5,6,7,8,9]]]]]]]]]");
    expected = { 1,1,2,1,2,3,1,2,3,4,1,2,3,4,5,1,2,3,4,5,6,1,2,3,4,5,6,7,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,9 };
}

void UtilityTest::array_with_nullptr_test() const
{
    ic::Array array;
    array.emplace_back(nullptr);
    COMPARE(ic::array_utility::flatten_array(array), std::vector<int>{});

    array.emplace_back(std::make_unique<ic::Integer>(42));
    array.emplace_back(std::make_unique<ic::Integer>(-23));
    array.emplace_back(nullptr);
    std::vector<int> expected = {42, -23};
    COMPARE(ic::array_utility::flatten_array(array), expected);
}

int main(int argc, char *argv[])
{
    UtilityTest utility_test;
    utility_test.empty_array_test();
    utility_test.array_with_one_integer_test();
    utility_test.invalid_type_in_array_ignored_test();
    utility_test.array_of_empty_array_test();
    utility_test.array_of_array_of_integer_test();
    utility_test.negative_integers_test();
    utility_test.requirements_example_test();
    utility_test.array_of_array_complex_test();
    utility_test.array_with_nullptr_test();

    return 0;
}
