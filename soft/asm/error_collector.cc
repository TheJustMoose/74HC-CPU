#include "error_collector.h"

// static
ErrorCollector* Singleton::GetInstance() {
  if (!instance_)
    instance_ = new ErrorCollector();

  return instance_;
}

// static
ErrorCollector* Singleton::instance_ {nullptr};
