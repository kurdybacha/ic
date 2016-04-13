#ifndef _IC_INTEGER_H_
#define _IC_INTEGER_H_

#include "object.h"

namespace ic {

class Integer : public Object
{
public:
    Integer() : value_{0} {}
    Integer(int value) : value_{value} {}
     operator int() const { return value_; }
private:
    int value_;
};

} // namespace ic


#endif /* ifndef _IC_INTEGER_H_ */
