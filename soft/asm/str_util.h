#pragma once

#include <string>

std::string ToUpper(std::string s);
std::string NormalizeLine(std::string s);
std::string RemoveQuotes(std::string s);
bool StrToInt(std::string val, int* pout, std::string* err = nullptr);
