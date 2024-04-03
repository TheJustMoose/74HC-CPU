#pragma once

#include <map>
#include <memory>

class Id;
class Token;

class Env {
 public:
  typedef std::map<Token*, std::shared_ptr<Id>> SymTable;

  Env(Env* n = nullptr) {
    prev_ = n;
  }

  void put(Token* w, std::shared_ptr<Id> i) {
    table_[w] = i;
  }

  std::shared_ptr<Id> get(Token* w) {
    for (Env* e = this; e != nullptr; e = e->prev_) {
      SymTable::iterator it = e->table_.find(w);
      if (it != e->table_.end())
        return it->second;
    }
    return nullptr;
  }

 protected:
  Env* prev_ {nullptr};

 private:
  SymTable table_;  // Hashtable
};
