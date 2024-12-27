#pragma once

#include <vector>

class Observer;

class Subject {
public:
  void Subscribe(Observer*);
  void Notify();

private:
  std::vector<Observer*> observers_;
};

class Observer {
public:
  virtual void OnChange(Subject*) = 0;
};
