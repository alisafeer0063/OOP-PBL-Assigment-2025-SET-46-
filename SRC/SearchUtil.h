#ifndef SEARCH_UTIL_H
#define SEARCH_UTIL_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Generic search utility: searches a vector of shared_ptr<T>
// by comparing a field returned by fieldGetter with the given value.
template <typename T>
std::vector<std::shared_ptr<T>> searchByField(
    const std::vector<std::shared_ptr<T>>& items,
    const std::string& value,
    std::string (T::*fieldGetter)() const)
{
    std::vector<std::shared_ptr<T>> results;
    for (const auto& item : items) {
        if ((item.get()->*fieldGetter)() == value) {
            results.push_back(item);
        }
    }
    return results;
}

#endif
