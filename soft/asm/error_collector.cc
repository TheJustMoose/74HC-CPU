#include "error_collector.h"

// static
ErrorCollector& ErrorCollector::GetInstance() {
  static ErrorCollector instance;
  return instance;
}
