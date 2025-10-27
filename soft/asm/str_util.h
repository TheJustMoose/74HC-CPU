#pragma once

#include <string>
#include <vector>

std::string ToUpper(std::string);
std::string NormalizeLine(std::string);
std::string RemoveQuotes(std::string);

bool StrToInt(std::string val, int* pout, std::string* err = nullptr);

bool IsSpace(char);
bool IsDelimeter(char);

std::vector<std::string> Split(std::string);
std::vector<std::string> SplitToCmdParts(std::string);

std::string trim_right(std::string s);
std::string trim_left(std::string s);
std::string trim(std::string s);
