#ifndef M_UTILITY_HPP
#define M_UTILITY_HPP
#include <memory>
//https://stackoverflow.com/questions/45507041/how-to-check-if-weak-ptr-is-empty-non-assigned
template <typename T>
bool CheckInitialization(std::weak_ptr<T> const& weak) {
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

#endif //M_UTILITY_HPP