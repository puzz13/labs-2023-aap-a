#include "convert_to_lowercase.h"

#include <cctype>

char * kovtun::convertToLowercase(char * destination, const char * source)
{
  char * destinationBegin = destination;
  for ( ; *source != '\0'; destination++, source++)
  {
    *destination = tolower(*source);
  }

  return destinationBegin;
}