#ifndef _IC_ARRAY_UTILITY_H_
#define _IC_ARRAY_UTILITY_H_

#include "array.h"
#include <vector>

namespace ic {
namespace array_utility {

std::vector<int> flatten_array(const ic::Array &array);

} //namespace array_utility
} //namespace ic

#endif /* ifndef _IC_ARRAY_UTILITY_H_ */
