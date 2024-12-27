#include "observer.h"

void Subject::Subscribe(Observer* obs) {
  observers_.push_back(obs);
}

void Subject::Notify() {
  for (auto obs : observers_)
    obs->OnChange(this);
}
