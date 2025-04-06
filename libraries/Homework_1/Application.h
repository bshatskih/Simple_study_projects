#pragma once
#include "LongLong.h"
#include "Money.h"
#include "Exception.h"

class Application {
 private:
  int operation;
 public:
  Application();
  void run();
  void LongLong_run();
  void Money_run();
};
