#include "trim.h"

using namespace std;

string trim_right(string s) {
  if (s.empty())
    return {};

  int cnt {0};
  string::reverse_iterator it;
  for (it = s.rbegin(); it != s.rend(); it++)
    if (*it == ' ')
      cnt++;
    else
      break;

  if (cnt > 0)
    s.resize(s.size() - cnt);

  return s;
}

string trim_left(string s) {
  if (s.empty())
    return {};

  int cnt {0};
  string::iterator it;
  for (it = s.begin(); it != s.end(); it++)
    if (*it == ' ')
      cnt++;
    else
      break;

  if (cnt > 0)
    s = s.erase(0, cnt);

  return s;
}

string trim(string s) {
  return trim_left(trim_right(s));
}
