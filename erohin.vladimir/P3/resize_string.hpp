#ifndef RESIZE_STRING_HPP
#define RESIZE_STRING_HPP

#include <cstddef>

namespace erohin
{
  char * resizeString(const char * str, size_t size, size_t shift);
  char * resizeString(const char * str, const char * source);
}

#endif
