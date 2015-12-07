#ifndef PATCH_H_INCLUDED_
#define PATCH_H_INCLUDED_

#include <string>
#include <sstream>

namespace patch {
  template <typename T> std::string to_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

#endif
