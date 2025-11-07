#include "error_collector.h"

// static
ErrorCollector& Singleton::GetInstance() {
  static ErrorCollector instance;
  return instance;
}
