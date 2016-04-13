#include "array_utility.h"
#include "integer.h"
#include <stack>

std::vector<int> ic::array_utility::flatten_array(const ic::Array &array)
{

    std::vector<int> result;

    auto iterator_pair = std::make_pair(std::begin(array), std::end(array));

    std::stack<decltype(iterator_pair)> stack;
    stack.push(iterator_pair);

    while (!stack.empty()) {

        auto &begin = stack.top().first;
        auto &end = stack.top().second;

        if (begin == end) {
            stack.pop();
            continue;
        }

        bool subarray_found = false;
        for (; begin != end && !subarray_found; ++begin) {
            if (ic::Integer *integer = dynamic_cast<ic::Integer*>((*begin).get())) {
                result.push_back(*integer);
            } else if (ic::Array *subarray = dynamic_cast<ic::Array*>((*begin).get())) {
                stack.push({ std::begin(*subarray), std::end(*subarray)});
                subarray_found = true;
            }
        }

    }
    
    return result;
}
