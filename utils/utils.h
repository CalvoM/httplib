#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <algorithm>
namespace httplib{
    template<typename Obj, typename val>
    bool Contains(Obj o, val v){
        return std::find(Obj.begin(), Obj.end(), v) != Obj.end();
}
    
};
#endif
