#pragma once

#include <map>
#include <string>
#include <vector>

std::string join(std::vector<std::string> v, char del = '|');

class Define {
 public:
  Define() = default;
  Define(std::string name, std::vector<std::string> body)
    : name_(name), body_(body) {}

  std::string Body();
  std::vector<std::string> BodyParts();

  std::string BodyWoParams();
  std::vector<std::string> BodyPartsWoParam();

  bool HasParams();
  bool IsValid();

  std::string ParamName();

 private:
  std::string name_ {};
  std::vector<std::string> body_ {};
};

class Preprocessor {
 public:
  Preprocessor() = default;

  bool Preprocess(std::map<int, std::string> *lines);
  std::string StripLine(std::string);

  bool IsSpace(char);
  bool IsDelimeter(char);

  std::vector<std::string> Split(std::string);
  void AddDefineIntoMap(std::vector<std::string> parts);
  void ApplyDefines(std::map<int, std::string> *lines);

 private:
  std::map<std::string, Define> defines_ {};
};
