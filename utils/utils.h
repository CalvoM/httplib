#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <iostream>
namespace httplib {
template <typename Obj, typename val> bool Contains(Obj o, val v) {
    return (std::find(o.begin(), o.end(), v) != o.end());
}
}; // namespace httplib
#endif
