#ifndef _IC_ARRAY_H
#define _IC_ARRAY_H

#include "object.h"
#include <vector>
#include <memory>

namespace ic {

class Array : public Object
{
private:
    std::vector<std::unique_ptr<Object>> elements_;
public:
    auto begin() -> decltype(elements_.begin()) { return elements_.begin(); }
    auto begin() const -> decltype(elements_.begin()) { return elements_.begin(); }

    auto end() -> decltype(elements_.end()) { return elements_.end(); }
    auto end() const -> decltype(elements_.end()) { return elements_.end(); }

    auto last() -> decltype(elements_.back()) { return elements_.back(); }
    auto last() const -> decltype(elements_.back()) { return elements_.back(); }

    template<class... Args>
    void emplace_back(Args&&... args) { elements_.emplace_back(std::forward<Args>(args)...); }
};

} //namespace ic

#endif /* ifndef _IC_ARRAY_H */
