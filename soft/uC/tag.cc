#include "tag.h"

namespace tag {

bool isChar(Tag t) {
  return static_cast<int>(t) < 256;
}

char cTag(Tag t) {
  return (static_cast<int>(t) < 256) ? static_cast<char>(t) : 0;
}

int rawTag(Tag t) {
  return static_cast<int>(t);
}

std::string toString(Tag t) {
  if (tag::isChar(t)) {
    std::string res;
    res = tag::cTag(t);
    return res;
  } else {
    return std::to_string(tag::rawTag(t));
  }
}

}  // namespace tag
